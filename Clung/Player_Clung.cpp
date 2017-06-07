#include "Player_Clung.h"

#include <Engine\ResourceManager.h>
#include <Engine\InputManager.h>
#include <iostream>


Player_Clung::Player_Clung(float maxHealth)
{
	m_maxHealth = maxHealth;
	m_health = maxHealth;
}


Player_Clung::~Player_Clung()
{
}

void Player_Clung::init(b2World * world, const glm::vec2 & position, glm::vec2& direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D* camera, Engine::ColorRGBA8 color)
{
	m_textureID = Engine::ResourceManager::getTexture("Assets/textures/placeholder.png").id;
	m_type = EntityCategory::PLAYER;
	m_color = color;
	m_speed = speed;
	m_camera = camera;
	m_drawDims = drawDims;
	m_circle.init(world, this, position, collisionDims, 1.0f, 0.1f, true);

	b2Filter filter = m_circle.getFixtures()[0]->GetFilterData();
	filter.categoryBits = EntityCategory::PLAYER;
	m_circle.getFixtures()[0]->SetFilterData(filter);


}

void Player_Clung::update(Engine::InputManager* const inputManager)
{
	b2Body* body = m_circle.getBody();

	m_position.x = body->GetPosition().x;
	m_position.y = body->GetPosition().y;

	if (inputManager->isKeyDown(SDLK_a)) {
		body->ApplyForceToCenter(b2Vec2(-m_speed, 0.0f), true);
	}
	else if (inputManager->isKeyDown(SDLK_d)) {
		body->ApplyForceToCenter(b2Vec2(m_speed, 0.0f), true);
	}
	else {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.9f, body->GetLinearVelocity().y));
	}
	
	if (inputManager->isKeyDown(SDLK_w)) {
		body->ApplyForceToCenter(b2Vec2(0.0f, m_speed), true);
	}
	else if (inputManager->isKeyDown(SDLK_s)) {
		body->ApplyForceToCenter(b2Vec2(0.0f, -m_speed), true);
	}
	else {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, body->GetLinearVelocity().y * 0.9f));
	}

	const float MAX_SPEED = 10.0f;
	if (body->GetLinearVelocity().x < -MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(-MAX_SPEED, body->GetLinearVelocity().y));
	}
	else if (body->GetLinearVelocity().x > MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(MAX_SPEED, body->GetLinearVelocity().y));
	}

	if (body->GetLinearVelocity().y < -MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -MAX_SPEED));
	}
	else if (body->GetLinearVelocity().y > MAX_SPEED) {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, MAX_SPEED));
	}

	glm::vec2 mouseCoords = inputManager->getMouseCoords();
	mouseCoords = m_camera->convertScreenToWorld(mouseCoords);

	glm::vec2 centerPosition = glm::vec2(body->GetPosition().x, body->GetPosition().y) + glm::vec2(m_drawDims.x / 2.0f);
	m_direction = glm::normalize(mouseCoords - centerPosition);

	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, m_direction));
	if (m_direction.y < 0.0f) angle = -angle;

	if (std::to_string(angle) == "-nan(ind)") {
		m_direction = right;
		angle = acos(glm::dot(right, m_direction));
	}

	body->SetTransform(body->GetPosition(), angle);

	if (m_health > m_maxHealth) {
		m_health = m_maxHealth;
	}
}

void Player_Clung::drawDebug(Engine::DebugRenderer& debugRenderer) {
	m_circle.drawDebug(debugRenderer);
}