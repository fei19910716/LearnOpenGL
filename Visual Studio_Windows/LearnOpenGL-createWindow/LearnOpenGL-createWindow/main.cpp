#include <windows.h>
#include <tchar.h>
#include <iostream>

#include <gl/GL.h>
#include <gl/GLU.h>

#include "Texture.h"
#include "ObjModel.h"
#include "Utils.h"
#include "Camera.h"
#include "SkyBox.h"


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"Winmm.lib")


HDC dc;
WNDCLASSEX wndclass;
HWND hwnd;
/*
* 场景摄像机
*/
Camera camera;
/*
* 鼠标点击运动时的初始鼠标位置
*/
POINT orignalMousePosition;
/*
* bool值，控制鼠标运动
*/
bool bRotateByMouse = false;

static float timeSinceStart = 0.0f;

// 监听用户操作
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN: // 按“下”键
		switch (wParam)
		{
			case 'A':
				camera.moveLeft_ = true;
				break;
			case 'D':
				camera.moveRight_ = true;
				break;
			case 'W':
				camera.moveForward_ = true;
				break;
			case 'S':
				camera.moveBack_ = true;
				break;
			default:
				break;
		}
		return 0;;
	case WM_KEYUP:
		switch (wParam)
		{
			case 'A':
				camera.moveLeft_ = false;
				break;
			case 'D':
				camera.moveRight_ = false;
				break;
			case 'W':
				camera.moveForward_ = false;
				break;
			case 'S':
				camera.moveBack_ = false;
				break;
			default:
				break;
		}
		return 0;
	case WM_RBUTTONDOWN: // 鼠标右键按下
		bRotateByMouse = true;
		orignalMousePosition.x = LOWORD(lParam);
		orignalMousePosition.y = HIWORD(lParam);
		ClientToScreen(hwnd, &orignalMousePosition); // 坐标转换，统一为屏幕坐标
		SetCapture(hwnd);
		ShowCursor(false);
		return 0;
	case WM_RBUTTONUP:
		bRotateByMouse = false;
		ReleaseCapture();
		SetCursorPos(orignalMousePosition.x, orignalMousePosition.y); // 鼠标需要重新显示在初始位置
		ShowCursor(true);
		return 0;
	case WM_MOUSEMOVE:
		if (bRotateByMouse) {
			POINT currentPos;
			currentPos.x = LOWORD(lParam);
			currentPos.y = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPos);
			float deltaX = currentPos.x - orignalMousePosition.x;
			float deltaY = currentPos.y - orignalMousePosition.y;
			camera.pitch(deltaY / 1000.0f);
			camera.yaw(deltaX / 1000.0f);
		}
		return 0;
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

/*
* 绘制场景
*/
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.3f, 0.8f, 1.0f);

	float currentTime = timeGetTime() / 1000.0f;
	float deltaTime = currentTime - timeSinceStart;
	timeSinceStart = currentTime;
	camera.update(deltaTime);

	//draw scene
	SkyBox skybox;
	skybox.load("resource\\skybox\\");
	skybox.draw(camera.position_.x, camera.position_.y, camera.position_.z);


	ObjModel objModel;
	objModel.load("resource\\Sphere.obj");
	objModel.draw();
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// 对窗口程序启动控制台输出，方便调试
	AllocConsole();freopen("CONOUT$", "r+", stdout);

	regiterWindow(hInstance);
	createWindow(hInstance);

	timeSinceStart = timeGetTime() / 1000.0f;

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



