#pragma once

// 정점의 인덱스를 저장하는 버퍼
class IndexBuffer
{
public:
	~IndexBuffer();

	void Create(const vector<UINT>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() { return buffer; }
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount()  { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};

/*
InputLayout
- 정점 버퍼의 데이터 구조를 정의
- 정점 데이터의 각 요소(위치, 색상, 텍스처 좌표 등)의 형식, 크기, 순서 등을 지정
- IA 단계에서는 정점 셰이더로 데이터를 전달하기 전에 정덤 데이터를 올바르게 해석하는데 사용
*/