#pragma once

#include "Capsule.h"
#include <Engine\SpriteBatch.h>
#include <Engine\GLTexture.h>
#include <Engine\InputManager.h>
#include <Engine\TileSheet.h>

enum class PlayerMoveState {STANDING, RUNNING, PUNCHING, IN_AIR};

class Player
{
public:
	void init(b2World* world,
		const glm::vec2& position,
		const glm::vec2& drawDims,
		glm::vec2& collisionDims,
		Engine::ColorRGBA8 color);
	void draw(Engine::SpriteBatch& spriteBatch);
	void drawDebug(Engine::DebugRenderer & debugRenderer);
	void update(Engine::InputManager& inputManager);

	const Capsule& getCapsule() const { return m_capsule; }
	
	glm::vec2 getPosition() const {
		glm::vec2 rv;
		rv.x = m_capsule.getBody()->GetPosition().x;
		rv.y = m_capsule.getBody()->GetPosition().y;

		return rv;
	}

	bool isOnGround();

private:
	glm::vec2 m_drawDims;
	Capsule m_capsule;
	Engine::TileSheet m_texture;
	Engine::ColorRGBA8 m_color;
	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
	float m_animTime = 0.0f;
	int m_direction = 1;
	bool m_onGround = false;
	bool m_punching = false;
};

