#include "Texture.h"
#include "Utils.h"

/*
* ����һ��ͼƬ��·����ͨ����ͼƬ����opengl����
*/
void Texture::init(const std::string imagePath)
{
	// load image form disk to memory
	unsigned char* content = Utils::loadFileContent(imagePath);

	//decode image
	int width, height;
	unsigned char* pixelData = Utils::decodeBMP(content, width, height);

	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//�������ݴ�cpu����gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete content;
}
