#include "ObjModel.h"
#include "Utils.h"
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <gl/GL.h>

/*
* ½âÂëobjÄ£ÐÍ
*/
void ObjModel::init(const char* objModel)
{
	struct FloatData {
		float v[3];
	};
	struct VertexDefine {
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	unsigned char* fileContent = Utils::loadFileContent(objModel);
	if (fileContent == nullptr) {
		return;
	}

	int nFileSize = 0;

	std::vector<FloatData> positions, texcoords, normals;
	std::vector<VertexDefine> vertexes;
	std::vector<int> indexes;
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof()) {
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0) {
			if (szOneLine[0] == 'v') {
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't') {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}
			else if (szOneLine[0] == 'f') {
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				for (int i = 0; i < 3; i++) {
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VertexDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexes.size();
					for (int j = 0; j < nCurrentVertexCount; ++j) {
						if (vertexes[j].posIndex == vd.posIndex &&
							vertexes[j].normalIndex == vd.normalIndex &&
							vertexes[j].texcoordIndex == vd.texcoordIndex) {
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1) {
						nCurrentVertexIndex = (int)vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
			}
		}
	}
	mIndexCount = (int)indexes.size();
	mIndexes = new unsigned short[mIndexCount];
	for (int i = 0; i < mIndexCount; ++i) {
		mIndexes[i] = indexes[i];
	}
	int vertexCount = (int)vertexes.size();
	mVertexes = new VertexData[vertexCount];
	for (int i = 0; i < vertexCount; ++i) {
		memcpy(mVertexes[i].position, positions[vertexes[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].textureCoord, texcoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}
	delete fileContent;
}

void ObjModel::draw()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < mIndexCount; i++)
	{
		glVertex3fv(mVertexes[mIndexes[i]].position);
		glNormal3fv(mVertexes[mIndexes[i]].normal);
		glTexCoord2fv(mVertexes[mIndexes[i]].textureCoord);
	}
	glEnd();
}
