#include "ChildOden.h"
#include "Engine//Fbx.h"

ChildOden::ChildOden(GameObject* parent)
{
}

void ChildOden::Initialize()
{
	
	pFbx = new Fbx;
	pFbx->Load("Assets/odenn.fbx");
	transform_.scale_.x = 0.2;
	transform_.scale_.y = 0.2;
	transform_.scale_.z = 0.2;
	Instantiate<ChildOden>(this);

}

void ChildOden::Update()
{
	transform_.rotate_.y++;
}

void ChildOden::Draw()
{
	pFbx->Draw(transform_);
}

void ChildOden::Release()
{
	pFbx->Release();
	
}
