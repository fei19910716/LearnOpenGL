#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <unordered_map>
#include <memory>

/*
* ��ʹ��glew�Ļ���GL_CLAMP_TO_EDGE��δ���壬�����Լ�����
*/
#define GL_CLAMP_TO_EDGE 0x812F

class Texture
{
public:
	/*
	* ����ͼƬ·�����ز���������Ϊopengl������
	*/
	void init(const std::string imagePath);

	/*
	* ʹ��������SOIL����ͼƬ����opengl����
	*/
	void initWithSOIL(const std::string imagePath, bool flip_y = false, unsigned int wrapMode = GL_CLAMP_TO_EDGE);

	/*
	* opengl�����id
	*/
	GLuint  textureID_;
	/*
	* �����·��������Ϊ����texture_map_��key
	*/
	std::string path_;
	/*
	* �洢���м��ع���texture�������ظ�����
	*/
	static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_map_;
	/*
	* ���ݴ����ͼƬ·������SOIL����opengl������������
	*/
	static std::shared_ptr<Texture> createTexture(const std::string imagePath, bool flip_y = false);
	/*
	* ɾ�������е�texture����ɾ��GPU�е������Դ�
	*/
	static void removeTexture(std::shared_ptr<Texture> texture);
};

