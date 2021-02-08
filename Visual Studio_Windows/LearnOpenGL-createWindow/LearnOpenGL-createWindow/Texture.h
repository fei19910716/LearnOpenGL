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
	* ����ͼƬ·�����ز���������Ϊopengl������
	*/
	void init(const std::string imagePath);

	/*
	* ʹ��������SOIL����ͼƬ����opengl����
	*/
	void initWithSOIL(const std::string imagePath, bool flip_y = false);

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

