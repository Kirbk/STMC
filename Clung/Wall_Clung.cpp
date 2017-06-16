#include "Wall_Clung.h"

#include <Engine\ResourceManager.h>


Wall_Clung::Wall_Clung()
{
}


Wall_Clung::~Wall_Clung()
{
}

void Wall_Clung::init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D * camera, Engine::ColorRGBA8 color)
{
	m_textureID = Engine::ResourceManager::getTexture("Assets/textures/wall.png").id;
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_drawDims = drawDims;
	m_camera = camera;
	m_color = color;
	m_box.init(world, b2_staticBody, this, m_position, collisionDims);
	m_type = EntityCategory::BOUNDARY;
}

void Wall_Clung::update()
{
	m_position.x = m_box.getBody()->GetPosition().x;
	m_position.y = m_box.getBody()->GetPosition().y;

	m_direction.x = cos(m_box.getBody()->GetAngle());
	m_direction.y = sin(m_box.getBody()->GetAngle());
}

void Wall_Clung::drawDebug(Engine::DebugRenderer& debugRenderer) {
	m_box.drawDebug(debugRenderer);
}