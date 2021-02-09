#include "Camera.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

Camera::Camera():position_(0.0f,0.0f,0.0f),
				 up_(0.0f,1.0f,0.0f),
				 target_(0.0f,0.0f,-1.0f),
				 moveLeft_(false),
				 moveRight_(false),
				 moveForward_(false),
				 moveBack_(false)
{
}

void Camera::update(float deltaTime)
{
	float speed = 1.0f;
	float rotateSpeed = 1.0f;
	if (moveLeft_) {
		// span(deltaTime* speed);
		yaw(rotateSpeed * deltaTime);
	}
	if (moveRight_) {
		// span(-deltaTime* speed);
		yaw(-rotateSpeed * deltaTime);

	}
	if (moveForward_) {
		zoom(deltaTime * speed);
		
	}
	if (moveBack_) {
		zoom(-deltaTime * speed);
		
	}
	/*
	* 这里非常重要，不要就会出现鼠标抬起画面在动的现象
	*/
	glLoadIdentity();

	// se mvp
	gluLookAt(position_.x, position_.y, position_.z,
			  target_.x, target_.y, target_.z,
			  up_.x, up_.y, up_.z);
}

void Camera::span(float dist)
{
	Vector3f viewDirection = target_ - position_;
	viewDirection.normalize();
	Vector3f rightDirection = viewDirection.cross(up_);
	position_ = position_ + rightDirection * dist;
	target_ = target_ + rightDirection * dist;
}

void Camera::zoom(float scale)
{
	Vector3f forwardDirection = target_ - position_;
	forwardDirection.normalize();
	position_ = position_ + forwardDirection * scale;
	target_ = target_ + forwardDirection * scale;
	
}


void Camera::rotate(float angle, float x, float y, float z)
{
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3f viewDirection = target_ - position_;
	Vector3f newViewDirection;
	viewDirection.normalize();
	newViewDirection.x = Vector3f(C + x * x * (1 - C), x * y * (1 - C) - z * S, x * z * (1 - C) + y * S) * viewDirection; // 绕任意轴旋转的矩阵公式
	newViewDirection.y = Vector3f(x * y * (1 - C) + z * S, C + y * y * (1 - C), y * z * (1 - C) - x * S) * viewDirection;
	newViewDirection.z = Vector3f(x * z * (1 - C) - y * S, y * z * (1 - C) + x * S, C + z * z * (1 - C)) * viewDirection;
	target_ = position_ + newViewDirection;

}

void Camera::pitch(float angle)
{
	Vector3f viewDirection = target_ - position_;
	viewDirection.normalize();
	Vector3f rightDirection = viewDirection.cross(up_);
	rotate(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void Camera::yaw(float angle)
{
	rotate(angle, up_.x, up_.y, up_.z);
}
