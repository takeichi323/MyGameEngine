#include "PlayScene.h"
#include "Engine//Fbx.h"
#include"Player.h"
#include "Enemy.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	/*: GameObject(parent, "PlayScene")*/
{
}

//������
void PlayScene::Initialize()
{
	//Player* pPlayer;
	//pPlayer = new Player(this);//�v���C���[�̐e�́A����(PlayScene)
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);//PlayScene�̎q�Ƃ��āA�v���C���[��o�^
	/*GameObject* pPlayer=*/ Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	
}

//�X�V
void PlayScene::Update()
{
	
	
	
}

//�`��
void PlayScene::Draw()
{
	
	
}

//�J��
void PlayScene::Release()
{

	
}
