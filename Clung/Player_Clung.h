#pragma once

#include "Entity_Clung.h"

class Player_Clung : public Entity_Clung
{
public:
	Player_Clung(float maxHealth);
	~Player_Clung();

	// Inherited via Entity_Clung
	virtual void init(b2World * world, const glm::vec2 & position, glm::vec2& direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D* camera, Engine::ColorRGBA8 color) override;
	virtual void update(Engine::InputManager* const inputManager = nullptr) override;
	void drawDebug(Engine::DebugRenderer& debugRenderer);

	const Circle_Collision_Clung& getCircle() const { return m_circle; }
	float getMaxHealth() const { return m_maxHealth; }
	float getHealth() const { return m_health; }
	void setHealth(float health) { m_health = health; }
	void addHealth(float amount) { m_health += amount; }

private:
	Circle_Collision_Clung m_circle;
	float m_maxHealth;
	float m_health;
};

