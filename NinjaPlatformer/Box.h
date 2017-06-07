#pragma once

#include <Box2D\Box2D.h>
#include <glm.hpp>
#include <Engine\Vertex.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLTexture.h>
#include <Engine\InputManager.h>
#include <Engine\Camera2D.h>

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, Engine::GLTexture texture, Engine::ColorRGBA8 color, bool fixedRotation = false, glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void draw(Engine::SpriteBatch& spriteBatch);
	void update(Engine::InputManager& inputManager, Engine::Camera2D& camera);


	b2Body* getBody() const { return m_body; }
	b2Fixture* getFixture() const { return m_fixture; }
	const glm::vec2& getDimensions() const { return m_dimensions; }
	const Engine::ColorRGBA8 getColor() const { return m_color; }

private:
	glm::vec4 m_uvRect;
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	glm::vec2 m_dimensions;
	Engine::ColorRGBA8 m_color;
	Engine::GLTexture m_texture;
	bool m_isGrabbed = false;
	glm::vec2 m_mousePosition;
};

