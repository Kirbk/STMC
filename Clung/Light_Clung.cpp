#include "Light_Clung.h"



Light_Clung::Light_Clung(glm::vec2& pos, float Size, Engine::ColorRGBA8 Color) : position(pos), size(Size), color(Color)
{
}


Light_Clung::~Light_Clung()
{	
}

void Light_Clung::update(std::vector<Entity_Clung*> const entities)
{
	m_entities = entities;
	m_rays = castRays();
}

void Light_Clung::drawDebug(Engine::DebugRenderer & debugRenderer)
{
	for (glm::vec2 pts : m_rays) {
		float halfX = size / 2.0f;
		float halfY = size / 2.0f;
		glm::vec2 pos;

		glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, pts));
		if (pts.y < 0.0f) angle = -angle;

		pos.x = (cos(angle) * size) + position.x;
		pos.y = (sin(angle) * size) + position.y;

		debugRenderer.drawLine(position, pos, Engine::ColorRGBA8(255, 255, 255, 255));
	}
}

std::vector<glm::vec2> Light_Clung::castRays()
{
	std::vector<glm::vec2> points;
	
	for (Entity_Clung* e : m_entities) {
		switch (e->getShape()) {
		case Shape::RECTANGLE:
			{
				glm::vec2 halfDims = e->getDrawDims() / 2.0f;

				glm::vec2 tlPoint(-halfDims.x, halfDims.y);
				glm::vec2 blPoint(-halfDims.x, -halfDims.y);
				glm::vec2 brPoint(halfDims.x, -halfDims.y);
				glm::vec2 trPoint(halfDims.x, halfDims.y);

				tlPoint = rotatePoint(tlPoint, e->getAngle()) + e->getPosition();
				blPoint = rotatePoint(blPoint, e->getAngle()) + e->getPosition();
				brPoint = rotatePoint(brPoint, e->getAngle()) + e->getPosition();
				trPoint = rotatePoint(trPoint, e->getAngle()) + e->getPosition();

				glm::vec4 topFace(tlPoint.x, tlPoint.y, trPoint.x, trPoint.y);
				glm::vec4 bottomFace(blPoint.x, blPoint.y, brPoint.x, brPoint.y);
				glm::vec4 rightFace(trPoint.x, trPoint.y, brPoint.x, brPoint.y);
				glm::vec4 leftFace(tlPoint.x, tlPoint.y, blPoint.x, blPoint.y);

				glm::vec2 tl = glm::normalize(tlPoint - position);
				glm::vec2 bl = glm::normalize(blPoint - position);
				glm::vec2 br = glm::normalize(brPoint - position);
				glm::vec2 tr = glm::normalize(trPoint - position);

				//if (get_line_intersection() || get_line_intersection()) {
					points.push_back(tl);
				//}

				
				points.push_back(bl);
				points.push_back(br);
				points.push_back(tr);
			}
			break;

		case Shape::ROUND:
			// TODO: ROUND RAY CAST

			break;
		default:
			break;
		}
	}

	return points;
}

glm::vec2 Light_Clung::rotatePoint(glm::vec2 pos, float angle)
{
	
	glm::vec2 newvec;

	newvec.x = pos.x * cos(angle) - pos.y * sin(angle);
	newvec.y = pos.x * sin(angle) + pos.y * cos(angle);
	
	return newvec;
}

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
	float p2_x, float p2_y, float p3_x, float p3_y)
{
	float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
	s10_x = p1_x - p0_x;
	s10_y = p1_y - p0_y;
	s32_x = p3_x - p2_x;
	s32_y = p3_y - p2_y;

	denom = s10_x * s32_y - s32_x * s10_y;
	if (denom == 0)
		return 0; // Collinear
	bool denomPositive = denom > 0;

	s02_x = p0_x - p2_x;
	s02_y = p0_y - p2_y;
	s_numer = s10_x * s02_y - s10_y * s02_x;
	if ((s_numer < 0) == denomPositive)
		return 0; // No collision

	t_numer = s32_x * s02_y - s32_y * s02_x;
	if ((t_numer < 0) == denomPositive)
		return 0; // No collision

	if (((s_numer > denom) == denomPositive) || ((t_numer > denom) == denomPositive))
		return 0; // No collision
				  // Collision detected
	return 1;
}