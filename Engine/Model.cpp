#include "Model.h"

namespace Model {

	
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;
		//�g�����X�t�H�[��

	};
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*>modelList;
}
int Model::Load(std::string fileName)
{
	

	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//�t�@�C���l�[����������������A�ǂݍ��܂Ȃ�
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

	//�ǂ�ō��
	// modellist�ɂԂ�����
	// ���ǂ񂾃��f���̃��f���ԍ���Ԃ�

}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
}

void Model::Draw(int hModel)
{
	//���f���ԍ��́AmodelList�̃C���f�b�N�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_/*�����o�̃g�����X�t�H�[��*/);


}

void Model::Release()
{

}
