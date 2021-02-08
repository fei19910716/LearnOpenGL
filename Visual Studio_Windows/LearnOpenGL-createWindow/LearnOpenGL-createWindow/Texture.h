#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <unordered_map>
#include <memory>

class Texture
{
public:
	/*
	* 根据图片路径加载并解析生成为opengl的纹理
	*/
	void init(const std::string imagePath);

	
	void initWithSOIL(const std::string imagePath, bool flip_y = false);

	/*
	* opengl纹理的id
	*/
	GLuint  textureID_;

	std::string path_;

	static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_map_;
	static std::shared_ptr<Texture> textureCreate(const std::string imagePath, bool flip_y = false);
	static void removeTexture(std::shared_ptr<Texture> texture);
};

