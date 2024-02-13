#include "Framework.h"
#include "TMap.h"

TMap::TMap(uint width, uint height, uint spacing)
	:width(width), height(height), spacing(spacing)
{
	TileSet::Create();

	GenerateTileMap();

	vertices.assign(4, VertexTile());

	vertices[0].position = Values::ZeroVec3;
	vertices[1].position = Vector3(0.0f, (float)spacing, 0.0f);
	vertices[2].position = Vector3((float)spacing, 0.0f, 0.0f);
	vertices[3].position = Vector3((float)spacing, (float)spacing, 0.0f);

	indices = { 0,1,2,2,1,3 };

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexTile.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexTile.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

	wb = new WorldBuffer();
	wb->SetWorld(world);

	inb = new IndexNumBuffer();
	inb->SetIndex(0);

}

TMap::~TMap()
{
	TileSet::Delete();

	for (uint y = 0; y < height; y++)
		SAFE_DELETE_ARRAY(tiles[y]);

	SAFE_DELETE_ARRAY(tiles);

	SAFE_DELETE(inb);
	SAFE_DELETE(wb);

	SAFE_DELETE(il);

	SAFE_DELETE(ps);
	SAFE_DELETE(vs);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TMap::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Down('S'))
		{
			string filename;
			cin >> filename;
			getchar(); // ����Ű �Դ� �뵵 
			Save(TilePath + filename + ".data");
		}
		if (Keyboard::Get()->Down('L'))
		{
			string filename;
			cin >> filename;
			getchar(); // ����Ű �Դ� �뵵 
			Load(TilePath + filename + ".data");
		}
	}
	// ���콺 ��ġ �ҷ�����
	Vector3 mPos = Mouse::Get()->GetPosition();
	// ���콺 ��ġ�� Ÿ�� �ִ��� Ȯ��
	Tile* tile = GetTile(mPos);

	// �ִٸ�
	if (tile != nullptr)
	{
		//�ش� Ÿ�� ��ȣ �˷��ֱ�
		inb->SetIndex(tile->GetIndex());
	}
	// ��Ŭ��
	if (Mouse::Get()->Press(0x0000))
	{
		if (tile != nullptr)
		{
			tile->SetColor(Values::Red);
			Vector2 startUV = TileSet::Get()->selectedStartUV;
			Vector2 endUV = startUV + TileSet::Get()->TexelTileSize;
			tile->SetStartUV(startUV);
			tile->SetEndUV(endUV);
		}
	}
}

void TMap::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();

	DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];

			MapVertexBuffer();
			{
				for (VertexTile& v : vertices)
				{
					v.color = tile.GetColor();
					v.index = tile.GetIndex();
				}
				// Ÿ�� �ǿ� �ö� tile �� uv == ���� ���
				vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
				vertices[1].uv = tile.GetStartUV();
				vertices[2].uv = tile.GetEndUV();
				vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

				// ���� Ÿ�Ͽ� �׷��� �׸� uv
				vertices[0].uv2 = Vector2(0, 1);
				vertices[1].uv2 = Vector2(0, 0);
				vertices[2].uv2 = Vector2(1, 1);
				vertices[3].uv2 = Vector2(1, 0);

			}
			UnmapVertexBuffer();

			world = DXMath::Translation(tile.Getposition());
			wb->SetWorld(world);
			wb->SetVSBuffer(0);
			wb->SetPSBuffer(0);
			inb->SetPSBuffer(0);
			DC->DrawIndexed(ib->GetCount(), 0, 0);
		}
	}
}

void TMap::GUI()
{
	TileSet::Get()->GUI();
}

void TMap::GenerateTileMap()
{
	if (width == 0 || height == 0 || spacing == 0)
	{
		assert(false);
	}

	tiles = new Tile * [height];
	int index = 0;

	for (uint y = 0; y < height; y++)
	{
		tiles[y] = new Tile[width];

		for (uint x = 0; x < width; x++)
		{
			tiles[y][x].Setposition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
			tiles[y][x].SetIndex(index);
			index++;
		}
	}
}

