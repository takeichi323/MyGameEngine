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
	
		//�R���X�^���g�o�b�t�@�[
		struct CONSTANT_BUFFER
		{
	
			XMMATRIX	matW;//���[���h���W
		};
		
		//���_���
		struct VERTEX
		{
			XMFLOAT3 position;
			XMFLOAT3 uv;
			
		};
protected:
	UINT64  vertextNum_;//���_��
	std::vector<VERTEX>vertices_;//���_���
	ID3D11Buffer* pVertexBuffer_;//���_�o�b�t�@

	UINT64 indexNum_;//�C���f�b�N�X��
	std::vector<int>index_;//�C���f�b�N�X���

	ID3D11Buffer* pIndexBuffer_;//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;//�R���X�^���g�o�b�t�@

	Texture* pTexture_;//�e�N�X�`��
public:
	Sprite();
	~Sprite();

	HRESULT Initialize();

	void Draw(XMMATRIX& worldMatrix);

	void Release();

private:

	virtual void InitVertexData();//���_���̏���
	HRESULT CreateVertexBuffer();//���_�o�b�t�@���쐬

	virtual void InitIndexData();//�C���f�b�N�X��������
	HRESULT  CreateIndexBuffer();//�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer();//�R���X�^���g�o�b�t�@�쐬

	HRESULT LoadTexture();//�e�N�X�`�������[�h

	void PassDateToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();


		
		

};

