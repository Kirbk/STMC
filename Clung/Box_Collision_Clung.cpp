#include "Box_Collision_Clung.h"

#include <iostream>

#include "Entity_Clung.h"


Box_Collision_Clung::Box_Collision_Clung()
{
}


Box_Collision_Clung::~Box_Collision_Clung()
{
}

void Box_Collision_Clung::init(b2World * world, b2BodyType type, Entity_Clung* parent, const glm::vec2 & position, const glm::vec2 & dimensions, bool fixedRotation, glm::vec4 uvRect)
{
	m_parent = parent;

	m_uvRect = uvRect;
	m_dimensions = dimensions;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;

	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, m_parent->getDirection()) / (glm::length(right) * glm::length(m_parent->getDirection())));
	if (m_parent->getDirection().y < 0.0f) angle = -angle;
	
	bodyDef.angle = angle;
	m_body = world->CreateBody(&bodyDef);

	m_body->SetUserData(parent);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = parent;
	m_fixtures.push_back(m_body->CreateFixture(&fixtureDef));
}

void Box_Collision_Clung::drawDebug(Engine::DebugRenderer & debugRenderer)
{
	glm::vec4 destRect;

	destRect.x = m_parent->getPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_parent->getPosition().y - m_dimensions.y / 2.0f ;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	debugRenderer.drawBox(destRect, Engine::ColorRGBA8(255, 255, 255, 255), m_body->GetAngle());

	float halfX = m_parent->getDrawDims().x / 2.0f;
	float halfY = 0;
	glm::vec2 pos;
	pos.x = (halfX * cos(m_body->GetAngle()) - halfY * sin(m_body->GetAngle())) + m_parent->getPosition().x;
	pos.y = (halfX * sin(m_body->GetAngle()) + halfY * cos(m_body->GetAngle())) + m_parent->getPosition().y;

	debugRenderer.drawLine(m_parent->getPosition(), pos, Engine::ColorRGBA8(255, 255, 255, 255));
}

glm::vec2 rotatePoint(glm::vec2 pos, float angle) {
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}