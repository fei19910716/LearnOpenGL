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
* ���������
*/
Camera camera;
/*
* ������˶�ʱ�ĳ�ʼ���λ��
*/
POINT orignalMousePosition;
/*
* boolֵ����������˶�
*/
bool bRotateByMouse = false;

static float timeSinceStart = 0.0f;

// �����û�����
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN: // �����¡���
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
	case WM_RBUTTONDOWN: // ����Ҽ�����
		bRotateByMouse = true;
		orignalMousePosition.x = LOWORD(lParam);
		orignalMousePosition.y = HIWORD(lParam);
		ClientToScreen(hwnd, &orignalMousePosition); // ����ת����ͳһΪ��Ļ����
		SetCapture(hwnd);
		ShowCursor(false);
		return 0;
	case WM_RBUTTONUP:
		bRotateByMouse = false;
		ReleaseCapture();
		SetCursorPos(orignalMousePosition.x, orignalMousePosition.y); // �����Ҫ������ʾ�ڳ�ʼλ��
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
* ע�� window class
* @param HINSTANCE
*/
bool regiterWindow(HINSTANCE hInstance) {
	// ע�ᴰ��
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
* ����opengl���ڻ���������ʾ
* @param HINSTANCE
*/
void createWindow(HINSTANCE hInstance) {
	// ����ȷ����С���ӿ�
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	// ��������ʾ����
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

	// opengl code��
	//***********************************ע�⣺͸�Ӿ�����Ҫ����������************************************
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

/*
* ���Ƴ���
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
	// �Դ��ڳ�����������̨������������
	AllocConsole();freopen("CONOUT$", "r+", stdout);

	regiterWindow(hInstance);
	createWindow(hInstance);

	timeSinceStart = timeGetTime() / 1000.0f;

	// �ó����������
	MSG msg;
	while (true)
	{
		// window ��Ϣ����
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



