#pragma once
#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include"Texture.h"
#include<vector>
using namespace DirectX;
#define SAFE_DELE
class Sprite
{
	
		//コンスタントバッファー
		struct CONSTANT_BUFFER
		{
	
			XMMATRIX	matW;//ワールド座標
		};
		
		//頂点情報
		struct VERTEX
		{
			XMFLOAT3 position;
			XMFLOAT3 uv;
			
		};
protected:
	UINT64  vertextNum_;//頂点数
	std::vector<VERTEX>vertices_;//頂点情報
	ID3D11Buffer* pVertexBuffer_;//頂点バッファ

	UINT64 indexNum_;//インデックス数
	std::vector<int>index_;//インデックス情報

	ID3D11Buffer* pIndexBuffer_;//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ

	Texture* pTexture_;//テクスチャ
public:
	Sprite();
	~Sprite();

	HRESULT Initialize();

	void Draw(XMMATRIX& worldMatrix);

	void Release();

private:

	virtual void InitVertexData();//頂点情報の準備
	HRESULT CreateVertexBuffer();//頂点バッファを作成

	virtual void InitIndexData();//インデックス情報を準備
	HRESULT  CreateIndexBuffer();//インデックスバッファを作成

	HRESULT CreateConstantBuffer();//コンスタントバッファ作成

	HRESULT LoadTexture();//テクスチャをロード

	void PassDateToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();


		
		

};

