#include "Ball_Pong.h"

#include <Engine\ResourceManager.h>


Ball_Pong::Ball_Pong()
{
}


Ball_Pong::~Ball_Pong()
{
}

void Ball_Pong::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions, const glm::vec2& screenDims, Engine::ColorRGBA8 color, int speed, glm::vec4 uvRect)
{
	m_dimensions = dimensions;
	m_screenDims = screenDims;
	m_color = color;
	m_speed = speed;

	Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/textures/circle.png");
	m_texture.init(texture, glm::ivec2(1, 1));

	m_uvRect = uvRect;
	m_fixedRotation = true;
	m_isDynamic = true;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	m_body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = dimensions.x / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;

	circleShape.m_p.Set(0.0f, 0.0f);
	m_fixture = m_body->CreateFixture(&fixtureDef);

	m_body->SetLinearVelocity(b2Vec2(m_speed, 0.0f));
}

void Ball_Pong::destroy(b2World * world)
{

}

void Ball_Pong::draw(Engine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;
	spriteBatch.draw(destRect, m_uvRect, m_texture.texture.id, 0.0f, m_color, m_body->GetAngle());
}

void Ball_Pong::update()
{
	if ((m_body->GetPosition().x - (m_dimensions.x / 2.0f)) > m_screenDims.x / 2.0f) {
		m_body->SetTransform(b2Vec2(-m_body->GetPosition().x + 1.0f, m_body->GetPosition().y), m_body->GetAngle());
	}

	if ((m_body->GetPosition().x + (m_dimensions.x / 2.0f)) < -m_screenDims.x / 2.0f) {
		m_body->SetTransform(b2Vec2(-m_body->GetPosition().x - 1.0f, m_body->GetPosition().y), m_body->GetAngle());
	}

	if ((m_body->GetPosition().y - (m_dimensions.y / 2.0f)) > m_screenDims.y / 2.0f) {
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -m_body->GetPosition().y + 1.0f), m_body->GetAngle());
	}

	if ((m_body->GetPosition().y + (m_dimensions.y / 2.0f)) < -m_screenDims.y / 2.0f) {
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x, -m_body->GetPosition().y - 1.0f), m_body->GetAngle());
	}
}
