#pragma once
#include "Engine/GameObject.h"

const int MODEL_NUM = 5;
const int XSIZE{ 15 };
const int ZSIZE{ 15 };

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[MODEL_NUM];    //モデル番号
    int table_[XSIZE][ZSIZE];
public:
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
};