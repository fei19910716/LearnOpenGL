#pragma once

#include <iostream>
#include <string>

namespace Utils {
	/*
	* ͨ�õ��ļ��ֽ�����ȡ����
	*/
	unsigned char* loadFileContent(const std::string imagePath);
	/*
	* ����bmp�ļ����ֽ�������
	*/
	unsigned char* decodeBMP(unsigned char* bpmData, int& width, int& height);

	/*
	* �Լ�ָ���������ݽ��л�ͼ��ѧϰobjģ�ͼ��غ���ʹ�ã�
	*/
	void drawSimpleVertex();
}

