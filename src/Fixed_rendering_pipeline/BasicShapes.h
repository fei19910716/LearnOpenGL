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
        glEnable(GL_POINT_SMOOTH);// 将point变成圆形

        glBegin(GL_POINTS);
        glVertex3f(0.0,0.0,-0.5f);// opengl 使用的是右手坐标系，camera朝向-z，右边为+x，向上为+y
        glVertex3f(0.8,0.0,-0.5f);// 注意坐标范围-1～1，标准设备坐标系
        glEnd();

    }

    // 画三角形
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

    int DrawTriangle(){
        glClearColor(0.0,0.0,0.0,0.3);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        gluPerspective(50.0, 800.0/600.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glLineWidth(4.0f);// 设置线宽

        // front face: CCW 默认正面是逆时针画点的三角形
        glEnable(GL_CULL_FACE);// 剔除背面，如果三角形的三个点是顺时针画的，就会被剔除
        // glFrontFace(GL_CW); // 将顺时针设置为正面

        glPolygonMode(GL_FRONT,GL_LINE); // 线框模式：默认为：GL_FILL

        /*
         * GL_TRIANGLES：每3个点画三角形
         * GL_TRIANGLES_FAN: 每两个点与第一个点连成三角形
         * GL_TRIANGLES_STRIP: 相邻3点画三角形，如果是奇数点：n，n+1，n+2连成三角形；如果是偶数点：n，n-1，n+1连成三角形
         */
        glBegin(GL_TRIANGLES);
        glColor4ub(255,0,0,255); // 设置当前点颜色
        glVertex3f(0.5,0.5,-0.7f);

        glColor4ub(0,255,0,255); // 设置当前点颜色
        glVertex3f(0.0,0.0,-0.5f);

        glColor4ub(0,0,255,255); // 设置当前点颜色
        glVertex3f(0.5,0.0,-0.7f);

        glEnd();
    }
}


#endif //LEARN_OPENGL_DRAWPOINTS_H
