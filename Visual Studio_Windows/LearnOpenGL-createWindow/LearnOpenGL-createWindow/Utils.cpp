#include "Utils.h"
#include "Texture.h"

#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include <vector>
#include <sstream>

/*
* ���Զ������ļ�,��main������ ���Ҫ�����console ����Ҫ�����Դ��������¼�����ӣ�editbin /subsystem:console $(OutDir)$(ProjectName).exe
*/
unsigned char* Utils::loadFileContent(const std::string imagePath)
{
    unsigned char* content = nullptr;
    FILE* file = fopen(imagePath.c_str(), "rb");
    if (file) {
        //read
        fseek(file, 0, SEEK_END);
        int len = ftell(file);
        if (len) {
            rewind(file);
            content = new unsigned char[len + 1];
            fread(content, sizeof(unsigned char), len, file);
            content[len] = '\0';
            fclose(file); 
        }
    }
    return content;
}

/*
* ����bmpͼ������
*/
unsigned char* Utils::decodeBMP(unsigned char* bpmData, int& width, int& height)
{
    if (0x4D42 == *((unsigned short*)bpmData)) {
        int pixelDataOffset = *((int*)(bpmData+10));
        width = *((int*)(bpmData + 18));
        height = *((int*)(bpmData + 22));
        unsigned char* pixelData = bpmData + pixelDataOffset;
        // bgr -> rgb
        for (size_t i = 0; i < width* height * 3; i+=3)
        {
            unsigned char temp = pixelData[i];
            pixelData[i] = pixelData[i + 2];
            pixelData[i + 2] = temp;
        }
        return pixelData;
    }
    else {
        return nullptr;
    }
}

void Utils::drawSimpleVertex()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1, 0.4, 0.6, 1.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // set the mv matrix
    //***********************************ע�⣺͸�Ӿ���������������************************************
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(45, 1.0, 0.0, 0.0);

    // set texture
    Texture texture;
    texture.init("resource\\test.bmp");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.textureID_);

    glBegin(GL_TRIANGLES);
    // ���Լ��Ķ�������
    /*glColor4ub(255, 0, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -1.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 0.0); // ����
    /*glColor4ub(0, 0, 255, 255);*/ glVertex3f(0.5f, -0.25f, -1.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 0.0); // ����
    /*glColor4ub(0, 255, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -4.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 1.0); // ����


    /*glColor4ub(0, 0, 255, 255);*/ glVertex3f(0.5f, -0.25f, -1.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 0.0); // ����
    /*glColor4ub(0, 255, 0, 255);*/ glVertex3f(0.5f, -0.25f, -4.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 1.0); // ����
    /*glColor4ub(255, 0, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -4.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 1.0); // ����
    glEnd();
}
