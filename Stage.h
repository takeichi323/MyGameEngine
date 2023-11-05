#pragma once
#include "Engine/GameObject.h"
#include"windows.h"




namespace {
    const int MODEL_NUM = 5;
    const int XSIZE{ 15 };
    const int ZSIZE{ 15 };

    enum BLOCKTYPE
    {
        DEFAULT,
        BRICK,
        GRASS,
        SAND,
        WATER
    };
}





//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //���f���ԍ�
   // int table_[XSIZE][ZSIZE];
    struct
    {
        int type;
        int height;
    } table_[XSIZE][ZSIZE];

   


    

    int mode_;     //0:�グ��@�P:������@�Q�F��ނ�ς���
    int select_;  //���
    bool push_;  //�N���b�Nor������
    int bufX = -1, bufZ;


public:
    struct BlockState {
        BLOCKTYPE type;
        int height;

        // �R�s�[�R���X�g���N�^��ǉ�
        BlockState(const BlockState& other) {
            type = other.type;
            height = other.height;
        }
    };

  

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
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
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    void Save() ;
    void Load();
    void ResetStage();
    void SaveToHistory();
    void Undo();
    void ButtonChange();
   
};

