#pragma once

#include "Entity_Clung.h"

#include "Box_Collision_Clung.h"

class Wall_Clung : public Entity_Clung
{
public:
	Wall_Clung();
	~Wall_Clung();

	// Inherited via Entity_Clung
	virtual void init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, Engine::Camera2D * camera, Engine::ColorRGBA8 color) override;
	virtual void update() override;

	void drawDebug(Engine::DebugRenderer& debugRenderer);
private:
	Box_Collision_Clung m_box;
};

