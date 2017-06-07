#pragma once

#include <Box2D\Box2D.h>
#include <glm.hpp>
#include <Engine\Vertex.h>
#include <Engine\SpriteBatch.h>
#include <Engine\GLTexture.h>
#include <Engine\InputManager.h>
#include <Engine\Camera2D.h>
#include <Engine\DebugRenderer.h>

class Entity_Clung;

class Box_Collision_Clung
{
public:
	Box_Collision_Clung();
	~Box_Collision_Clung();

	void init(b2World* world, b2BodyType type, Entity_Clung* parent, const glm::vec2& position, const glm::vec2& dimensions, bool fixedRotation = false, glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void drawDebug(Engine::DebugRenderer & debugRenderer);


	b2Body* getBody() const { return m_body; }
	std::vector<b2Fixture*> getFixtures() { return m_fixtures; }
	const glm::vec2& getDimensions() const { return m_dimensions; }
	const Engine::ColorRGBA8 getColor() const { return m_color; }

private:
	glm::vec4 m_uvRect;
	Entity_Clung* m_parent = nullptr;
	b2Body* m_body = nullptr;
	std::vector<b2Fixture*> m_fixtures;
	glm::vec2 m_dimensions;
	Engine::ColorRGBA8 m_color;
};


