#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Fbx;

//�v���C�V�[�����Ǘ�����N���X
class ChildOden : public GameObject
{
	Fbx* pFbx;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ChildOden(GameObject* parent);
	//�f�X�g���N�^
	~ChildOden();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


