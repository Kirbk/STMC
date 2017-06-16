#include "Entity_Clung.h"

#include <iostream>


Entity_Clung::Entity_Clung()
{
}


Entity_Clung::~Entity_Clung()
{
}

void Entity_Clung::init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D * camera, Engine::ColorRGBA8 color, Engine::InputManager * inputManager)
{
	m_inputManager = inputManager;
	init(world, position, direction, speed, drawDims, collisionDims, camera, color);
}

void Entity_Clung::draw(Engine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;

	destRect.x = m_position.x - m_drawDims.x / 2.0f;
	destRect.y =  m_position.y - m_drawDims.y / 2.0f;

	destRect.z = m_drawDims.x;
	destRect.w = m_drawDims.y;

	spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_textureID, 0.0f, m_color, m_direction);
}
