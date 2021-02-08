#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>

class Texture
{
public:
	/*
	* 根据图片路径加载并解析生成为opengl的纹理
	*/
	void init(const std::string imagePath);

	/*
	* opengl纹理的id
	*/
	GLuint  textureID_;
};

