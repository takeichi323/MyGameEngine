#include "Stage.h"
#include "Engine/Model.h"
#include "Controller.h"
#include"resource.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"



void Stage::SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].type = _type;
}

void Stage::SetBlockHeight(int _x, int _z, int _height)
{
    table_[_x][_z].height = _height;
}



//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_{-1,-1,-1,-1,-1}
{
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = -1;
    }
    for (int x = 0; x < XSIZE; x++) {
        for (int z = 0; z< ZSIZE; z++) {
            SetBlock(x, z, DEFAULT);
        }
    }
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    string modelname[] = {
        "BoxDefault.fbx",
        "BoxBrick.fbx",
        "BoxGrass.fbx",
        "BoxSand.fbx",
        "BoxWater.fbx"
    };
    string fname_base = "assets/";
    //モデルデータのロード
    for (int i = 0; i < MODEL_NUM; i++) {
        hModel_[i] = Model::Load(fname_base+ modelname[i]);
        assert(hModel_[i] >= 0);
    }
    for (int z = 0; z < ZSIZE; z++) {
        for (int x = 0; x < XSIZE; x++) {
            SetBlock(x, z, (BLOCKTYPE)(z % 5));
            SetBlockHeight(x, z, x % 5);
        }
    }
    /*table_[3][5] = GRASS;*/
}

//更新
void Stage::Update()
{
    if (!Input::IsMouseButtonDown(0)) {
        return;
    }
    float w = (float)(Direct3D::scrWidth/2);
    float h = (float)(Direct3D::scrHeight / 2);


    XMMATRIX vp =
    {
        w ,0, 0, 0,
        0, -h, 0, 0,
        0, 0, 1, 0,
        w, h ,0, 1


    };
         //ビューポート
        XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
        //プロジェクション変換
        XMMATRIX invProj = XMMatrixInverse(nullptr,Camera::GetProjectionMatrix);
        //ビュー変換
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
        XMFLOAT3 mousePosFront = Input::GetMouseposition();//マウスポジゲット;
        mousePosFront.z = 0.0f;
        XMFLOAT3 mousePosBack = Input::GetMousePosition();
        mousePosBack.z = 1.0f;
        
        //①　mousePosFrontをベクトル変換
        XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
        //②　①にinvVP,invPrj,invViewをかける
        vMouseFront = XMVector3TransformCoord(vMouseFront, invVP* invProj* invView);
        //③　mousePosBackをベクトルに変換
        XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
        //④　③にinvVP,invPrj,invViewをかける
        vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
        
       
        
  
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                //⑤　②から④に向かってレイをうつ（とりあえずモデル番号はhModel_[0]）
                //table[x][z]からオブジェクトのタイプを取り出して書く！
                RayCastData data;
                XMStoreFloat4(&data.start,vMouseFront );
                XMStoreFloat4(& data.dir, vMouseBack - vMouseFront );
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::RayCast(hModel_[0], data);


                    Model::RayCast(hModel_[0], data);

                //⑥　レイが当たったらブレークポイントで止める
                if (data.hit)
                {
                    table_[x][z].height++;
                    break;
                }


               /* int type = table_[x][z].type;
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::SetTransform(hModel_[type], trans);
                Model::Draw(hModel_[type]);*/
            }
        }
    }
//void Stage::Draw()
//{
//
//}

//開放
void Stage::Release()
{
}



BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //ダイアログができた
    case WM_INITDIALOG:
        //ラジオボタンの初期値
            SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP),BM_SETCHECK, BST_CHECKED, 0);

            //コンボボックスの初期値
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"デフォルト"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"レンガ"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"草原"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"砂地"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"水"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        
            return TRUE;

    }
    return FALSE;
}


