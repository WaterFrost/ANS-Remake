#include "stdafx.h"
#include "02_CollisionDemo.h"
#include "Geomatries/Rect.h"
void CollisionDemo::Init()
{
	// Player
	{
		player = new Rect(Vector3(WinMaxWidth * 0.5 - 375, WinMaxHeight * 0.5, 0), Vector3(35, 35, 1), 0.0f);
		Players.push_back(player);
		player = new Rect(Vector3(WinMaxWidth * 0.5 - 375, WinMaxHeight * 0.5, 0), Vector3(25, 25, 1), 0.0f);
		Players.push_back(player);
	}

	goal = new Rect(Vector3(WinMaxWidth * 0.5+375, WinMaxHeight * 0.5, 0), Vector3(150, 300, 1), 0.0f);
	start = new Rect(Vector3(WinMaxWidth * 0.5-375, WinMaxHeight * 0.5, 0), Vector3(150, 300, 1), 0.0f);
	// Road
	{
		road = new Rect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(500, 200, 1), 0.0f);
		Roads.push_back(road);
		road = new Rect(Vector3(WinMaxWidth * 0.5 + 250, WinMaxHeight * 0.5 + 125, 0), Vector3(100, 50, 1), 0.0f);
		Roads.push_back(road);
		road = new Rect(Vector3(WinMaxWidth * 0.5 - 250, WinMaxHeight * 0.5 - 125, 0), Vector3(100, 50, 1), 0.0f);
		Roads.push_back(road);
	}

	// Wall
	{
		wall = new Rect(Vector3(WinMaxWidth * 0.5 + 25, WinMaxHeight * 0.5 - 125, 0), Vector3(450, 50, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5 - 25, WinMaxHeight * 0.5 + 125, 0), Vector3(450, 50, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5 + 275, WinMaxHeight * 0.5 - 25, 0), Vector3(50, 250, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5 - 275, WinMaxHeight * 0.5 + 25, 0), Vector3(50, 250, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5 + 175, 0), Vector3(900, 50, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5 - 175, 0), Vector3(900, 50, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5 + 475, WinMaxHeight * 0.5, 0), Vector3(50, 400, 1), 0.0f);
		Walls.push_back(wall);
		wall = new Rect(Vector3(WinMaxWidth * 0.5 - 475, WinMaxHeight * 0.5, 0), Vector3(50, 400, 1), 0.0f);
		Walls.push_back(wall);
	}

	// Enemy
	{
		for (int i = 0; i < 4; i++)
		{
			if (i % 2 == 0)
			{
				enemy = new Rect(Vector3(WinMaxWidth * 0.5 - 175, WinMaxHeight * 0.5 + 75 - (i / 2 * 100), 0), Vector3(20, 20, 1), 0.0f);
				Enemys.push_back(enemy);
				enemy = new Rect(Vector3(WinMaxWidth * 0.5 - 175, WinMaxHeight * 0.5 + 75 - (i / 2 * 100), 0), Vector3(30, 30, 1), 0.0f);
				Enemys.push_back(enemy);
			}
			else
			{
				enemy = new Rect(Vector3(WinMaxWidth * 0.5 + 175, WinMaxHeight * 0.5 + 25 - (i / 2 * 100), 0), Vector3(20, 20, 1), 0.0f);
				Enemys.push_back(enemy);
				enemy = new Rect(Vector3(WinMaxWidth * 0.5 + 175, WinMaxHeight * 0.5 + 25 - (i / 2 * 100), 0), Vector3(30, 30, 1), 0.0f);
				Enemys.push_back(enemy);
			}
		}
	}
}

void CollisionDemo::Destroy()
{
	SAFE_DELETE(enemy);
	SAFE_DELETE(wall);
	SAFE_DELETE(road);
	SAFE_DELETE(start);
	SAFE_DELETE(goal);
	SAFE_DELETE(player);
	Players.clear();
	Roads.clear();
	Walls.clear();
	Enemys.clear();
}

