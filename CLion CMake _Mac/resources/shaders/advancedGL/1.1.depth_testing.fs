#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1;
float far  = 100.0;

// 计算线性的深度图
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near)); // 投影矩阵的逆变换，回到view坐标系中
}

void main()
{
    //FragColor = texture(texture1, TexCoords); // 纹理采样显示
    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0); // 显示非线性的深度图

    float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
    FragColor = vec4(vec3(depth), 1.0);
}

// view空间经过投影变化后，深度值由near到far区间的线性值变换为了-1 到 1 的非线性值，在near平面需要更高的精度，在far平面需要较少的精度
// 深度缓冲区一般是24位的，可以通过提高深度缓冲区精度优化far平面精度低导致的深度冲突问题