#pragma once

#include "Tile.h"
#include "TileSet.h"

class IndexNumBuffer : public ShaderBuffer
{
public:
	IndexNumBuffer()
		:ShaderBuffer(&data, sizeof(Data))
	{
		data.index = 0;
	}
	void SetIndex(uint index) { data.index = index; }
	struct Data
	{
		uint index;
		Vector3 dummy;
	};
private:
	Data data;
};
class TMap
{
public:
	// width = ���ο� �� Ÿ�ϰ���
	// height = ���� �� Ÿ���� ����
	// 10x10 �� ��� �� 100���� Ÿ���� �򸰴�.
	//spacing�� �� Ÿ���� ����,���� ����
	TMap(uint width, uint height, uint spacing);
	~TMap();

	void Update();
	void Render();
	void GUI();

	void GenerateTileMap();
	
	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void Save(string path);
	void Load(string path);

	Tile* GetTile(Vector3 mPos);
private:

	vector<VertexTile> vertices;
	VertexBuffer* vb = nullptr;

	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;
	vector<uint> indices;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;

	IndexNumBuffer* inb = nullptr;

	uint width = 0;
	uint height = 0;
	uint spacing = 0;

	uint vertexCount = 0;
	uint indexCount = 0;

	D3D11_MAPPED_SUBRESOURCE subResource;

	Tile** tiles = nullptr;
};