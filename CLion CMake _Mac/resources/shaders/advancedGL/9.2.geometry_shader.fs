#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1; // model.h 解析模型代码中让我们命名按照texture_diffuse1 texture_diffuse2 texture_diffuse3这种方式进行

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}
