#pragma once

#include <Engine\SpriteBatch.h>
#include <Engine\InputManager.h>
#include <Engine\Camera2D.h>
#include <Engine\TileSheet.h>
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

enum Shape {
	ROUND,
	RECTANGLE
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
		glm::vec4& uvRect,
		Engine::Camera2D* camera,
		Engine::ColorRGBA8 color) = 0;

	virtual void init(b2World* world,
		const glm::vec2& position,
		glm::vec2& direction,
		float speed,
		const glm::vec2& drawDims,
		glm::vec2& collisionDims,
		glm::vec4& uvRect,
		Engine::Camera2D* camera,
		Engine::ColorRGBA8 color,
		Engine::InputManager* inputManager);

	virtual void update() = 0;
	void draw(Engine::SpriteBatch& spriteBatch);

	const glm::vec2 getPosition() const { return m_position; }
	const EntityCategory getType() const { return m_type; }
	bool isItem() { return m_item; }
	const ItemList getItemType() const { return m_itemType; }
	void destroy() { m_destroy = true; }
	bool isDestroyed() { return m_destroy; }
	const glm::vec2 getDrawDims() const { return m_drawDims; }
	const glm::vec2 getDirection() const { return m_direction; }
	const float getAngle() const { return m_angle; }
	const Shape getShape() const { return m_shape; }
	const glm::vec2& getCollisionDims() const { return m_collisionDims; }
	const Engine::ColorRGBA8& getColor() const { return m_color; }
	const glm::vec4& getUVRect() const { return m_uvRect; }
	const Engine::TileSheet& getTexture() const { return m_texture; }
	const bool& getFixedRotation() const { return m_fixedRotation; }
	const bool& getIsDynamic() const { return m_isDynamic; }


protected:
	glm::vec2 m_position;
	glm::vec2 m_drawDims;
	glm::vec2 m_direction = glm::vec2(1.0f, 0.0f);
	float m_angle = 0;

	Engine::ColorRGBA8 m_color;
	Engine::Camera2D* m_camera;
	Engine::InputManager* m_inputManager = nullptr;

	Engine::TileSheet m_texture;
	float m_health = 0, m_speed = 0;
	EntityCategory m_type;
	ItemList m_itemType;
	Shape m_shape = Shape::RECTANGLE;
	bool m_item = false;
	bool m_destroy = false;
	glm::vec2 m_collisionDims;
	glm::vec4 m_uvRect;
	bool m_fixedRotation;
	bool m_isDynamic;
};

