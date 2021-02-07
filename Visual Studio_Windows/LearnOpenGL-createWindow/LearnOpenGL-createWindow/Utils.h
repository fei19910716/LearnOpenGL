#pragma once

#include <iostream>
#include <string>

namespace Utils {
	unsigned char* loadFileContent(const std::string imagePath);

	unsigned char* decodeBMP(unsigned char* bpmData, int& width, int& height);

	void drawSimpleVertex();
}

