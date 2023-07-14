#pragma once
#include<string>
#include<vector>
#include"Engine/Fbx.h"

namespace Model
{
	struct ModelData
	{
		Fbx* pfbx_;
		Transform transform_;
		std::string filename_;
		//�g�����X�t�H�[��
		
	};
	
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*>modelList;


}



