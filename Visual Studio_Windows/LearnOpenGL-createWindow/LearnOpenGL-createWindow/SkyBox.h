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
	* 加载天空盒的6张图片并生成纹理
	*/
	void load(const std::string imagePath);
	/*
	* 绘制6个平面构成天空盒
	* @param: camera的position_，让天空盒跟着camera运动，实现无法逃逸的效果
	*/
	void draw(float x, float y, float z);
	/*
	* 存储天空盒6张纹理
	*/
	std::shared_ptr<Texture> front_, back_, left_, right_, top_, bottom_;

};

