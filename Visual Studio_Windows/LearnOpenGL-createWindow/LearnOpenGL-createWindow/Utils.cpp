#include "Utils.h"
#include "Texture.h"

#include <Windows.h>
#include <gl/GL.h>
#include <iostream>
#include <vector>
#include <sstream>

/*
* 可以读任意文件,在main函数中 如果要输出到console ，需要在属性窗口生成事件中添加：editbin /subsystem:console $(OutDir)$(ProjectName).exe
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
* 解码bmp图像数据
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
    //***********************************注意：透视矩阵不能在这里设置************************************
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(45, 1.0, 0.0, 0.0);

    // set texture
    Texture texture;
    texture.init("resource\\test.bmp");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.textureID_);

    glBegin(GL_TRIANGLES);
    // 用自己的顶点数据
    /*glColor4ub(255, 0, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -1.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 0.0); // 左下
    /*glColor4ub(0, 0, 255, 255);*/ glVertex3f(0.5f, -0.25f, -1.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 0.0); // 右下
    /*glColor4ub(0, 255, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -4.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 1.0); // 左上


    /*glColor4ub(0, 0, 255, 255);*/ glVertex3f(0.5f, -0.25f, -1.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 0.0); // 右下
    /*glColor4ub(0, 255, 0, 255);*/ glVertex3f(0.5f, -0.25f, -4.0f);  glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(1.0, 1.0); // 右上
    /*glColor4ub(255, 0, 0, 255);*/ glVertex3f(-0.5f, -0.25f, -4.0f); glNormal3f(0.0, 1.0, 0.0);  glTexCoord2f(0.0, 1.0); // 左上
    glEnd();
}
