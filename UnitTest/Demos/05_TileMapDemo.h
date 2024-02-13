#pragma once
#include "Geomatries/Tile/TMap.h"
#include "Utilities/FileStream.h"
class TileMapDemo : public IObject
{
public:


	// IObject��(��) ���� ��ӵ�
	void Init() override;

	void Destroy() override;

	void Update() override;

	void Render() override;

	void PostRender() override;

	void GUI() override;
private:
	TMap* tm = nullptr;
};