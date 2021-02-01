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

        glMatrixMode(GL_PROJECTION_MATRIX);
        gluPerspective(50.0, 480.0/640.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor4ub(255,255,255,255);
        glPointSize(20.0f);

        glBegin(GL_POINTS);
        glVertex3f(0.0,0.0,-0.5f);
        glVertex3f(0.8,0.0,-0.5f);
        glEnd();

    }

    // 画线
    int DrawLine(){
        glClearColor(0.3,0.0,0.0,0.3);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        gluPerspective(50.0, 480.0/640.0,0.1,1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor4ub(255,255,255,255);


        glBegin(GL_LINE);
        glVertex3f(0.0,0.0,-0.5f);
        glVertex3f(0.4,0.0,-0.5f);
        glEnd();
    }
}


#endif //LEARN_OPENGL_DRAWPOINTS_H
