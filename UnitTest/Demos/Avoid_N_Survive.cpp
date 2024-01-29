#include "stdafx.h"
#include "Avoid_N_Survive.h"


void Avoid_N_Survive::Init()
{
	player = new Player(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(30, 30, 1), 0.0f);
	player->SetColor(Values::Green);
	player->Update();

	ground = new Rect(Vector3(WinMaxWidth * 0.5, 10, 0), Vector3(WinMaxWidth, 20, 1), 0.0f);
	ground->SetColor(Values::Green);
	ground->Update();

	Sounds::Get()->addSound("BGM", SoundPath + L"ANS.mp3", true);
	Sounds::Get()->Play("BGM", 0.2f);

}

void Avoid_N_Survive::Destroy()
{
	SAFE_DELETE(ground);
	SAFE_DELETE(player);
}

void Avoid_N_Survive::Update()
{
	// ���� �ð� ���� �Լ� ����
	GameTime();
	// ���� ���� �ο� �Լ�
	RandomPattern();
	// �÷��̾� ������ ���� �Լ� �ҷ�����
	player->Control();
	player->IsWall();

	// �÷��̾�� �� �浹 Ȯ��
	IsGround();

	player->Update();
	ground->Update();
}

void Avoid_N_Survive::Render()
{
	ground->Render();
	player->Render();
}

void Avoid_N_Survive::PostRender()
{
}

void Avoid_N_Survive::GUI()
{
}

void Avoid_N_Survive::GameTime()
{
	deltatime += Time::Delta();
	if (deltatime >= 1)
	{
		// 1�� ���� -1
		deltatime--;

		// ���� ��� �ð� ����
		
		if (!pattern)
		{
			pTime++;
			if (pTime < 3)
			{
				pattern = true;
			}
		}
		// �÷��� �� ���� ǥ��
		playtime_s++;
		if (playtime_s < 60 && playtime_m == 0)
		{
			printf("PlayTime : %d second\n", playtime_s);
		}
		// �÷��� �� ���� ǥ��
		else if (playtime_s == 60)
		{
			playtime_m++;
			playtime_s = 0;
		}
		if (playtime_m >= 1)
		{
			printf("PlayTime : %d minute %d second\n", playtime_m, playtime_s);
		}
	}
}

void Avoid_N_Survive::IsGround()
{
	if (BoundingBox::AABB(player->GetCollision(), ground->GetCollision()) == true)
	{
		player->SetGroud(true);
	}
	if (player->GetGround())
	{
		Vector3 g_pos = ground->GetPosition();
		Vector3 p_pos = player->GetPosition();
		player->SetPositionY(g_pos.y + 25.1f);
	}
}

void Avoid_N_Survive::RandomPattern()
{
	if (pattern)
	{
		pNumber = Random::GetRandomInt(1, 1);
		if (pNumber == 1)
			Firstpattern();
	}
}

void Avoid_N_Survive::Firstpattern()
{
	Vector3 g_pos = ground->GetPosition();
	if (g_pos.y < WinMaxHeight - 100)
	{
		g_pos.y += 100 * Time::Delta();
		ground->SetPosition(g_pos);
	}
}


