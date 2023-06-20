#include "Sprite.h"
#include "Camera.h"
#include "Direct3D.h"
#include <cassert>


Sprite::Sprite() :
	/*vertextNum_(0),
	vertices_(nullptr),
	pVertexBuffer_(nullptr),
	indexNum_(0),
	index_(nullptr),
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),*/
	pTexture_(nullptr)

{
}

Sprite::~Sprite()
{

	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	//Release();
}

//������
HRESULT Sprite::Initialize()
{
	//���_���
	InitVertexData();
	if (FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}

	//�C���f�b�N�X���
	InitIndexData();
	if (FAILED(CreateIndexBuffer()))
	{
		return E_FAIL;
	}

	//�R���X�^���g�o�b�t�@�쐬
	if (FAILED(CreateConstantBuffer()))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃��[�h����
	if (FAILED(LoadTexture()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	//Direct3D::InitShader(SHADER_2D);

	PassDateToCB(worldMatrix);

	SetBufferToPipeline();

	Direct3D::pContext_->DrawIndexed(indexNum_, 0, 0);
}

void Sprite::Release()
{
	SAFE_DELETE(pTexture_);
	SAFE_DELETE(pConstantBuffer_);
	SAFE_DELETE(pIndexBuffer_);
	SAFE_DELETE(pVertexBuffer_);
	
	
}

void Sprite::InitVertexData()
{
	// ���_�f�[�^�錾
	VERTEX vertices[] =
	{
		{ XMFLOAT3(-1.0f,  1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i����j
		{ XMFLOAT3(1.0f,  1.0f, 0.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },   // �l�p�`�̒��_�i�����j
		{ XMFLOAT3(1.0f, -1.0f, 0.0f),	XMFLOAT3(1.0f, 1.0f, 0.0f) },   // �l�p�`�̒��_�i�E���j
	};


	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

HRESULT Sprite::CreateVertexBuffer()
{
	/*HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX)* vertextNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;*/

	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertextNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;
	Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	

	hr = Direct3D::pDevice_->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "CreateBuffer�̏������Ɏ��s���܂���", "�G���[", MB_OK);
		//�G���[����
		return hr;
	}
	return S_OK;
}

void Sprite::InitIndexData()
{
	int index[] = {
		0,2,3, 0,1,2, };
	HRESULT hr;
	// �C���f�b�N�X�o�b�t�@�𐶐�����
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum_;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

    Direct3D::pDevice_->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	


}

HRESULT Sprite::CreateIndexBuffer()
{
	
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

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
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
		MessageBox(NULL, "�e�N�X�`���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}
	return S_OK;
}

void Sprite::PassDateToCB(DirectX::XMMATRIX& worldMatrix)
{
	CONSTANT_BUFFER cb;
	cb.matW = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext_->PSSetSamplers(0, 1, &pSampler);
	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext_->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext_->Unmap(pConstantBuffer_, 0);
}

void Sprite::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext_->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext_->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);
	//�R���X�^���g�o�b�t�@
	Direct3D::pContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
}
