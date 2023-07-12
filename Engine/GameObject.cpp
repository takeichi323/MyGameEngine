#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr),IsDead(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),IsDead(false),objectName_(name)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->UpdateSub();
	for (auto itr = childList_.begin(); itr != childList_.end(); )
	{
		if ((*itr)->IsDead == true)
		{
			(*itr)->ReleaseSub();
			//SAFE_DELETE(*itr);
			itr=childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
	
		(*itr)->ReleaseSub();
		//SAFE_DELETE(*itr);
	}
	Release();
}



void GameObject::KillMe()
{
	IsDead = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}



