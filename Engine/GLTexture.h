#pragma once
#include <glew.h>
#include <string>

namespace Engine {
	struct GLTexture {
		std::string filePath = "";
		GLuint id;
		int width;
		int height;
	};
}