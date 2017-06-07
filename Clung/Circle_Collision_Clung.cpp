#include "Circle_Collision_Clung.h"

#include "Entity_Clung.h"


Circle_Collision_Clung::Circle_Collision_Clung()
{
}


Circle_Collision_Clung::~Circle_Collision_Clung()
{
}

void Circle_Collision_Clung::init(b2World * world, Entity_Clung* parent, const glm::vec2 & position, const glm::vec2 & dimensions, float density, float friction, bool fixedRotation)
{
	m_parent = parent;
	m_dimensions = dimensions;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	m_body = world->CreateBody(&bodyDef);

	m_body->SetUserData(parent);

	// Create the circle
	b2CircleShape circleShape;
	circleShape.m_radius = dimensions.x / 2.0f;

	b2FixtureDef circleDef;
	circleDef.shape = &circleShape;
	circleDef.density = density;
	circleDef.friction = friction;
	circleDef.userData = parent;

	circleShape.m_p.Set(0.0f, 0.0f);
	m_fixtures.push_back(m_body->CreateFixture(&circleDef));
}

void Circle_Collision_Clung::drawDebug(Engine::DebugRenderer & debugRenderer)
{
	Engine::ColorRGBA8 color(255, 255, 255, 255);

	debugRenderer.drawCircle(glm::vec2(m_parent->getPosition().x, m_parent->getPosition().y), color, m_dimensions.x / 2.0f);
}
