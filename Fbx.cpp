#include "Fbx.h"

Fbx::Fbx():
	pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
	vertexCount_(0), polygonCount_(0)
{
}

HRESULT Fbx::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//各情報の個数を取得

	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数

	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数

	InitVertex(mesh);		//頂点バッファ準備
	InitIndex(mesh);		//インデックスバッファ準備
	IntConstantBuffer();	//コンスタントバッファ準備


	//マネージャ解放
	pFbxManager->Destroy();
}
HRESULT Fbx::IntConstantBuffer()
{

}

//インデックスバッファ準備
void Fbx::InitIndex(fbxsdk::FbxMesh* mesh)
{
	int* index = new int[polygonCount_ * 3];
	int count = 0;

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (DWORD vertex = 0; vertex < 3; vertex++)
		{
			index[count] = mesh->GetPolygonVertex(poly, vertex);
			count++;
		}
	}
}

//頂点バッファ準備
void Fbx::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//頂点情報を入れる配列
	VERTEX* vertices = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);
		}
	}

	
	
}

void Fbx::Draw(Transform& transform)
{
}

void Fbx::Release()
{
}
