//
// Created by FordChen on 2021/2/1.
//

#include <GLFW/glfw3.h>
#include <GLUT/glut.h>

#ifndef LEARN_OPENGL_DRAWPOINTS_H
#define LEARN_OPENGL_DRAWPOINTS_H

/*
 * 固定渲染管线
 */
namespace FixedRenderingPipeline{

    // 画points
    int DrawPoints(){
        glClearColor(0.3,0.0,0.0,0.3);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX); // 设置投影矩阵
        gluPerspective(50.0, 800.0/600.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW); // 设置modelView矩阵
        glLoadIdentity();

        glColor4ub(255,255,255,255); // 设置点的颜色
        glPointSize(20.0f);

        glBegin(GL_POINTS);
        glVertex3f(0.0,0.0,-0.5f);// opengl 使用的是右手坐标系，camera朝向-z，右边为+x，向上为+y
        glVertex3f(0.8,0.0,-0.5f);// 注意坐标范围-1～1，标准设备坐标系
        glEnd();

    }

    // 画线
    int DrawLine(){
        glClearColor(0.0,0.0,0.0,0.3);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        gluPerspective(50.0, 800.0/600.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glLineWidth(4.0f);// 设置线宽

        /*
         * GL_LINES：每两个点画线
         * GL_LINE_LOOP: 收尾点相连，闭合曲线
         * GL_LINE_STRIP: 相邻两点画线，收尾不相连
         */
        glBegin(GL_LINE_STRIP);
        glColor4ub(255,0,0,255); // 设置当前点颜色
        glVertex3f(0.5,0.5,-0.7f);
        glColor4ub(0,255,0,255); // 设置当前点颜色
        glVertex3f(0.0,0.0,-0.5f);

        glVertex3f(0.5,0.0,-0.7f);
        glEnd();
    }
}


#endif //LEARN_OPENGL_DRAWPOINTS_H
