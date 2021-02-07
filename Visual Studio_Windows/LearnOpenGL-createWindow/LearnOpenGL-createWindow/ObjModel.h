#pragma once

struct VertexData
{
	float position[3];
	float normal[3];
	float textureCoord[2];
};

class ObjModel
{
public:

	void init(const char* objModel);

	void draw();

	VertexData* mVertexes;
	unsigned short* mIndexes;
	int mIndexCount;

};

