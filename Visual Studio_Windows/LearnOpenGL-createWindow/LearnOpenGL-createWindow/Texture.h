#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>

class Texture
{
public:
	/*
	* ����ͼƬ·�����ز���������Ϊopengl������
	*/
	void init(const std::string imagePath);

	/*
	* opengl�����id
	*/
	GLuint  textureID_;
};

