#include "LevelReadWrite_Clung.h"

#include <Engine/ResourceManager.h>
#include <fstream>

// When you want to make a new version, add it here
const unsigned int TEXT_VERSION_0 = 100;

// Make sure this is set to the current version
const unsigned int TEXT_VERSION = TEXT_VERSION_0;

bool LevelReadWrite_Clung::saveAsText(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items) {
	// Keep this updated with newest version
	return saveAsTextV0(filePath, player, items);
}

bool LevelReadWrite_Clung::saveAsTextV0(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items) {
	// Open file and error check
	std::ofstream file(filePath);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	// Write version
	file << TEXT_VERSION << '\n';
	// Write player
	file << player.getPosition().x << ' ' << player.getPosition().y << ' '
		<< player.getDrawDims().x << ' ' << player.getDrawDims().y << ' '
		<< player.getCollisionDims().x << ' ' << player.getCollisionDims().y << ' '
		<< player.getColor().r << ' ' << player.getColor().g << ' '
		<< player.getColor().b << ' ' << player.getColor().a << '\n';

	// Write number of items
	file << items.size() << '\n';
	// Write all items
	for (auto& b : items) {
		file << b.getPosition().x << ' ' << b.getPosition().y << ' '
			<< b.getCollisionDims().x << ' ' << b.getCollisionDims().y << ' '
			<< b.getColor().r << ' ' << b.getColor().g << ' '
			<< b.getColor().b << ' ' << b.getColor().a << ' '
			<< b.getUVRect().x << ' ' << b.getUVRect().y << ' '
			<< b.getUVRect().z << ' ' << b.getUVRect().w << ' '
			<< b.getAngle() << ' ' << b.getTexture().texture.filePath << ' '
			<< b.getIsDynamic() << ' ' << b.getFixedRotation() << '\n';
	}

	// Write number of lights
	/*file << lights.size() << '\n';
	// Write all lights
	for (auto& l : lights) {
		file << l.position.x << ' ' << l.position.y << ' '
			<< l.size << ' ' << l.color.r << ' ' << l.color.g << ' '
			<< l.color.b << ' ' << l.color.a << '\n';
	}*/

	return true;
}

bool LevelReadWrite_Clung::saveAsBinary(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items) {
	puts("saveBinary not implemented.");
	return false;
}

bool LevelReadWrite_Clung::loadAsText(const std::string& filePath, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items) {
	// Open file and error check
	std::ifstream file(filePath);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	// Get version
	unsigned int version;
	file >> version;

	// Parse based on version
	switch (version) {
	case TEXT_VERSION_0:
		loadAsTextV0(file, world, player, items);
		break;
	default:
		puts("Unknown version number in level file. File may be corrupted...");
		return false;
	}

	return true;
}

bool LevelReadWrite_Clung::loadAsBinary(const std::string& filePath, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items) {
	puts("loadBinary not implemented.");
	return false;
}

bool LevelReadWrite_Clung::loadAsTextV0(std::ifstream& file, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items) {
	{ // Read player
		glm::vec2 pos;
		glm::vec2 ddims;
		glm::vec2 cdims;
		Engine::ColorRGBA8 color;
		file >> pos.x >> pos.y >> ddims.x >> ddims.y >> cdims.x >> cdims.y >> color.r >> color.g >> color.b >> color.a;
		//player.init(world, pos, ddims, , cdims, color);
	}

	{ // Read boxes
		glm::vec2 pos;
		glm::vec2 dims;
		glm::vec4 uvRect;
		Engine::ColorRGBA8 color;
		bool fixedRotation;
		bool isDynamic;
		float angle;
		Engine::GLTexture texture;
		std::string texturePath;
		size_t numItems;
		file >> numItems;
		for (size_t i = 0; i < numItems; i++) {
			file >> pos.x >> pos.y >> dims.x >> dims.y >> color.r >> color.g >> color.b >> color.a
				>> uvRect.x >> uvRect.y >> uvRect.z >> uvRect.w
				>> angle >> texturePath >> isDynamic >> fixedRotation;

			texture = Engine::ResourceManager::getTexture(texturePath);

			//boxes.emplace_back();
			//boxes.back().init(world, pos, dims, texture, color, fixedRotation, isDynamic, angle, uvRect);
		}
	}

	/*{ // Read lights
		glm::vec2 pos;
		float size;
		Engine::ColorRGBA8 color;
		size_t numLights;
		file >> numLights;
		for (size_t i = 0; i < numLights; i++) {
			file >> pos.x >> pos.y >> size >> color.r >> color.g >> color.b >> color.a;
			lights.emplace_back();
			lights.back().color = color;
			lights.back().position = pos;
			lights.back().size = size;
		}
	}*/

	return true;
}
