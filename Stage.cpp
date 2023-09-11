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



//�R���X�g���N�^
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

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
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
    //���f���f�[�^�̃��[�h
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

//�X�V
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
         //�r���[�|�[�g
        XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
        //�v���W�F�N�V�����ϊ�
        XMMATRIX invProj = XMMatrixInverse(nullptr,Camera::GetProjectionMatrix);
        //�r���[�ϊ�
        XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
        XMFLOAT3 mousePosFront = Input::GetMouseposition();//�}�E�X�|�W�Q�b�g;
        mousePosFront.z = 0.0f;
        XMFLOAT3 mousePosBack = Input::GetMousePosition();
        mousePosBack.z = 1.0f;
        
        //�@�@mousePosFront���x�N�g���ϊ�
        XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
        //�A�@�@��invVP,invPrj,invView��������
        vMouseFront = XMVector3TransformCoord(vMouseFront, invVP* invProj* invView);
        //�B�@mousePosBack���x�N�g���ɕϊ�
        XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
        //�C�@�B��invVP,invPrj,invView��������
        vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
        
       
        
  
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            for (int y = 0; y < table_[x][z].height + 1; y++)
            {
                //�D�@�A����C�Ɍ������ă��C�����i�Ƃ肠�������f���ԍ���hModel_[0]�j
                //table[x][z]����I�u�W�F�N�g�̃^�C�v�����o���ď����I
                RayCastData data;
                XMStoreFloat4(&data.start,vMouseFront );
                XMStoreFloat4(& data.dir, vMouseBack - vMouseFront );
                Transform trans;
                trans.position_.x = x;
                trans.position_.y = y;
                trans.position_.z = z;
                Model::RayCast(hModel_[0], data);


                    Model::RayCast(hModel_[0], data);

                //�E�@���C������������u���[�N�|�C���g�Ŏ~�߂�
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

//�J��
void Stage::Release()
{
}



BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        //�_�C�A���O���ł���
    case WM_INITDIALOG:
        //���W�I�{�^���̏����l
            SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP),BM_SETCHECK, BST_CHECKED, 0);

            //�R���{�{�b�N�X�̏����l
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"�f�t�H���g"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"�����K"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"����"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"���n"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_ADDSTRING, 0, ((LPARAM)"��"));
        SendMessage(GetDlgItem(hDlg, IDC_COMBO2), CB_SETCURSEL, 0, 0);
        
            return TRUE;

    }
    return FALSE;
}


