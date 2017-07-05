#pragma once

#include "Item_Clung.h"
#include "Box_Collision_Clung.h"

class MedKit_Clung : public Item_Clung
{
public:
	MedKit_Clung(float benefit = 0);
	~MedKit_Clung();

	// Inherited via Entity_Clung
	virtual void init(b2World * world, const glm::vec2 & position, glm::vec2 & direction, float speed, const glm::vec2 & drawDims, glm::vec2 & collisionDims, glm::vec4& uvRect, Engine::Camera2D * camera, Engine::ColorRGBA8 color) override;
	virtual void update() override;

	void drawDebug(Engine::DebugRenderer& debugRenderer);

	const Box_Collision_Clung& getBox() const { return m_box; }
	float getBenefit() const { return m_benefit; }
	bool isUsed() const { return m_used; }
	void setUsed(bool use = true) { m_used = use; }

private:
	Box_Collision_Clung m_box;
	float m_benefit;
	bool m_used = false;
};

