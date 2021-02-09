#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <unordered_map>
#include <memory>

/*
* 不使用glew的话，GL_CLAMP_TO_EDGE宏未定义，可以自己定义
*/
#define GL_CLAMP_TO_EDGE 0x812F

class Texture
{
public:
	/*
	* 根据图片路径加载并解析生成为opengl的纹理
	*/
	void init(const std::string imagePath);

	/*
	* 使用三方库SOIL加载图片生成opengl纹理
	*/
	void initWithSOIL(const std::string imagePath, bool flip_y = false, unsigned int wrapMode = GL_CLAMP_TO_EDGE);

	/*
	* opengl纹理的id
	*/
	GLuint  textureID_;
	/*
	* 纹理的路径，将作为缓存texture_map_的key
	*/
	std::string path_;
	/*
	* 存储所有加载过的texture，避免重复加载
	*/
	static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_map_;
	/*
	* 根据传入的图片路径调用SOIL生成opengl纹理并缓存起来
	*/
	static std::shared_ptr<Texture> createTexture(const std::string imagePath, bool flip_y = false);
	/*
	* 删除缓存中的texture，并删除GPU中的纹理显存
	*/
	static void removeTexture(std::shared_ptr<Texture> texture);
};

