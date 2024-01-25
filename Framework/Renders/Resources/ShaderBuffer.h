#pragma once
#include "Framework.h"

// GPU에서 사용하는 데이터를 CPU에서 생성하고 수정할 수 있도록 하는 버퍼
class ShaderBuffer
{
public:
	void SetVSBuffer(uint slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(uint slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	ShaderBuffer(void* data, uint dataSize)
		:data(data), dataSize(dataSize)
	{
		// 버퍼의 사용 용도	// USAGE_DYNAMIC 은 CPU에서 수정 가능
		desc.Usage = D3D11_USAGE_DYNAMIC;
		// 버퍼의 크기
		desc.ByteWidth = dataSize;
		// 바인딩할 대상
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		// CPU에서 버퍼에 접근하는 방식
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	void MapData()
	{
		// 데이터 매핑을 위한 구조체
		D3D11_MAPPED_SUBRESOURCE subResource;
		// 데이터 맵핑
		HRESULT hr = DC->Map
		(
			buffer,						// 매핑할 그래픽 리소스
			0,							// 매핑할 시작 바이트 위치
			D3D11_MAP_WRITE_DISCARD,	
			// 매핑 방법 (WRITE_DISCARD는 완전히 새로 쓴다.)
			0,							// 매핑을 원하는 하위 리소스
			&subResource				// 매핑된 메모리 주소를 전달
		);
		CHECK(hr);
		// 데이터 복사
		memcpy(subResource.pData, data, dataSize);
		// 버퍼 언매핑
		DC->Unmap(buffer, 0);
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	uint dataSize = 0;
};