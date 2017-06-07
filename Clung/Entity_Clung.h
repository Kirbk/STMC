#pragma once

#include <Engine\SpriteBatch.h>
#include <Engine\InputManager.h>
#include <Engine\Camera2D.h>
#include <Box2D\Box2D.h>

#include "Circle_Collision_Clung.h"

enum EntityCategory {
	BOUNDARY = 0x0001,
	PLAYER = 0x0002,
	ENEMY = 0x0004,
	ITEM = 0x0008,
};

enum ItemList {
	MedKit = 0x0001
};

class Entity_Clung
{
public:
	Entity_Clung();
	virtual ~Entity_Clung();

	virtual void init(b2World* world,
		const glm::vec2& position,
		glm::vec2& direction,
		float speed,
		const glm::vec2& drawDims,
		glm::vec2& collisionDims,
		Engine::Camera2D* camera,
		Engine::ColorRGBA8 color) = 0;

	virtual void update(Engine::InputManager* const inputManager = nullptr) = 0;
	void draw(Engine::SpriteBatch& spriteBatch);

	glm::vec2 getPosition() { return m_position; }
	EntityCategory getType() const { return m_type; }
	bool isItem() { return m_item; }
	ItemList getItemType() { return m_itemType; }
	void destroy() { m_destroy = true; }
	bool isDestroyed() { return m_destroy; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_drawDims;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);

	Engine::ColorRGBA8 m_color;
	Engine::Camera2D* m_camera;

	int m_textureID;
	float m_health = 0, m_speed = 0;
	EntityCategory m_type;
	ItemList m_itemType;
	bool m_item = false;
	bool m_destroy = false;
};

