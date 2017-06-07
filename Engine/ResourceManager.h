#pragma once
#include "TextureCache.h"
#include <string>

//This is a way for us to access all our resources, such as
//Models or textures.

namespace Engine {
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;
	};

}