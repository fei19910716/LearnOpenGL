#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>

class Texture
{
public:
	void init(const std::string imagePath);

	GLuint  textureID_;
};

