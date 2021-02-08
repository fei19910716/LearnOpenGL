#pragma once

#include <memory>
#include <vector>

/*
* 每个顶点包含的信息
*/
struct VertexData
{
	float position[3];		 // 位置
	float normal[3];		 // 法线
	float textureCoord[2];   // 纹理坐标
};

/*
* 用于加载obj模型的类
*/
class ObjModel
{
public:
	/*
	* 根据obj模型文件的path加载并解析
	*/
	void load(const char* objModel);

	/*
	* 调用opengl 进行绘制obj模型
	*/
	void draw(); // 绘制obj模型

	/*
	* 存储解析后的所有顶点数据
	*/
	std::vector<std::shared_ptr<VertexData>> mVertexes;
	/*
	* 存储解析后构成一个三角形的三个顶点的索引
	*/
	std::vector<unsigned short> mIndexes;
	/*
	* 存储mIndexes的size()
	*/
	int mIndexCount;
};

