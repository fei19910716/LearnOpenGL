//
// Created by FordChen on 2021/3/16.
//
#include <glad/glad.h>// 这个库用于在运行时获取gl函数地址，需要include在顶部
#include <GLFW/glfw3.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

#include <iostream>
#include <string>

#ifndef LEARN_OPENGL_UTILS_H
#define LEARN_OPENGL_UTILS_H

namespace UTILS {

    //! write the texture to file
    void writeTexturePNG(const std::string &path, int width, int height, GLuint textureID, GLuint format = GL_RGBA) {
//! 1st: directly use glGetTexImage() to save texture data to file
        unsigned char *data = new unsigned char[width * height]; // depth texture only has 1 chanel
        glBindTexture(GL_TEXTURE_2D, textureID);
        glGetTexImage(GL_TEXTURE_2D,0,format,GL_UNSIGNED_BYTE,data);
        stbi_write_png(path.c_str(), width, height, 1, data, 0);// depth texture only has 1 chanel


//! 2st: use glReadPixels() to transfer the bind fbo texture data to file
//        GLuint fbo;
//        glGenFramebuffers(1, &fbo);
//        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureID, 0);
//        unsigned char * data = new unsigned char[width*height];
//        // transfer the bind fbo image data, here is the texture data
//        glReadPixels(0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
//        stbi_write_png(path.c_str(),width,height,1,data,0);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        glDeleteFramebuffers(1, &fbo);

    }

    //! write the render result to file
    void writeResultPNG(const std::string &path, int width, int height, GLuint format = GL_RGBA){

        unsigned char * data = new unsigned char[width*height*4];
        // transfer the bind fbo image data, here is the opengl result data
        glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,data);
        stbi_write_png(path.c_str(),width,height,4,data,0);
    }

}

#endif //LEARN_OPENGL_UTILS_H
