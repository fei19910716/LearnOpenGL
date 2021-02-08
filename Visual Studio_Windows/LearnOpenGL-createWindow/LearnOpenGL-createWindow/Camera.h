#pragma once
#include "Vector3f.h"

class Camera
{
public:
	explicit Camera();

	void update(float deltaTime);
	/*
	* 控制摄像机左右运动进行平移
	*/
	void span(float dist);
	/*
	* 控制camera的前后运动进行缩放
	*/
	void zoom(float scale);
	/*
	* 控制camera绕任意轴的旋转
	*/
	void rotate(float angle, float x, float y, float z);
	/*
	* 控制camera绕x轴的旋转
	*/
	void pitch(float angle);
	/*
	* 控制camera绕up轴的旋转
	*/
	void yaw(float angle);

	/*
	* position_: 记录camera的位置
	* up_： 记录camera的up轴
	* target_：记录camera的右方向
	*/
	Vector3f position_, up_, target_;

	/*
	* 使用bool变量进行运动的控制
	*/
	bool moveLeft_, moveRight_,moveForward_,moveBack_;
};

