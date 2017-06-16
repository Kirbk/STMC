#pragma once

#include "Entity_Clung.h"

class Player_Clung : public Entity_Clung
{
public:
	Player_Clung(float maxHealth);
	~Player_Clung();

	// Inherited via Entity_Clung
	virtual void init(b2World * world, const glm::vec2 & position, glm::vec2& direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D* camera, Engine::ColorRGBA8 color) override;
	virtual void update() override;
	void drawDebug(Engine::DebugRenderer& debugRenderer);

	const Circle_Collision_Clung& getCircle() const { return m_circle; }
	float getMaxHealth() const { return m_maxHealth; }
	float getHealth() const { return m_health; }
	void setHealth(float health) { m_health = health; }
	void addHealth(float amount) { m_health += amount; }

	void bindController(Engine::Controller controller, Engine::InputManager* const inputManager);
	void bindController(unsigned int controllerIndex, Engine::InputManager* const inputManager);

	const Engine::Controller* getBoundController() const { return m_boundController; }
	void updateController(Engine::InputManager* const inputManager);

private:
	Circle_Collision_Clung m_circle;
	Engine::Controller* m_boundController = nullptr;
	float m_maxHealth;
	float m_health;
	float m_controllerPreviousX, m_controllerPreviousY;
};

