#include "Box.h"
#include <SDL.h>
#include <iostream>

Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions, Engine::GLTexture texture, Engine::ColorRGBA8 color, bool fixedRotation, glm::vec4 uvRect)
{
	m_uvRect = uvRect;
	m_dimensions = dimensions;
	m_color = color;
	m_texture = texture;
	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2, dimensions.y / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Box::draw(Engine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	spriteBatch.draw(destRect, m_uvRect, m_texture.id, 0.0f, m_color, m_body->GetAngle());
}

void Box::update(Engine::InputManager& inputManager, Engine::Camera2D& camera)
{
	glm::vec2 pos = camera.convertScreenToWorld(inputManager.getMouseCoords());
	b2Vec2 mousePosition(pos.x, pos.y);

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		//std::cout << "(" << mousePosition.x << ", " << mousePosition.y << ") : (" << m_body->GetPosition().x << ", " << m_body->GetPosition().y << ")\n";
		//std::cout << m_fixture->TestPoint(mousePosition) << std::endl;
		m_isGrabbed = m_fixture->TestPoint(mousePosition);
	}

	if (m_isGrabbed) {
		m_body->SetAwake(true);

		const float MOTION_SCALE = 100.0f;
		b2Vec2 direction((mousePosition.x - m_body->GetPosition().x) * MOTION_SCALE, (mousePosition.y - m_body->GetPosition().y) * MOTION_SCALE - m_body->GetWorld()->GetGravity().y);
		m_body->ApplyForceToCenter(direction, true);

		m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x * 0.9f, m_body->GetLinearVelocity().y * 0.9f));

		if (!inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			m_isGrabbed = false;
			m_body->SetAwake(true);
		}

		if (inputManager.isScrolling()) {
			m_body->ApplyTorque(inputManager.getScrollAmount() * 20, true);
		}
	}

	m_mousePosition = pos;
}