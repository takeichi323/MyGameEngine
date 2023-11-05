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





//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //モデル番号
   // int table_[XSIZE][ZSIZE];
    struct
    {
        int type;
        int height;
    } table_[XSIZE][ZSIZE];

   


    

    int mode_;     //0:上げる　１:下げる　２：種類を変える
    int select_;  //種類
    bool push_;  //クリックor長押し
    int bufX = -1, bufZ;


public:
    struct BlockState {
        BLOCKTYPE type;
        int height;

        // コピーコンストラクタを追加
        BlockState(const BlockState& other) {
            type = other.type;
            height = other.height;
        }
    };

  

    void SetBlock(int _x, int _z, BLOCKTYPE _type);
    void SetBlockHeight(int _x, int _z, int _height);
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

    void Save() ;
    void Load();
    void ResetStage();
    void SaveToHistory();
    void Undo();
    void ButtonChange();
   
};

