#include "Border_Pong.h"

#include <Engine\ResourceManager.h>

Border_Pong::Border_Pong()
{
}


Border_Pong::~Border_Pong()
{
}

void Border_Pong::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions, Engine::ColorRGBA8 color, glm::vec4 uvRect)
{
	m_dimensions = dimensions;
	m_color = color;

	Engine::GLTexture texture = Engine::ResourceManager::getTexture("Assets/textures/border.png");
	m_texture.init(texture, glm::ivec2(1, 1));

	m_uvRect = uvRect;
	m_fixedRotation = true;
	m_isDynamic = true;

	// Make the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.isSensor = true;
}

void Border_Pong::destroy(b2World * world)
{
}

void Border_Pong::draw(Engine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;
	spriteBatch.draw(destRect, m_uvRect, m_texture.texture.id, 0.0f, m_color, m_body->GetAngle());
}