void CollisionDemo::Update()
{
	Vector3 p_pos, e_pos, w_pos;
	for (int i = 0; i < Players.size(); i++)
	{
		if (!Checkwall)
			Players[i]->Move();
	}
	MoveEnemys();
	Players[0]->SetColor(Values::Black);
	goal->SetColor(Values::Green);
	start->SetColor(Values::Green);

	for (int i = 0; i < Roads.size(); i++)
	{
		Roads[i]->SetColor(Values::White);
	}
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i]->SetColor(Values::ClearColor);
	}

	for (int i = 0; i < Enemys.size(); i++)
	{
		if (i % 2 == 0)
			Enemys[i]->SetColor(Values::Blue);
		else
			Enemys[i]->SetColor(Values::Black);
	}
	// 도착 판정
	if (BoundingBox::AABB(Players[1]->GetCollision(), goal->GetCollision()) == true)
	{
		for (int i = 0; i < Players.size(); i++)
			Players[i]->SetColor(Values::ClearColor);
	}
	else
	{
		Players[1]->SetColor(Values::Red);
	}
	// 대각선판정 수정 방법
	// 1. 상하,좌우 벽을 각 다른벡터로 적용후 제각각 판정을 만든다.
	// 2. 충돌 위치를 확인후에 키 입력을 받지 못하게 한다.
	// 3. 뭐였지
	// 플레이어 > 벽 판정
	for (int i = 0; i < Walls.size(); i++)
	{
		if (BoundingBox::AABB(Players[1]->GetCollision(), Walls[i]->GetCollision()) == true)
		{
			Checkwall = true;
			{
				if (Players[1].Setposition >= Walls[i]->position.x && Keyboard::Get()->Press(VK_LEFT))
				{
					Players[0]->position.x = Players[0]->position.x + 1;
					Players[1]->position.x = Players[1]->position.x + 1;
				}
				else if (Players[1]->position.x <= Walls[i]->position.x && Keyboard::Get()->Press(VK_RIGHT))
				{
					Players[0]->position.x = Players[0]->position.x - 1;
					Players[1]->position.x = Players[1]->position.x - 1;
				}
				else if (Players[1]->position.y >= Walls[i]->position.y && Keyboard::Get()->Press(VK_DOWN))
				{
					Players[0]->position.y = Players[0]->position.y + 1;
					Players[1]->position.y = Players[1]->position.y + 1;
				}
				else if (Players[1]->position.y <= Walls[i]->position.y && Keyboard::Get()->Press(VK_UP))
				{
					Players[0]->position.y = Players[0]->position.y - 1;
					Players[1]->position.y = Players[1]->position.y - 1;
				}
			}
			Checkwall = false;
		}
	}

	// 적 좌우 무빙
	for (int i = 0; i < Enemys.size(); i++)
	{
		if (BoundingBox::AABB(Enemys[i]->GetCollision(), Walls[2]->GetCollision()) == true)
		{
			if (Left)
			{
				Left = false;
			}
		}
		else if(BoundingBox::AABB(Enemys[i]->GetCollision(), Walls[3]->GetCollision()) == true)
		{
			if (!Left)
			{
				Left = true;
			}
		}
	}
	// 플레이어 > 적 히트 판정
	for (int i = 0; i < Enemys.size(); i++)
	{
		if (BoundingBox::AABB(Players[1]->GetCollision(), Enemys[i]->GetCollision()) == true)
		{
			CheckHit = true;
			if (CheckHit)
			{
				for (int i = 0; i < Players.size(); i++)
				{
					Players[i]->SetPosition().x = WinMaxWidth * 0.5 - 375;
					Players[i]->position.y = WinMaxHeight * 0.5;
				}
			}
		}
		else
		{
			CheckHit = false;
		}
	}
	
	goal->Update();
	start->Update();
	// 플레이어 업데이트
	for (int i = 0; i < Players.size(); i++)
	{
		if (Players.size() == 0)
			return;
		Players[i]->Update();
	}
	// 길 업데이트
	for (int i = 0; i < Roads.size(); i++)
	{
		Roads[i]->Update();
	}
	// 적 업데이트
	for (int i = 0; i < Enemys.size(); i++)
	{
		Enemys[i]->Update();
	}
	// 벽 업데이트
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i]->Update();
	}
}

void CollisionDemo::Render()
{
	// 길 렌더
	for (int i = 0; i < Roads.size(); i++)
	{
		Roads[i]->Render();
	}
	// 벽 렌더
	for (int i = 0; i < Walls.size(); i++)
	{
		Walls[i]->Render();
	}

	goal->Render();
	start->Render();
	
	// 플레이어 렌더
	for (int i = 0; i < Players.size(); i++)
	{
		if (Players.size() == 0)
			return;
		Players[i]->Render();
	}

	// 적 렌더
	for (int i = 0; i <Enemys.size(); i++)
	{
		if (i % 2 == 1)
			Enemys[i]->Render();
	}
	for (int i = 0; i <Enemys.size(); i++)
	{
		if (i % 2 == 0)
			Enemys[i]->Render();
	}
	
	
}

void CollisionDemo::PostRender()
{
}

void CollisionDemo::GUI()
{
}

void CollisionDemo::MoveEnemys()
{
	if (Left)
	{
		Enemys[0]->position.x = Enemys[0]->position.x - 1;
		Enemys[1]->position.x = Enemys[0]->position.x;
		Enemys[4]->position.x = Enemys[0]->position.x;
		Enemys[5]->position.x = Enemys[0]->position.x;

		Enemys[2]->position.x = Enemys[2]->position.x + 1;
		Enemys[3]->position.x = Enemys[2]->position.x;
		Enemys[6]->position.x = Enemys[2]->position.x;
		Enemys[7]->position.x = Enemys[2]->position.x;
	}
	if (!Left)
	{
		Enemys[0]->position.x = Enemys[0]->position.x + 1;
		Enemys[1]->position.x = Enemys[0]->position.x ;
		Enemys[4]->position.x = Enemys[0]->position.x ;
		Enemys[5]->position.x = Enemys[0]->position.x ;

		Enemys[2]->position.x = Enemys[2]->position.x - 1;
		Enemys[3]->position.x = Enemys[2]->position.x ;
		Enemys[6]->position.x = Enemys[2]->position.x ;
		Enemys[7]->position.x = Enemys[2]->position.x ;
	}
}

