#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
//     vec3 I = normalize(Position - cameraPos); // 计算camera到片元的向量
//     vec3 R = reflect(I, normalize(Normal)); // 计算反射向量
//     FragColor = vec4(texture(skybox, R).rgb, 1.0); // 用反射向量在cubemap上采样

    //折射效果
    float ratio = 1.00 / 1.52; // 空气到玻璃的折射率
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio); // 计算折射光线
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}