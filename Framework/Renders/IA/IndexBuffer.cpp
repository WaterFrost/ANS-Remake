#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
	// I로 시작하는 DX 자료형들은 프로그래머가 빌려온 데이터이기 때문에 
	// RELEASE를 통해서 제거해줘야 한다.
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(uint);
	count = indices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	// desc
	{
		desc.Usage = usage;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = stride * count;

		switch (usage)
		{
		case D3D11_USAGE_DEFAULT:
		case D3D11_USAGE_IMMUTABLE:
			break;
		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;
		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
		}
	}

	// 버퍼 생성
	{
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

		subData.pSysMem = indices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
		CHECK(hr);
	}
}

void IndexBuffer::SetIA()
{
	// buffer가 가지고 있는 정점의 개수를 32비트로 설정
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
