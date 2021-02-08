#include "ObjModel.h"
#include "Utils.h"
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include "Texture.h"

/*
* 解码obj文件
*/
void ObjModel::load(const char* objModel)
{
	struct FloatData {
		float v[3];
	};
	struct VertexDataIndexs {
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};

	unsigned char* fileContent = Utils::loadFileContent(objModel);
	if (fileContent == nullptr) {
		return;
	}

	int nFileSize = 0;

	std::vector<FloatData> positionDatas, texcoordDatas, normaDatals;
	std::vector<VertexDataIndexs> vertexDataIndexs;
	std::vector<int> indexes_vector;
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
					texcoordDatas.push_back(floatData);
					printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n') {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normaDatals.push_back(floatData);
					printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positionDatas.push_back(floatData);
					printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}
			else if (szOneLine[0] == 'f') {
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				for (int i = 0; i < 3; i++) {
					ssOneLine >> vertexStr; // "1/2/3"
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VertexDataIndexs vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int)vertexDataIndexs.size();
					for (int j = 0; j < nCurrentVertexCount; ++j) {
						if (vertexDataIndexs[j].posIndex == vd.posIndex &&
							vertexDataIndexs[j].normalIndex == vd.normalIndex &&
							vertexDataIndexs[j].texcoordIndex == vd.texcoordIndex) {
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1) {
						nCurrentVertexIndex = (int)vertexDataIndexs.size();
						vertexDataIndexs.push_back(vd);
					}
					indexes_vector.push_back(nCurrentVertexIndex);
				}
			}
		}
	}
	// copy the data to the class member
	mIndexCount = (int)indexes_vector.size();
	mIndexes.resize(mIndexCount);
	for (int i = 0; i < mIndexCount; ++i) {
		mIndexes[i] = indexes_vector[i];
	}
	int vertexCount = (int)vertexDataIndexs.size();
	
	for (int i = 0; i < vertexCount; ++i) {
		mVertexes.push_back(std::make_shared<VertexData>());
		memcpy(mVertexes[i]->position, positionDatas[vertexDataIndexs[i].posIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i]->textureCoord, texcoordDatas[vertexDataIndexs[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i]->normal, normaDatals[vertexDataIndexs[i].normalIndex - 1].v, sizeof(float) * 3);
	}
	delete fileContent;
}

void ObjModel::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.4, 0.6, 1.0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// set the mv matrix
	//***********************************注意：透视矩阵不能在这里设置************************************
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);

	static float angle = 0.0f;
	angle += 1.0f;
	if (angle > 360.0f) angle = 0.0;
	glRotatef(angle, 0.0, 1.0, 0.0);


	// set the light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float blackColor[] = { 0.0,0.0,0.0 };
	float whiteColor[] = { 1.0,1.0,1.0 };
	float lightPosition[] = { 0.0, 1.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	//*********************************** 灯光向量与normal向量同向时，diffuse 和specular效果最强 ***********************************
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);// direction, point ,spot light

	float blackMaterial[] = { 0.0,0.0,0.0 };
	float ambientMaterial[] = { 0.1,0.1,0.1 };
	float diffuseMaterial[] = { 0.4	,0.4,0.4 };
	float specularMaterial[] = { 0.9,0.9,0.9 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, 60.0f); // 设置高光的系数

	// set texture
	auto texture = Texture::textureCreate("resource\\earth.bmp",true);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->textureID_);

	
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < mIndexCount; i++)
	{
		glVertex3fv(mVertexes[mIndexes[i]]->position);
		glNormal3fv(mVertexes[mIndexes[i]]->normal);
		glTexCoord2fv(mVertexes[mIndexes[i]]->textureCoord);
	}
	glEnd();
	glPopMatrix();
}
