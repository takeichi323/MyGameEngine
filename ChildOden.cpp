#include "ChildOden.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

ChildOden::ChildOden(GameObject* parent) :GameObject(parent, "ChildOden"),hModel_(-1)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	
	

	hModel_=Model::Load("Assets/odenn.fbx");
	assert(hModel_ >= 0);

	transform_.scale_.x = 0.2f;
	transform_.scale_.y = 0.2f;
	transform_.scale_.z = 0.2f;
	/*transform_.position_.x = 2.0f;
	transform_.position_.y = 1.0f;*/
	SphereCollider* col = new SphereCollider(1.0f);

}

void ChildOden::Update()
{
	
	transform_.rotate_.y++;
	transform_.position_.z += 0.5f;
	if (transform_.position_.z > 50)
	{
		KillMe();
	}
}

void ChildOden::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
}

void ChildOden::Release()
{
	pFbx->Release();
	
}
