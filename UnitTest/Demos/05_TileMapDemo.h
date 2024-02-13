#pragma once
#include "Geomatries/Tile/TMap.h"
#include "Utilities/FileStream.h"
class TileMapDemo : public IObject
{
public:


	// IObject을(를) 통해 상속됨
	void Init() override;

	void Destroy() override;

	void Update() override;

	void Render() override;

	void PostRender() override;

	void GUI() override;
private:
	TMap* tm = nullptr;
};