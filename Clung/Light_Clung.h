#pragma once

#include <vector>
#include <Engine\Vertex.h>
#include <glm.hpp>

#include "Entity_Clung.h"

enum class RelativeLocation {
	TOP_LEFT,
	BOTTOM_LEFT,
	TOP_RIGHT,
	BOTTOM_RIGHT
};

struct Point {
	glm::vec2 location;
	RelativeLocation relativeLocation;
};

class Light_Clung
{
public:
	Light_Clung(glm::vec2& pos, float Size, Engine::ColorRGBA8 Color);
	~Light_Clung();

	void update(std::vector<Entity_Clung*> const entities);

	Engine::ColorRGBA8 color;
	glm::vec2 position;
	float size;
	std::vector<Entity_Clung*> m_entities;

	void drawDebug(Engine::DebugRenderer& debugRenderer);

private:
	std::vector<glm::vec2> castRays();
	glm::vec2 rotatePoint(glm::vec2 pos, float angle);
	std::vector<glm::vec2> m_rays;
};

