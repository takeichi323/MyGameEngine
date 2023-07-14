#include "Player.h"
#include "ChildOden.h"
#include "Engine//Fbx.h"
#include "Engine/Input.h"





Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),pFbx(nullptr)
{
}

void Player::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/odenn.fbx");
	this->transform_.scale_.x = 0.5;
	this->transform_.scale_.y = 0.5;
	this->transform_.scale_.z = 0.5;
	/*Instantiate< ChildOden>(this);
	GameObject*pCO2= Instantiate< ChildOden>(this);
	pCO2->SetPosition(-2, 1, 0);*/
}

void Player::Update()
{
	
	transform_.rotate_.y++;
	/*if (transform_.rotate_.y > 600)
	{
		KillMe();
	}*/
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= 0.1f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += 0.1f;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* pBullet = Instantiate<ChildOden>(pParent_);
		pBullet->SetPosition(transform_.position_);
	}
}

void Player::Draw()
{
	pFbx->Draw(this->transform_);
}

void Player::Release()
{
	pFbx->Release();
	delete pFbx;
}
