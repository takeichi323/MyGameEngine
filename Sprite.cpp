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

//�f�X�g���N�^
Sprite::~Sprite()
{
	Release();
}

HRESULT  Sprite::Initialize()
{
	
	// ���_���
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

	
	
	


	//�C���f�b�N�X���
	

	

	

	// �R���X�^���g�o�b�t�@�쐬
	
}

void Sprite::Draw(XMMATRIX& worldMatrix)
{
	// �R���X�^���g�o�b�t�@�ɓn�����

		

	//���_�o�b�t�@
	
	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	
	//�R���X�^���g�o�b�t�@


	

}

void Sprite::Release()
{
	pTexture_->Release();
	SAFE_DELETE(pTexture_);

	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
	

}





