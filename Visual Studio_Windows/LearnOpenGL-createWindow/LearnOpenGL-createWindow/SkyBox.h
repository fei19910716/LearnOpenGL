#pragma once

#include <string>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Texture.h"
#include <memory>

class SkyBox
{
public:
	/*
	* ������պе�6��ͼƬ����������
	*/
	void load(const std::string imagePath);
	/*
	* ����6��ƽ�湹����պ�
	* @param: camera��position_������պи���camera�˶���ʵ���޷����ݵ�Ч��
	*/
	void draw(float x, float y, float z);
	/*
	* �洢��պ�6������
	*/
	std::shared_ptr<Texture> front_, back_, left_, right_, top_, bottom_;

};

