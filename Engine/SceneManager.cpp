#include "SceneManager.h"
#include "Model.h"
#include "../TestScene.h"
#include "../PlayScene.h"
#include "Direct3D.h"


SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	//�V�[�������ۂɐ؂�ւ���
	//���݂̃V�[���ƁA�l�N�X�g�V�[�����ʂ�������؂�ւ�
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		//���[�h�����f�[�^��S�폜
		Model::Release();
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		
		}

	}
	//���݂̃V�[���̌�Еt��
	//�V�����V�[���̏���
	currentSceneID_ = nextSceneID_;
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// �w�肵���V�[����nextSceneID_�ɐݒ肷��i������Update�Łj
/// </summary>
/// <param name="_next"></param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;

}
