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
}