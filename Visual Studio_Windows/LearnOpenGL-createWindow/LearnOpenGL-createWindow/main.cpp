#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <gl/GL.h>
#include <gl/GLU.h>

#include "Texture.h"
#include "ObjModel.h"
#include "Utils.h"


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


HDC dc;
WNDCLASSEX wndclass;
HWND hwnd;

// 监听用户操作
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

/*
* 注册 window class
* @param HINSTANCE
*/
bool regiterWindow(HINSTANCE hInstance) {
	// 注册窗口
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom) {
		MessageBox(NULL, L"Register Fail", L"Error", MB_OK);
		return 0;
	}
	return 1;
}

/*
* 创建opengl窗口环境，并显示
* @param HINSTANCE
*/
void createWindow(HINSTANCE hInstance) {
	// 创建确定大小的视口
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	// 创建并显示窗口
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;
	hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW,
		100, 100, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);

	// create the opengl context
	dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc,rc);
	//...

	// opengl code，
	//***********************************注意：透视矩阵需要在这里设置************************************
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

// opengl 渲染场景
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.1, 0.4, 0.6, 1.0);

	glEnable(GL_CULL_FACE);

	// set the mv matrix
	//***********************************注意：透视矩阵不能在这里设置************************************
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// set the light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float blackColor[] = { 0.0,0.0,0.0 };
	float whiteColor[] = { 1.0,1.0,1.0 };
	float lightPosition[] = { 0.0, 0.0, 1.0, 0.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	//*********************************** 灯光向量与normal向量同向时，diffuse 和specular ***********************************
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);// direction, point ,spot light

	float blackMaterial[] = { 0.0,0.0,0.0 };
	float ambientMaterial[] = { 0.1,0.1,0.1 };
	float diffuseMaterial[] = { 0.4	,0.4,0.4 };
	float specularMaterial[] = { 0.9,0.0,0.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);

	// set texture
	Texture texture;
	texture.init("resource\\test.bmp");
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.textureID_);

	ObjModel objModel;
	objModel.init("resource\\Sphere.obj");

	// set the verticex
	glPointSize(10.0f);
	//glPolygonMode(GL_FRONT, GL_LINE);
	//Utils::drawSimpleVertex();
	
	objModel.draw();
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	regiterWindow(hInstance);
	createWindow(hInstance);


	// 让程序持续运行
	MSG msg;
	while (true)
	{
		// window 消息处理
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//draw scene
		drawScene();

		// swap buffer
		SwapBuffers(dc);
	}
	return 0;
}



