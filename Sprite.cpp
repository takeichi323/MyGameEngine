#include "Sprite.h"
#include "Camera.h"
#include <cassert>


Sprite::Sprite() :
	vertextNum_(0),
	//vertices_(nullptr),
	pVertexBuffer_(nullptr),
	indexNum_(0),
	//index_(nullptr),
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	pTexture_(nullptr)

{
}

Sprite::~Sprite()
{
	Release();
}

//初期化
HRESULT Sprite::Initialize()
{
	//頂点情報
	InitVertexData();
	if (FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}

	//インデックス情報
	InitIndexData();
	if (FAILED(CreateIndexBuffer()))
	{
		return E_FAIL;
	}

	//コンスタントバッファ作成
	if (FAILED(CreateConstantBuffer()))
	{
		return E_FAIL;
	}

	//テクスチャのロードする
	if (FAILED(LoadTexture()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	PassDateToCB(worldMatrix);

	SetBufferToPipeline();

	Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}

void Sprite::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_DELETE(pConstantBuffer_);
	SAFE_DELETE(pIndexBuffer_);
	//SAFE_DELETE(index_);
	SAFE_DELETE(pVertexBuffer_);
	//SAFE_DELETE(vertices_);
	
}

void Sprite::InitVertexData()
{
	// 頂点情報
	VERTEX vertices[] =
	{
		//正面  1
		{XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f)},	// 四角形の頂点（左上）
		{XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.0f, 0.0f, 0.0f) },	// 四角形の頂点（右上）
		{XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25f, 0.5f, 0.0f, 0.0f) },	// 四角形の頂点（右下）
		{XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f)  },	// 四角形の頂点（左下）	
	};

	vertextNum_ = sizeof(vertices) / sizeof(VERTEX);

	vertices_ = new VERTEX[vertextNum_];
	memccpy(vertices_, vertices, sizeof(vertices));
}

HRESULT Sprite::CreateVertexBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX)* vertextNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;
	

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "CreateBufferの初期化に失敗しました", "エラー", MB_OK);
		//エラー処理
		return hr;
	}
	return S_OK;
}

void Sprite::InitIndexData()
{
	int index[] = {
		0,2,3, 0,1,2, };



}

HRESULT Sprite::CreateIndexBuffer()
{
	HRESULT hr;
	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int)*indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "CreateBufferの初期化に失敗しました", "エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT Sprite::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}
	pTexture_ = new Texture;
	pTexture_->Load("Assets\\dice.png");

	return S_OK;
}

HRESULT Sprite::LoadTexture()
{
	pTexture_ = new Texture;

	HRESULT hr;
	hr = pTexture_->Load("Assets\\Dice.png");
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャの作成に失敗しました", "エラー", MB_OK);
	}
	return S_OK;
}

void Sprite::PassDateToCB(DirectX::XMMATRIX& worldMatrix)
{
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);
}

void Sprite::SetBufferToPipeline()
{
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
}
