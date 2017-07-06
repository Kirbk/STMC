#pragma once

#include <Box2D/Box2D.h>
#include <glm.hpp>
#include <Engine/Vertex.h>
#include <Engine/SpriteBatch.h>
#include <Engine/GLTexture.h>
#include <Engine\TileSheet.h>
#include <Engine\InputManager.h>
#include <Engine\DebugRenderer.h>

class Border_Pong
{
public:
	Border_Pong();
	~Border_Pong();

	void init(b2World* world,
		const glm::vec2& position,
		const glm::vec2& dimensions,
		Engine::ColorRGBA8 color,
		glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	void destroy(b2World* world);

	void draw(Engine::SpriteBatch& spriteBatch);

private:
	glm::vec4 m_uvRect;
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimensions;
	glm::vec2 m_screenDims;
	Engine::ColorRGBA8 m_color;
	bool m_fixedRotation;
	bool m_isDynamic;
	Engine::TileSheet m_texture;
};

