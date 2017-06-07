#include "Level_Clung.h"

#include <Engine\EngineErrors.h>
#include <fstream>
#include <iostream>

#include <Engine\ResourceManager.h>
#include <Engine\Camera2D.h>
#include <Box2D\Box2D.h>

#include "Wall_Clung.h"
#include "MedKit_Clung.h"

Level_Clung::Level_Clung(const std::string& fileName, b2World* world, Engine::Camera2D* camera)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail())
		Engine::fatalError("failed to open" + fileName);

	std::string tmp;
	file >> tmp;
	m_rawLevelData.push_back(tmp);

	std::getline(file, tmp);

	while (std::getline(file, tmp)) {
		m_rawLevelData.push_back(tmp);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Engine::ColorRGBA8 color(255, 255, 255, 255);

	/*
	for (int y = 0; y < m_rawLevelData.size(); y++) {
		for (int x = 0; x < m_rawLevelData[y].size(); x++) {
			char tile = m_rawLevelData[y][x];
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile) {
			case '#':
				m_spriteBatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("Assets/textures/block.png").id, 0.0f, Engine::ColorRGBA8(128, 128, 128, 255));
				break;
			case '@':
				m_rawLevelData[y][x] = '.';
				m_startPlayerPosition.x = x * TILE_WIDTH;
				m_startPlayerPosition.y = y * TILE_WIDTH;
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected Symbol '%c' at (%d, %d)", tile, x, y);
				break;
			}
		}
	}

	m_spriteBatch.end();

	*/
	
	for (int y = 0; y < m_rawLevelData.size(); y++) {
		for (int x = 0; x < m_rawLevelData[y].size(); x++) {
			char tile = m_rawLevelData[y][x];
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile) {
			case 'W':
				m_entityData.push_back(new Wall_Clung());
				m_entityData.back()->init(world, glm::vec2(x * 3, y * 3), glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(3), glm::vec2(3), camera, color);
				break;
			case '@':
				m_rawLevelData[y][x] = '.';
				m_startPlayerPosition.x = x * TILE_WIDTH;
				m_startPlayerPosition.y = y * TILE_WIDTH;
				break;
			case 'm':
				m_itemData.push_back(new MedKit_Clung(20));
				m_itemData.back()->init(world, glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH), glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(1.0f), glm::vec2(1.0f), camera, color);
				break;
			case 'M':
				m_itemData.push_back(new MedKit_Clung(50));
				m_itemData.back()->init(world, glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH), glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(1.0f), glm::vec2(1.0f), camera, color);
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected Symbol '%c' at (%d, %d)", tile, x, y);
				break;
			}
		}
	}
}

Level_Clung::~Level_Clung()
{
}

void Level_Clung::draw() {
	m_spriteBatch.renderBatch();
}