#include "Stage.h"
#include "Engine/Model.h"
#include "Controller.h"


void SetBlock(int _x, int _z, BLOCKTYPE _type)
{
    table_[_x][_z].height = _height;
}

void SetBlockHeght(int _x, int _z, int _height)
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
            table_[x][z] = x % 5;
        }
    }
    /*table_[3][5] = GRASS;*/
}

//�X�V
void Stage::Update()
{

}

//�`��
void Stage::Draw()
{
    
    for (int x = 0; x < 15; x++)
    {
        for (int z = 0; z < 15; z++)
        {
            
            Transform trans;
            trans.position_.x = x;
            trans.position_.z = z;
            Model::SetTransform(hModel_[(x+z)%5], trans);
            Model::Draw(hModel_[(x + z) % 5]);

        }
    }
    
}

//�J��
void Stage::Release()
{
}



