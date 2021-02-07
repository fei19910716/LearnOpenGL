//
// Created by FordChen on 2021/2/3.
//

#ifndef LEARN_OPENGL_MATRIXOPERATION_H
#define LEARN_OPENGL_MATRIXOPERATION_H

namespace FixedRenderingPipeline{
    /*
     * 这里需要注意，矩阵变换是改变的坐标系还是改变的物体，如果是动坐标系，应该使用矩阵右乘；如果是静态坐标系，应该使用矩阵左乘。
     */
    void MatrixOperation(){
        glClearColor(0.0,0.0,0.0,0.3);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        gluPerspective(50.0, 800.0/600.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glLineWidth(4.0f);                  // 设置线宽

        glPushMatrix();                     // 暂存当前矩形1
        glScalef(0.5,0.5,0.5);              // 缩放的是坐标的大小，而不是形状
        glRotatef(90.f,0.0,0.0,1.0f);       // 绕z轴旋转10度
        glTranslatef(-1.5f,0.0f,0.0f);      // x轴进行平移

        glPushMatrix();                     // 暂存当前矩形2
        glRotatef(90.f,0.0,0.0,1.0);        // 叠加旋转，继续转90度

        glBegin(GL_TRIANGLES);
        glColor4ub(255,0,0,255);            // 设置当前点颜色
        glVertex3f(0.0,0.5,-0.7f);

        glColor4ub(0,255,0,255);            // 设置当前点颜色
        glVertex3f(0.0,0.0,-0.5f);

        glColor4ub(0,0,255,255);             // 设置当前点颜色
        glVertex3f(0.5,0.0,-0.7f);

        glPopMatrix();                      // 恢复到矩形2
        glPopMatrix();                      // 恢复到矩形1

        glEnd();
    }
}

#endif //LEARN_OPENGL_MATRIXOPERATION_H
