#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));  // 统一在世界空间进行计算
    Normal = mat3(transpose(inverse(model))) * aNormal; // 解决模型在xyz方向上不等比缩放后的法线问题，使得法线的指向正确

    gl_Position = projection * view * vec4(FragPos, 1.0);
}