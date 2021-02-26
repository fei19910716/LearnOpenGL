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

// 注意，这样实现的反射、折射效果，无法反应环境中的其他物体，如果要实现真实的反射效果，
// 一种办法是使用动态环境映射：即每次渲染立方体之前，先用FBO渲染六个方向，然后生成一个cubemap，然后渲染立方体时，基于该cubemap进行采样；
// 二种方法是使用反射探针：参考https://github.com/tj41694/tinyEngine