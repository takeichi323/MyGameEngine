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
	
			XMMATRIX	matW;
		};
		
		//頂点情報
		struct VERTEX
		{
			XMVECTOR position;
			XMVECTOR uv;
			
		};
protected:
	UINT64  vertextNum_;
	std::vector<VERTEX>vertices_;
	ID3D11Buffer* pVertexBuffer_;

	UINT64 indexNum;
	std::vector<int>index_;

	ID3D11Buffer* PIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;

	Texture* pTexture_;
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

	void PassDateToCB(DirectX::XMMATRIX&worldMatrix)

		
		

};

