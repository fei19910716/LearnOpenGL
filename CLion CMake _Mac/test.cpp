#include <glad/glad.h>// 这个库用于在运行时获取gl函数地址，需要include在顶部
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

namespace TextDemo {
    struct Texture {
        GLuint ImageSize;

        GLuint BitPerPixel;

        GLuint Width;

        GLuint Height;

        GLubyte *Data;
    };
    // C 语言API 读取.tga文件
    GLuint LoadTexture(const char *filename) {

        if (!filename)

            return 0;

        FILE *file = fopen(filename, "r");

        if (file) {
            GLubyte fileheader[12];

            GLubyte Compare[12] = { 0, 0, 2, 0 };

            GLubyte info[6];

            if (fread(fileheader, 1, 12, file) != 12 || memcmp(fileheader, Compare, sizeof(Compare)))

                return 0;

            if (fread(info, 1, 6, file) != 6)

                return 0;

            Texture tex;

            tex.Width = 256 * info[1] + info[0];

            tex.Height = 256 * info[3] + info[2];

            tex.BitPerPixel = info[4];

            GLuint type;

            if (tex.BitPerPixel == 24)

                type = GL_RGB;

            else

                type = GL_RGBA;

            tex.ImageSize = tex.Width * tex.Height * tex.BitPerPixel / 8;

            tex.Data = new GLubyte[tex.ImageSize];

            if (fread(tex.Data, 1, tex.ImageSize, file) != tex.ImageSize) {

                fclose(file);

                delete[] tex.Data;

                return 0;

            }

            fclose(file);

            GLuint TexHandle;
            glGenTextures(1, &TexHandle);

            glBindTexture(GL_TEXTURE_2D, TexHandle);
            if(type == GL_RGB)
                glTexImage2D(GL_TEXTURE_2D, 0, type, tex.Width, tex.Height, 0, GL_BGR, GL_UNSIGNED_BYTE, tex.Data); // B and G should flip
            else if(type == GL_RGBA)
                glTexImage2D(GL_TEXTURE_2D, 0, type, tex.Width, tex.Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, tex.Data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, type, tex.Width, tex.Height, 0, type, GL_UNSIGNED_BYTE, tex.Data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            if (tex.Data)

                free(tex.Data);

            return TexHandle;

        }

        return 0;

    }

    // stb_image API 读取.tga文件
    GLuint LoadTexture_stb(const char *path){
        if (!path)

            return 0;

        std::string filename = std::string(path);

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // stbi_write_png("/Users/fordchen/Desktop/test_tga_out.png", width, height, nrComponents, data, 0);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }




    GLuint make_shader(GLenum type, const char* text) {
        GLuint shader;
        GLint shader_ok;
        GLsizei log_length;
        char info_log[8192];

        shader = glCreateShader(type);
        if (shader != 0) {
            glShaderSource(shader, 1, (const GLchar**)&text, NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
            if (shader_ok != GL_TRUE) {
                std::cout << "ERROR: Failed to compile shader: "
                           << ((type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex") <<std::endl;
                glGetShaderInfoLog(shader, 8192, &log_length, info_log);
                std::cout << "ERROR: " << info_log << std::endl;
                glDeleteShader(shader);
                shader = 0;
            }
        }
        return shader;
    }

    const char* vertex_shader_text =
            "#version 330 core\n"
            "layout(location = 0) in vec2 vPos;\n"
            "layout(location = 1) in vec2 in_texcoord;\n"
            "out vec2 out_texcoord;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(vec2(vPos.x,-vPos.y), 0.0, 1.0);\n"
            "    out_texcoord = in_texcoord;\n"
            "}\n";

    const char* fragment_shader_text =
            "#version 330 core\n"
            "in vec2 out_texcoord;\n"
            "out vec4 color;\n"
            "uniform sampler2D textureImage;\n"
            "void main()\n"
            "{\n"
            "    color = texture(textureImage, out_texcoord);\n"
            //    "    color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "}\n";

    const float vertices[] = {
            1.0f,  1.0f, 1.0f, 1.0f,
            1.0f,  -1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
    };
}

void processInput(GLFWwindow *window);

int main(){

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLuint vertex_shader,fragment_shader,textureImage_location,vao,vbo,textureId;

    vertex_shader = TextDemo::make_shader(GL_VERTEX_SHADER, TextDemo::vertex_shader_text);
    fragment_shader = TextDemo::make_shader(GL_FRAGMENT_SHADER, TextDemo::fragment_shader_text);

    int error = glGetError();
    std::cout << "GL error: " << error<<std::endl;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    GLint program_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (program_ok != GL_TRUE) {
        std::cout << "glGetProgramiv error: " << program_ok << std::endl;
    }

    textureImage_location = glGetUniformLocation(program, "textureImage");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    error = glGetError();
    std::cout << "GL error: " << error << std::endl;

    textureId = TextDemo::LoadTexture_stb("/Users/fordchen/Desktop/test_tga.tga");

    glUseProgram(program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(textureImage_location, 0);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TextDemo::vertices), TextDemo::vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

