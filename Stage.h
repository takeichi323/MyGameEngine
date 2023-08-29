#pragma once
#include "Engine/GameObject.h"

const int MODEL_NUM = 5;
const int XSIZE{ 15 };
const int ZSIZE{ 15 };

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //���f���ԍ�
    int table_[XSIZE][ZSIZE];
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};