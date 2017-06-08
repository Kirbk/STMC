#pragma once

#include "Capsule.h"
#include <Engine/InputManager.h>
#include <Engine/SpriteBatch.h>
#include <Engine/TileSheet.h>

enum class PlayerMoveState { STANDING, RUNNING, PUNCHING, IN_AIR };

class Player {
public:
	void init(b2World* world,
		const glm::vec2& position,
		const glm::vec2& drawDims,
		glm::vec2& collisionDims,
		Engine::ColorRGBA8 color);
	void destroy(b2World* world);

	void draw(Engine::SpriteBatch& spriteBatch);
	void drawDebug(Engine::DebugRenderer& debugRenderer);

	void update(Engine::InputManager& inputManager);

	const Capsule& getCapsule() const { return m_capsule; }

	glm::vec2 getPosition() const {
		glm::vec2 rv;
		rv.x = m_capsule.getBody()->GetPosition().x;
		rv.y = m_capsule.getBody()->GetPosition().y;
		return rv;
	}

	const glm::vec2& getDrawDims() const { return m_drawDims; }
	const glm::vec2& getCollisionDims() const { return m_collisionDims; }
	const Engine::ColorRGBA8& getColor() const { return m_color; }

private:
	glm::vec2 m_drawDims;
	glm::vec2 m_collisionDims;
	Engine::ColorRGBA8 m_color;
	Engine::TileSheet m_texture;
	Capsule m_capsule;
	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
	float m_animTime = 0.0f;
	int m_direction = 1; // 1 or -1
	bool m_onGround = false;
	bool m_isPunching = false;
};

