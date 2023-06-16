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
			XMVECTOR position;//位置
			XMVECTOR uv;//頂点情報
			
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

	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();

	void PassDateToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();


		
		

};

