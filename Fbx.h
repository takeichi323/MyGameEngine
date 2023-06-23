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
		XMMATRIX	matWVP;//���[���h�̂��
		XMMATRIX	matNormal;
	};

	struct VERTEX
	{
		XMVECTOR position;//�ʒu
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	//�I�u�W�F�N�g�����Ȃ��ƃ|���S�����ƒ��_����������Ȃ�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
public:

	Fbx();
	HRESULT Load(std::string fileName);
	HRESULT IntConstantBuffer();//�R���X�^���g�o�b�t�@
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitVertex(fbxsdk::FbxMesh* mesh);//���_�o�b�t�@����
	void    Draw(Transform& transform);
	void    Release();
};
