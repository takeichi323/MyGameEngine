#include "Model.h"

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//ファイルネームが同じだったら、読み込まない
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}
	modelList.push_back(pData);
	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx; pData->pfbx_->Load(fileName);
		
	}
	modelList.push_back(pData);
	return(modelList.size() - 1);

	//読んで作る
	// modellistにぶっこむ
	// 今読んだモデルのモデル番号を返す

}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//モデル番号は、modelListのインデックス
}

void Model::Draw(int hModel)
{
	//モデル番号は、modelListのインデックス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_/*メンバのトランスフォーム*/);


}
