#pragma once

#include <vector>
#include <Engine\SpriteBatch.h>

#include "Entity_Clung.h"

const int TILE_WIDTH = 2;

class Level_Clung
{
public:
	Level_Clung(const std::string& fileName, b2World* world, Engine::Camera2D* camera);
	~Level_Clung();

	void draw();

	const std::vector<std::string>& getRawLevelData() const { return m_rawLevelData; }
	const std::vector<Entity_Clung*>& getEntityData() const { return m_entityData; }
	const std::vector<Entity_Clung*>& getItemData() const { return m_itemData; }
	glm::vec2 getStartPlayerPos() const { return m_startPlayerPosition; }
private:
	std::vector<std::string> m_rawLevelData;
	std::vector<Entity_Clung*> m_entityData;
	std::vector<Entity_Clung*> m_itemData;
	Engine::SpriteBatch m_spriteBatch;
	glm::vec2 m_startPlayerPosition;
};

