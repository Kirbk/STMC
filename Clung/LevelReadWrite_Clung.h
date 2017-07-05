#pragma once

#include <string>

#include "Player_Clung.h"
#include "Item_Clung.h"

class LevelReadWrite_Clung {
public:
	static bool saveAsText(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items);
	static bool saveAsBinary(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items);
	static bool loadAsText(const std::string& filePath, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items);
	static bool loadAsBinary(const std::string& filePath, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items);
private:
	static bool saveAsTextV0(const std::string& filePath, const Player_Clung& player, const std::vector<Item_Clung>& items);
	static bool loadAsTextV0(std::ifstream& file, b2World* world, Player_Clung& player, std::vector<Item_Clung>& items);
};

