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

void Player_Clung::init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, glm::vec4& uvRect, Engine::Camera2D * camera, Engine::ColorRGBA8 color)
{
	Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/textures/placeholder.png");
	m_texture.init(texture, glm::ivec2(1, 1));
	m_type = EntityCategory::PLAYER;
	m_color = color;
	m_speed = speed;
	m_camera = camera;
	m_drawDims = drawDims;
	m_shape = Shape::ROUND;
	m_circle.init(world, this, position, collisionDims, 1.0f, 0.1f, true);
	m_collisionDims = collisionDims;
	m_uvRect = uvRect;

	b2Filter filter = m_circle.getFixtures()[0]->GetFilterData();
	filter.categoryBits = EntityCategory::PLAYER;
	m_circle.getFixtures()[0]->SetFilterData(filter);

	m_controllerPreviousX = m_camera->convertScreenToWorld(glm::vec2((m_camera->getScreenDims().x / 2.0f) + 1.0f)).x;
	m_controllerPreviousY = m_camera->convertScreenToWorld(glm::vec2(m_camera->getScreenDims().y / 2.0f)).y;
}

void Player_Clung::update()
{
	if (m_boundController != nullptr) {
		if (!m_boundController->isBinded) {
			m_boundController = nullptr;
		}
	}

	b2Body* body = m_circle.getBody();

	m_angle = body->GetAngle();

	float deltaX, deltaY;
	deltaX = body->GetPosition().x - m_position.x;
	deltaY = body->GetPosition().y - m_position.y;

	m_controllerPreviousX += deltaX;
	m_controllerPreviousY += deltaY;

	m_position.x = body->GetPosition().x;
	m_position.y = body->GetPosition().y;

	if (m_boundController == nullptr) {
		if (m_inputManager->isKeyDown(SDLK_a)) {
			body->ApplyForceToCenter(b2Vec2(-m_speed, 0.0f), true);
		}
		else if (m_inputManager->isKeyDown(SDLK_d)) {
			body->ApplyForceToCenter(b2Vec2(m_speed, 0.0f), true);
		}

		if (m_inputManager->isKeyDown(SDLK_w)) {
			body->ApplyForceToCenter(b2Vec2(0.0f, m_speed), true);
		}
		else if (m_inputManager->isKeyDown(SDLK_s)) {
			body->ApplyForceToCenter(b2Vec2(0.0f, -m_speed), true);
		}
	}

	if (m_boundController != nullptr) {
		updateController(m_inputManager);
	}

	body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.9f, body->GetLinearVelocity().y * 0.9f));

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

	if (m_boundController == nullptr) {

		glm::vec2 mouseCoords = m_inputManager->getMouseCoords();
		mouseCoords = m_camera->convertScreenToWorld(mouseCoords);

		glm::vec2 centerPosition = glm::vec2(m_position.x, m_position.y);
		m_direction = glm::normalize(mouseCoords - centerPosition);

		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, m_direction));
		if (m_direction.y < 0.0f) angle = -angle;

		if (std::to_string(angle) == "-nan(ind)") {
			m_direction = right;
			angle = acos(glm::dot(right, m_direction));
		}

		body->SetTransform(body->GetPosition(), angle);
	}

	if (m_health > m_maxHealth) {
		m_health = m_maxHealth;
	}

	if (m_boundController != nullptr) {
		//std::cout << m_boundController->index << " | " << m_boundController->SDL_Index << std::endl;
	}

	/*if (m_boundController == nullptr) {
		for (int i = 0; i < m_inputManager->getMaxControllers(); i++) {
			if (m_inputManager->getController(i) != nullptr) {
				if (!m_inputManager->getController(i)->isBinded) {
					bindController(i, m_inputManager);
					m_boundController->axes[(int)Engine::XBOX360Axes::rightStickX]->deadZone = 10000;
					m_boundController->axes[(int)Engine::XBOX360Axes::rightStickY]->deadZone = 10000;
					break;
				}
			}
		}
	}*/
}

void Player_Clung::drawDebug(Engine::DebugRenderer& debugRenderer) {
	m_circle.drawDebug(debugRenderer);
}

void Player_Clung::bindController(Engine::Controller controller, Engine::InputManager* const inputManager)
{
	bindController(controller.index, inputManager);
}

void Player_Clung::bindController(unsigned int controllerIndex, Engine::InputManager* const inputManager)
{
	if (inputManager->getController(controllerIndex) != nullptr) {
		m_boundController = inputManager->getController(controllerIndex);
		m_boundController->isBinded = true;
	}
	else {
		std::cout << "Controller Not Found!\n";
	}
}

void Player_Clung::updateController(Engine::InputManager* const inputManager) {
	b2Body* body = m_circle.getBody();

	if (m_boundController->axes[0]->axisValue > m_boundController->axes[0]->deadZone) {
		body->ApplyForceToCenter(b2Vec2(m_speed * abs(m_boundController->axes[0]->axisValue / 32768.0f), 0.0f), true);
	}
	else if (m_boundController->axes[0]->axisValue < -m_boundController->axes[0]->deadZone) {
		body->ApplyForceToCenter(b2Vec2(-m_speed * abs(m_boundController->axes[0]->axisValue / 32768.0f), 0.0f), true);
	}

	if (m_boundController->axes[1]->axisValue > m_boundController->axes[1]->deadZone) {
		body->ApplyForceToCenter(b2Vec2(0.0f, -m_speed * abs(m_boundController->axes[1]->axisValue / 32768.0f)), true);
	}
	else if (m_boundController->axes[1]->axisValue < -m_boundController->axes[1]->deadZone) {
		body->ApplyForceToCenter(b2Vec2(0.0f, m_speed * abs(m_boundController->axes[1]->axisValue / 32768.0f)), true);
	}

	float x = m_controllerPreviousX;
	float y = m_controllerPreviousY;

	if ((abs(m_boundController->axes[(int)Engine::XBOX360Axes::rightStickX]->axisValue) > m_boundController->axes[(int)Engine::XBOX360Axes::rightStickX]->deadZone) || (abs(m_boundController->axes[(int)Engine::XBOX360Axes::rightStickY]->axisValue) > m_boundController->axes[(int)Engine::XBOX360Axes::rightStickY]->deadZone)) {
		x = m_camera->convertScreenToWorld(glm::vec2(m_boundController->axes[(int)Engine::XBOX360Axes::rightStickX]->axisValue)).x;
		y = m_camera->convertScreenToWorld(glm::vec2(m_boundController->axes[(int)Engine::XBOX360Axes::rightStickY]->axisValue)).y;
	}

	glm::vec2 centerPosition(m_position.x, m_position.y);
	glm::vec2 rotateCoords(x, y);

	m_direction = glm::normalize(rotateCoords - centerPosition);

	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, m_direction));
	
	if (m_direction.y < 0.0f) angle = -angle;

	body->SetTransform(body->GetPosition(), angle);

	m_controllerPreviousX = x;
	m_controllerPreviousY = y;
}