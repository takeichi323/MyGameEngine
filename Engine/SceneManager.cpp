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
	//シーンを実際に切り替える
	//現在のシーンと、ネクストシーンが別だったら切り替え
	if (currentSceneID_ != nextSceneID_)
	{
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		//ロードしたデータを全削除
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
	//現在のシーンの後片付け
	//新しいシーンの準備
	currentSceneID_ = nextSceneID_;
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

/// <summary>
/// 指定したシーンをnextSceneID_に設定する（＝次のUpdateで）
/// </summary>
/// <param name="_next"></param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;

}
