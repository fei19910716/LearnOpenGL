#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(Position - cameraPos); // 计算camera到片元的向量
    vec3 R = reflect(I, normalize(Normal)); // 计算反射向量
    FragColor = vec4(texture(skybox, R).rgb, 1.0); // 用反射向量在cubemap上采样
}