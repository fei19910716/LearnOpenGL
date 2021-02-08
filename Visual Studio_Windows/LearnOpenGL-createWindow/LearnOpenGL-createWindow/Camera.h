#pragma once
#include "Vector3f.h"

class Camera
{
public:
	explicit Camera();

	void update(float deltaTime);
	/*
	* ��������������˶�����ƽ��
	*/
	void span(float dist);
	/*
	* ����camera��ǰ���˶���������
	*/
	void zoom(float scale);
	/*
	* ����camera�����������ת
	*/
	void rotate(float angle, float x, float y, float z);
	/*
	* ����camera��x�����ת
	*/
	void pitch(float angle);
	/*
	* ����camera��up�����ת
	*/
	void yaw(float angle);

	/*
	* position_: ��¼camera��λ��
	* up_�� ��¼camera��up��
	* target_����¼camera���ҷ���
	*/
	Vector3f position_, up_, target_;

	/*
	* ʹ��bool���������˶��Ŀ���
	*/
	bool moveLeft_, moveRight_,moveForward_,moveBack_;
};

