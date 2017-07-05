#include "Paddle_Pong.h"

#include <Engine\ResourceManager.h>

Paddle_Pong::Paddle_Pong()
{
}


Paddle_Pong::~Paddle_Pong()
{
}

void Paddle_Pong::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions, Engine::ColorRGBA8 color, int playerID, glm::vec4 uvRect)
{
	m_id = playerID;
	m_dimensions = dimensions;
	m_color = color;

	Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/textures/block.png");
	m_texture.init(texture, glm::ivec2(1, 1));

	m_uvRect = uvRect;
	m_fixedRotation = true;
	m_isDynamic = true;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Paddle_Pong::destroy(b2World * world)
{
}

void Paddle_Pong::draw(Engine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;
	spriteBatch.draw(destRect, m_uvRect, m_texture.texture.id, 0.0f, m_color, m_body->GetAngle());
}

void Paddle_Pong::update(Engine::InputManager & inputManager)
{

	if (m_id == 0) {
		if (inputManager.isKeyDown(SDLK_w)) {
			m_body->SetLinearVelocity(b2Vec2(0.0f, 100.0f));

		}
		else if (inputManager.isKeyDown(SDLK_s)) {
			m_body->SetLinearVelocity(b2Vec2(0.0f, -100.0f));
		}
		else {
			m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}
	else {
		if (inputManager.isKeyDown(SDLK_UP)) {
			m_body->SetLinearVelocity(b2Vec2(0.0f, 100.0f));

		}
		else if (inputManager.isKeyDown(SDLK_DOWN)) {
			m_body->SetLinearVelocity(b2Vec2(0.0f, -100.0f));
		}
		else {
			m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
	}

	if (true) {

	}
}

