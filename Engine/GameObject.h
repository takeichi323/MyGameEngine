#pragma once

#include ����������
#include ����������
#include "Transform.h"

class GameObject
{
	���������������� childList_;
	Transform	transform_;
	������������	pParent_;
	������������	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	�������� void Initialize() ������;
	�������� void Update() ������;
	�������� void Draw() ������;
	�������� void Release() ������;
};

