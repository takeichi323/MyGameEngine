#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Stage.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
	Instantiate<Stage>(this);
}

void TestScene::Update()
{
	
	//GameObject* dbgTest = FindObject("SceneManager");
	if (Input::IsKey(DIK_SPACE))
    {
		SceneManager* pSceneManager = (SceneManager *)FindObject("SceneManager");//ダウンキャスト
		
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
