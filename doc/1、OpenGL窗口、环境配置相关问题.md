@[TOC](目录)
## 1、使用Qt库跨平台配置OpenGL环境<br/>
在Qt中搭建OpenGL环境非常方便，只需要继承QOpenGLWidget就可以了，然后重载三个虚函数即可。<br/>
virtual void initializeGL() ；<br/>
virtual void	paintGL() ；<br/>
virtual void	resizeGL(int w, int h)；<br/>

```cpp
class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        ...
    }

    void resizeGL(int w, int h) override
    {
        // Update projection matrix and other size related settings:
        m_projection.setToIdentity();
        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
        ...
    }

    void paintGL() override
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);
        ...
    }

};
```



## 2、使用GLFW库在Windows上配置OpenGL环境
首先，去GLFW的官网下载预编译的库 <https://www.glfw.org/download.html>。当然也可以下载源码自己用CMake编译。<br/>
下载之后的文件夹如下：<br/>
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021020113205147.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY4NDMxMw==,size_16,color_FFFFFF,t_70)<br/>
只需要将上述的include里面的头文件，以及对应库文件夹中的库文件配置到VS中的项目属性窗口即可。

## 3、使用GLFW库在Mac上用CMake配置OpenGL环境
首先，去GLFW的官网下载源码或者预编译的库 <https://www.glfw.org/download.html>。<br/>
下面使用预编译库，利用CLion使用CMake进行配置：<br/>
	

```cpp
// 设置版本及项目名
cmake_minimum_required(VERSION 3.16)
project(Learn_OpenGL)
set(target Learn_OpenGL)

// CMake引入预编译的静态库libglfw3.a
ADD_LIBRARY(glfw3 STATIC IMPORTED)
SET_TARGET_PROPERTIES(glfw3 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/glfw/lib/libglfw3.a)

// 定义变量
set(CMAKE_CXX_STANDARD 11)
set(GLFW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
// set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c") //如果要使用glad需要加上

// 头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${GLFW_SOURCE_DIR}/include)
// include_directories(${GLFW_SOURCE_DIR}/deps) //如果要使用glad需要加上

// 源文件路径
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src TOOL_SRC)

// 生成可执行程序
add_executable(${target}
        //${GLAD_GL}
        ${TOOL_SRC}
        main.cpp
        )
        
// 链接依赖库
// 根据GLFW的官网可知，在Mac上GLFW创建OpenGL窗口上下文依赖于OpenGL、Cocoa、IOKit三个库，需要引入进来，否则编译报错
find_library(OpenGL_LIBRARY OpenGL )
find_library(Cocoa_LIBRARY Cocoa )
find_library(IOKit_LIBRARY IOKit )
target_link_libraries(${target}  ${OpenGL_LIBRARY} ${Cocoa_LIBRARY} ${IOKit_LIBRARY} glfw3)

// 设置exe输出目录
set(custom_output_dir ${CMAKE_CURRENT_BINARY_DIR}/bin/)
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${custom_output_dir})
set_target_properties(${target} PROPERTIES LINK_FLAGS_RELEASE -s)
```
然后就可以创建main.cpp开始写程序了
	

```cpp
#include <GLFW/glfw3.h>

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    return 0;
}
```

## 4、使用Window.h原生窗口配置OpenGL环境
要注意需要确保：项目->链接器->系统->子系统中要选用窗口而不是控制台
```cpp
#include <windows.h>
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
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // 注册窗口
	WNDCLASSEX wndclass;
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
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW,
		100, 100, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	// 让程序持续运行
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}
```

## 5、使用CMake编译Qt项目
这里介绍在Mac下的方法：
1.首先下载Qt库，由于QT官网下载较慢，建议使用镜像网站下载：https://mirrors.tuna.tsinghua.edu.cn/qt/archive/qt/5.13/5.13.0/
2.下载其中的mac版本dmg文件进行安装，建议所有模块都选上（尤其是里面的WebEngine模块一定要选上）
`注意：`如果编译报错找不到 WebEngine，请尝试运行 Qt 安装目录中的maintenance tool ，添加 QtWebEngine module，还不行就只能重新安装Qt）
```cpp
// 设置版本及项目名
cmake_minimum_required(VERSION 3.16)
project(LearnOpenCV)

// 设置变量
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
/*
 *这里可以创建符号链接，将Qt库链接到自己的项目目录中，方便查看
 *在project的目录下将Qt 5.13.0 添加符号链接到 父目录 Qt 文件夹。
 	例如：ln -s /Users/xxx/xxx/Qt5.13.0 ../Qt, cmake 中指向的位置为 ../Qt/5.13.0/clang_64/lib/cmake
	注意：/Users/xxx/Qt5.13.0 为个人电脑上面的Qt的安装文件夹，例如 ln -s /Users/xxx/xxx/Qt5.13.0 /Users/xxx/project/Qt
*/
set(QT_LOCAL_PATH ./Qt/5.13.0) #需要填入自己安装的路径，这里设置为软链接Qt目录
set(CMAKE_PREFIX_PATH ${QT_LOCAL_PATH}/clang_64/lib/cmake) #mac下用clang编译器

// 添加Qt模块
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5WebEngine REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5 COMPONENTS Svg REQUIRED)

// 头文件目录
include_directories(${QT_LOCAL_PATH}/clang_64/include) //Qt头文件

// 源文件
file(GLOB SOURCE_FILES *.cpp *.h *.hpp *.c src/*.*)

/*
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment version" FORCE)
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(DEPLOYQT_EXECUTABLE NAMES windeployqt macdeployqt HINTS "${_qt_bin_dir}")
*/
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIwONS} ${${Qt5Quick_DEFINITIONS}})
// qt5_add_resources(QT_RESOURCES assets/main.qrc)

// 生成exe
add_executable(LearnOpenCV ${SOURCE_FILES})

// 链接库
target_link_libraries(LearnOpenCV Qt5::Widgets Qt5::OpenGL Qt5::Core Qt5::Gui Qt5::Qml  Qt5::Quick Qt5::QuickControls2 Qt5::Multimedia Qt5::WebEngine Qt5::Svg Qt5::Concurrent)
qt5_use_modules(LearnOpenCV Core Widgets Gui OpenGL Qml Quick QuickControls2)

```