void TMap::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TMap::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void TMap::Save(string path)
{
	ofstream fout(path);
	
	// cout ���¿� ��� �Ʒ��� �����ǵ����͸� �������� ���� �ִ´�.
	// .data �� �ƴ� .txt �� ��½� �״�� �б� ����
	fout << to_string(width) << ' ' << to_string(height) << ' ' << to_string(spacing) << endl;

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];
			string output;
			// startUV �Է�
			output += to_string(tile.GetStartUV().x) + ' ' + to_string(tile.GetStartUV().y) + ' ';
			// endUV �Է�
			output += to_string(tile.GetEndUV().x) + ' ' + to_string(tile.GetEndUV().y);

			fout << output << endl;
		}
	}
}

void TMap::Load(string path)
{
	ifstream fin(path);
	// ���� ���� Ȯ��
	if (fin.fail())
	{
		assert(false);
	}

	for (uint y = 0; y < height; y++)
		SAFE_DELETE_ARRAY(tiles[y]);

	SAFE_DELETE_ARRAY(tiles);
	
	char temp[256];

	// width,height,spacing �ҷ�����

	// temp �� fin�� �������ִ� �������� 255 ���ڸ� �̾Ƽ� ����ֱ�
	fin.getline(temp, 256);
	string t = "";
	
	for (int i = 0; i < 256; i++)
	{
		// �����Ͱ� ������ �ƴϸ� �� ���ڵ� �ƴҰ�� �ش絥���͸� string �� �־�α�
		if (temp[i] != ' ' && temp[i] != '\0')
		{
			t += temp[i];
		}
		else
		{
			if (width == 0)
			{
				width = stoi(t);
				t.clear();
			}
			else if (height == 0)
			{
				height = stoi(t);
				t.clear();
			}
			else if (spacing == 0)
			{
				spacing = stoi(t);
				break;
			}
			continue;
		}
	}
	cout << "Ÿ�ϸ� �ҷ����� : " << path << endl;
	cout << "Width : " << width << endl;
	cout << "Height : " << height << endl;
	cout << "Spacing : " << spacing << endl;
	
	if (width == 0 || height == 0 || spacing == 0)
	{
		assert(false);
	}
	tiles = new Tile * [height];
	int count = 0;
	
	for (uint y = 0; y < height; y++)
	{
		// Ÿ�� ���α��
		tiles[y] = new Tile[width];
		for (uint x = 0; x < width; x++)
		{
			tiles[y][x].Setposition(Vector3((float)(x * spacing), (float)(y * spacing), 0.0f));
			tiles[y][x].SetIndex(count);
			count++;

			fin.getline(temp, 256);
			Vector2 uv;
			string t;

			int flag = 0;
			for (int i = 0; i < 256; i++)
			{
				// i�� 0~8 ������
				// float �� �Ҽ��� ���� 8�ڸ��̱� ������ 8�ڸ��� �д´�.
				if ((i + 1) % 9 == 0)
				{
					if (flag == 0)
					{
						uv.x = stof(t);
						flag++;

						cout << "StartUV.x : " << uv.x << endl;
					}
					else if (flag == 1)
					{
						uv.y = stof(t);
						flag++;
						tiles[y][x].SetStartUV(uv);

						cout << "StartUV.y : " << uv.y << endl;

						uv = Values::ZeroVec2;
					}
					else if (flag == 2)
					{
						uv.x = stof(t);
						flag++;

						cout << "EndUV.x : " << uv.x << endl;
					}
					else if (flag == 3)
					{
						uv.y = stof(t);
						flag++;

						tiles[y][x].SetEndUV(uv);

						cout << "EndUV.y : " << uv.y << endl;
						break;
					}
					t.clear();
					continue;
				}
				else
				{
					t += temp[i];
				}
			}
		}
	}
	// ����� ����
	Save(TilePath + "After.txt");
}

Tile* TMap::GetTile(Vector3 mPos)
{
	uint x = (int)mPos.x / spacing;
	uint y = (int)mPos.y / spacing;

	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;
	return &tiles[y][x];
}
