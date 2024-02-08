#pragma once

class TileSet : public SingletonBase<TileSet>
{
public:
	friend class SingletonBase<TileSet>;
	friend class TMap;

	void GUI();

	ID3D11ShaderResourceView* GetSRV() { return tileSRV; }

	void ChangeTileMap(wstring imagePath, uint xCount, uint yCount);
private:
	TileSet();
	~TileSet();
private:
	ID3D11ShaderResourceView* tileSRV = nullptr;

	uint tileXCount = 0;
	uint tileYCount = 0;

	//�÷��̾ ������ Ÿ���� ���� UV
	Vector2 selectedStartUV = Values::ZeroVec2;
	//�׸��� �̹��� ũ�� ������
	Vector2 TexelTileSize = Values::ZeroVec2;

};