#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	
	GameObject* dbgTest = FindObject("SceneManager");
	//if (Input::IsKey(DIK_SPACE))
	//{
	//	SceneManager* pSceneManager = (SceneManager *)FindObject("SceneManager");//ダウンキャスト
	//	pSceneManager->ChangeScene(SCENE_ID_PLAY);
	//}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
