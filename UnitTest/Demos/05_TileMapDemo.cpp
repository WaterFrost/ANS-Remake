#include "stdafx.h"
#include "05_TileMapDemo.h"

void TileMapDemo::Init()
{
	uint spacing = 40;
	
	uint width = WinMaxWidth / spacing;
	uint height = WinMaxHeight / spacing;


	tm = new TMap(width, height, spacing);

	TileSet::Get()->ChangeTileMap(TexturePath + L"/Tilesets/Hills.png", 11, 7);
}

void TileMapDemo::Destroy()
{
	SAFE_DELETE(tm);
}

void TileMapDemo::Update()
{
	tm->Update();
}

void TileMapDemo::Render()
{
	tm->Render();
}

void TileMapDemo::PostRender()
{
}

void TileMapDemo::GUI()
{
	tm->GUI();
}
