#include "Engine/Model.h"
#include "Engine/Direct3D.h"

namespace Model {

	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*> modelList;
}

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return(modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
}
void Model::Draw(int hModel) {
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; 
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}

void Model::RayCast(int hModel, RayCastData& rayData)
{	
	modelList[hModel]->transform_.Calclation();
	//�@���[���h�s��̋t�s��
	XMMATRIX wInv = XMMatrixInverse(nullptr, modelList[hModel]->transform_.GetWorldMatrix());
	//�A���C�̒ʉߓ_�����߂�i���f����Ԃł̃��C�̕����x�N�g�������߂�j
	XMVECTOR vpass{ rayData.start.x + rayData.dir.x,
					rayData.start.y + rayData.dir.y,
					rayData.start.z + rayData.dir.z,
					rayData.start.w + rayData.dir.w };
	//�BrayData.start�����f����Ԃɕϊ�(�@��������)
	XMVECTOR vstart = XMLoadFloat4(&rayData,start);
	vpass = XMVector3TransformCoord(vstart, wInv);
	//�C�i�n�_��������x�N�g�������傢�L�΂�����j�ʉߓ_�i�A�j�ɇ@��������
	vpass = XMVector3TransformCoord(vpass, wInv);
	//�DrayData.dir���B����C�Ɍ������x�N�g���ɂ���i�����Z�j
	vpass = vpass-vstart;
	XMStoreFloat4(&rayData.dir, vpass);
	//�w�肵�����f���ԍ���FBX�Ƀ��C�L���X�g
	modelList[hModel]->pfbx_->RayCast(rayData);
}
