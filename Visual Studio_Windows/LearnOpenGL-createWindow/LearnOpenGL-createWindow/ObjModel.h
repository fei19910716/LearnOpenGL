#pragma once

#include <memory>
#include <vector>

/*
* ÿ�������������Ϣ
*/
struct VertexData
{
	float position[3];		 // λ��
	float normal[3];		 // ����
	float textureCoord[2];   // ��������
};

/*
* ���ڼ���objģ�͵���
*/
class ObjModel
{
public:
	/*
	* ����objģ���ļ���path���ز�����
	*/
	void load(const char* objModel);

	/*
	* ����opengl ���л���objģ��
	*/
	void draw(); // ����objģ��

	/*
	* �洢����������ж�������
	*/
	std::vector<std::shared_ptr<VertexData>> mVertexes;
	/*
	* �洢�����󹹳�һ�������ε��������������
	*/
	std::vector<unsigned short> mIndexes;
	/*
	* �洢mIndexes��size()
	*/
	int mIndexCount;
};

