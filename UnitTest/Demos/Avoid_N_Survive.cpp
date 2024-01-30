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

	CreateEnemy();
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
	for (Enemy* E : enemy)
		E->Update();
}

void Avoid_N_Survive::Render()
{
	for (Enemy* E : enemy)
		E->Render();
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
		deltatime = 0;

		// ���� ��� �ð� ����
		if (!pattern)
		{
			pTime++;
			if (pTime >= 3)
			{
				pattern = true;
				pTime = 0;
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

void Avoid_N_Survive::CreateEnemy()
{
	for (int i = 0; i < 10; i++)
	{
		enemy.push_back(new Enemy(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
		enemy[i]->SetColor(Values::Red);
		enemy[i]->Setalpha(0.f);
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
	Vector3 p_pos = player->GetPosition();
	// �׶��� ���ݾ� ���� �̵�
	if (g_pos.y < WinMaxHeight - 100)
	{
		g_pos.y += 100 * Time::Delta();
		ground->SetPosition(g_pos);
	}

	// �׶����� ��ġ�� WinMaxHeight-100 �̻��϶�
	if (ground->GetPosition().y >= WinMaxHeight - 100)
	{
		// �׶��� ���İ� ������
		if (ground->GetAlpha() >= 0.f)
		{
			ground->Setalpha(ground->GetAlpha() - 0.001f);
		}
		// �׶��� ���İ�����ġ ���Ͻ� ��ġ �̵� �� �÷��̾��� �׶��� ���� ��Ȱ��ȭ
		else if (ground->GetAlpha() <= 0.f)
		{
			ground->SetPositionY(WinMaxHeight * 2);
			player->SetGroud(false);
		}
		// ������ �� ��ü��  ������ Y���� ȭ�� ���϶� ȭ�� ���� ������ ��ġ �ο�
		if (enemy[9]->GetPositionY() > WinMaxHeight)
		{
			for (Enemy* E : enemy)
			{
				E->GetRandomPosition(0, WinMaxWidth, 100, WinMaxHeight - 150);
			}
		}
		// ������ �� ��ü�� ���İ��� 1���� ������ ���İ� ����
		if (enemy[4]->GetAlpha() < 1.f)
		{
			for (Enemy* E : enemy)
			{
				E->Setalpha(E->GetAlpha() + 0.001f);
			}
		}
		
		// ������ �� ��ü�� ���İ��� 1�̻��϶� �̵� Ȱ��ȭ
		if (enemy[4]->GetAlpha() >= 1.0f)
		{
			for (Enemy* E : enemy)
			{
				E->Move();
			}
		}
		// �÷��̾� Y���� 0�����϶� ���� �ø��� �ڵ�
		if (p_pos.y < 0)
		{
			p_pos.y = WinMaxHeight + 150;
			player->SetPosition(p_pos);
		}
	}
	//������ġ�� �߰� ���� �����϶� ���������� �̵��ϴ� �ڵ� �ο�
	for (Enemy* E : enemy)
	{
		if (E->GetMoveNum() == 0)
		{
			if (E->GetPositionX() < WinMaxWidth * 0.5)
			{
				E->SetMoveNum(1);
				E->SetSpeed(Random::GetRandomInt(100, 500));
			}
			else if (E->GetPositionX() > WinMaxWidth * 0.5)
			{
				E->SetMoveNum(2);
				E->SetSpeed(Random::GetRandomInt(100, 500));
			}
		}
		if (E->GetPositionX() - 25 < 0)
		{
			E->SetMoveNum(1);
		}
		else if (E->GetPositionX() + 25 > WinMaxWidth)
		{
			E->SetMoveNum(2);
		}
		
	}
	
	
}


