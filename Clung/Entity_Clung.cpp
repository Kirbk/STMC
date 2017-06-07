#include "Entity_Clung.h"

#include <iostream>


Entity_Clung::Entity_Clung()
{
}


Entity_Clung::~Entity_Clung()
{
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
