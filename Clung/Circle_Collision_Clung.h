#pragma once

#include <Box2D\Box2D.h>
#include <glm.hpp>
#include <Engine\DebugRenderer.h>

class Entity_Clung;

class Circle_Collision_Clung
{
public:
	Circle_Collision_Clung();
	~Circle_Collision_Clung();

	void init(b2World* world, Entity_Clung* parent, const glm::vec2& position, const glm::vec2& dimensions, float density, float friction, bool fixedRotation = false);
	void drawDebug(Engine::DebugRenderer& debugRenderer);

	b2Body* getBody() const { return m_body; }
	std::vector<b2Fixture*> getFixtures() { return m_fixtures; }
	const glm::vec2& getDimensions() const { return m_dimensions; }

private:
	Entity_Clung* m_parent = nullptr;
	b2Body* m_body = nullptr;
	std::vector<b2Fixture*> m_fixtures;
	glm::vec2 m_dimensions;
};

