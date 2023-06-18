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
	Release();//SAFE_RELEASEシリーズに書き換えよう
}

HRESULT  Sprite::Initialize()
{
	
	// 頂点情報
	InitVertexData();
		if(FAILED(CreateVertexBuffer()))
	{
			return E_FAIL;

	}

	// 頂点データ用バッファの設定
	/*D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;*/

	
	


	//インデックス情報
	int index[] = {
		0,2,3, 0,1,2,//正
		4,6,7, 4,5,6,//右
		8,10,11, 8,9,10,//左
		12,14,15, 12,13,14,//上
		19,17,16,  19,18,17,//下
		21,23,22, 21,20,23//後
	};

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	

	// コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\Sprite.png");

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	// コンスタントバッファに渡す情報

	CONSTANT_BUFFER cb;
	/*cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());*/
	

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用


	Direct3D::pContext_->DrawIndexed(36, 0, 0);//数書いてる

}

void Sprite::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	/*pVertexBuffer_->Release();
	 pIndexBuffer_->Release();
	pConstantBuffer_->Release();*/

}



void Sprite::InitVertexData()
{
}

HRESULT Sprite::CreateVertexBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::CreateConstantBuffer()
{
	return E_NOTIMPL;
}

HRESULT Sprite::LoadTexture()
{
	return E_NOTIMPL;
}

void Sprite::PassDateToCB(DirectX::XMMATRIX& worldMatrix)
{
}

void Sprite::SetBufferToPipeline()
{
}

