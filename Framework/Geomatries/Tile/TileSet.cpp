#include "Framework.h"
#include "TileSet.h"

TileSet::TileSet()
{
	Texture2D* tex = new Texture2D(TexturePath + L"Tile.jpg");
	tileSRV = tex->GetSRV();
	SAFE_DELETE(tex);

	// GUI ���� ǥ���� �̹��� ��ư�� X,Y �� ����
	// �̹����� 10x10 ���� �߶� GUI �� ǥ��
	tileXCount = 10;
	tileYCount = 10;

	TexelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

TileSet::~TileSet()
{
}

void TileSet::GUI()
{
	ImGui::Begin("TileSet");
	{
		int count = 0;
		for (uint y = 0; y < tileYCount; y++)
		{
			for (uint x = 0; x < tileXCount; x++)
			{
				float startX = TexelTileSize.x * x;
				float startY = TexelTileSize.y * y;

				ImGui::PushID(count);
				if (ImGui::ImageButton(tileSRV, ImVec2(40, 40), ImVec2(startX, startY), ImVec2(startX + TexelTileSize.x, startY + TexelTileSize.y)))
				{
					selectedStartUV = Vector2(startX, startY);
				}

				count++;

				ImGui::PopID();

				if (count % tileXCount != 0)
					ImGui::SameLine();
			}
		}
	}
	ImGui::End();
}

void TileSet::ChangeTileMap(wstring imagePath, uint xCount, uint yCount)
{
	Texture2D* tex = new Texture2D(imagePath);
	tileSRV = tex->GetSRV();
	SAFE_DELETE(tex);

	// GUI ���� ǥ���� �̹��� ��ư�� X,Y �� ����
	// �̹����� 10x10 ���� �߶� GUI �� ǥ��
	tileXCount = xCount;
	tileYCount = yCount;

	TexelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

