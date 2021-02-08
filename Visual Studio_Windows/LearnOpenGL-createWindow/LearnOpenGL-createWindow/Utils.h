#pragma once

#include <iostream>
#include <string>

namespace Utils {
	/*
	* 通用的文件字节流读取函数
	*/
	unsigned char* loadFileContent(const std::string imagePath);
	/*
	* 解码bmp文件的字节流数据
	*/
	unsigned char* decodeBMP(unsigned char* bpmData, int& width, int& height);

	/*
	* 自己指定顶点数据进行绘图（学习obj模型加载后不再使用）
	*/
	void drawSimpleVertex();
}

