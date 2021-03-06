#include "Texture.h"
#include "Utils.h"
#include "soil.h"

#pragma comment(lib,"soil.lib")

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::texture_map_;

/*
* 传入一张图片的路径，通过该图片生成opengl纹理
*/
void Texture::init(const std::string imagePath)
{
	path_ = imagePath;
	// load image form disk to memory
	unsigned char* content = Utils::loadFileContent(imagePath);

	//decode image
	int width, height;
	unsigned char* pixelData = Utils::decodeBMP(content, width, height);

	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//纹理数据从cpu传到gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete content;
}

void Texture::initWithSOIL(const std::string imagePath, bool flip_y, unsigned int wrapMode)
{
	path_ = imagePath;
	if (flip_y) {
		textureID_ = SOIL_load_OGL_texture(imagePath.c_str(), 0, 0, SOIL_FLAG_INVERT_Y | SOIL_FLAG_POWER_OF_TWO);
	}
	else {
		textureID_ = SOIL_load_OGL_texture(imagePath.c_str(), 0, 0, SOIL_FLAG_POWER_OF_TWO);
	}
	// SOIL_load_OGL_texture无法指定wrapMode,所以通过传入形参来判断
	if (wrapMode == GL_CLAMP_TO_EDGE) {
		glBindTexture(GL_TEXTURE_2D, textureID_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

std::shared_ptr<Texture> Texture::createTexture(const std::string imagePath, bool flip_y)
{
	if (texture_map_.find(imagePath) != texture_map_.end()) {
		return texture_map_[imagePath];
	}
	auto texture = std::make_shared<Texture>();
	texture->initWithSOIL(imagePath,flip_y);
	texture_map_.insert(std::pair <std::string, std::shared_ptr<Texture>>(imagePath, texture));
	return texture;
}

void Texture::removeTexture(std::shared_ptr<Texture> texture)
{
	auto iter = texture_map_.find(texture->path_);
	if (iter != texture_map_.end()) {
		texture_map_.erase(iter);
		glDeleteTextures(1, &iter->second->textureID_);
	}
}
