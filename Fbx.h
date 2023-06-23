#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;//ワールドのやつ
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;//位置
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	//オブジェクトを見ないとポリゴン数と頂点数が分からない

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
public:

	Fbx();
	HRESULT Load(std::string fileName);
	HRESULT IntConstantBuffer();//コンスタントバッファ
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitVertex(fbxsdk::FbxMesh* mesh);//頂点バッファ準備
	void    Draw(Transform& transform);
	void    Release();
};
