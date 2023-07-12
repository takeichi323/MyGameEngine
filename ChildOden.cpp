#include "ChildOden.h"
#include "Engine//Fbx.h"

ChildOden::ChildOden(GameObject* parent) :GameObject(parent, "ChildOden")
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	
	pFbx = new Fbx;
	pFbx->Load("Assets/odenn.fbx");
	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;
	transform_.position_.x = 2.0f;
	transform_.position_.y = 1.0f;

}

void ChildOden::Update()
{
	
	transform_.rotate_.y++;
	if (transform_.rotate_.y > 200)
	{
		KillMe();
	}
}

void ChildOden::Draw()
{
	pFbx->Draw(transform_);
}

void ChildOden::Release()
{
	pFbx->Release();
	
}
