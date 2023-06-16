#include "Sprite.h"
#include "Camera.h"
#include <cassert>


Sprite::Sprite() :
	vertextNum_(0),
	vertices_(nullptr),
	pVertexBuffer_(nullptr),
	indexNum_(0),
	index_(nullptr),
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr)

{
}

//デストラクタ
Sprite::~Sprite()
{
	Release();
}

HRESULT  Sprite::Initialize()
{
	
	// 頂点情報
	InitVertexData();
		if(FAILED(CreateVertexBuffer()))
	{
			return E_FAIL;

	}

		
		InitVertexData();
		if (FAILED(CreateVertexBuffer()))
		{
			return E_FAIL;

		}

	
	
	


	//インデックス情報
	

	

	

	// コンスタントバッファ作成
	
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	// コンスタントバッファに渡す情報

		

	//頂点バッファ
	
	// インデックスバッファーをセット
	
	//コンスタントバッファ


	

}

void Sprite::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	

}





