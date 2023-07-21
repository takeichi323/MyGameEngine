#include "Enemy.h"
#include "Engine/SphereCollider.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("Assets/odenn.fbx");
	transform_.position_.z = 20.0f;

	SphereCollider* col = new SphereCollider(1.0f);
	AddColloder(col);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}
