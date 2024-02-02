#include "stdafx.h"
#include "Avoid_N_Survive.h"


void Avoid_N_Survive::Init()
{
	// ���� �߰�
	AddSounds();

	// �̹��� �߰�
	AddImages();

	// ���� ���
	Sounds::Get()->Play("BGM", 0.2f);

	// �÷��̾� ������ ��������
	player = new Player(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(30, 30, 1), 0.0f);
	player->SetColor(Values::Green);
	player->Update();

	// �׶��� ���� �� ��������
	ground = new Rect(Vector3(WinMaxWidth * 0.5, 10, 0), Vector3(WinMaxWidth, 20, 1), 0.0f);
	ground->SetColor(Values::Green);
	ground->Update();


	// ü���̹��� ����
	CreateHP();
	// �� ����
	CreateEnemy();
}

void Avoid_N_Survive::Destroy()
{
	for (Enemy* E : enemy)
	{
		SAFE_DELETE(E);
	}
	for (TextureRect* Hp : hp)
	{
		SAFE_DELETE(Hp);
	}
	SAFE_DELETE(scoreimg);
	SAFE_DELETE(ground);
	SAFE_DELETE(player);
}

void Avoid_N_Survive::Update()
{
	if (death && Keyboard::Get()->Down('R'))
	{
		Reset();
	}
	if (!death)
	{
		GameOver();
		// ���� �ð� ���� �Լ� ����
		GameTime();
		// ���� ���� �ο� �Լ�
		RandomPattern();
		// �÷��̾� ������ ���� �Լ� �ҷ�����
		player->Control();
		player->IsWall();
		// �÷��̾� ���� ����
		player->Immu();
		// �浹 ����
		Hit();

		// �÷��̾�� �� �浹 Ȯ��
		IsGround();


		player->Update();
		ground->Update();

		for (Enemy* E : enemy)
			E->Update();
		for (TextureRect* HP : hp)
			HP->Update();
	}
	else if (death)
	{
		Rank();
		scoreimg->Update();
		img_GameOver->Update();
		for (TextureRect* R : rank)
		{
			R->Update();
		}
	}
}

void Avoid_N_Survive::Render()
{
	if (!death)
	{
		for (Enemy* E : enemy)
			E->Render();
		for (TextureRect* HP : hp)
			HP->Render();
		ground->Render();
		player->Render();
	}
	else if (death)
	{
		img_GameOver->Render();
		scoreimg->Render();
		for (TextureRect* R : rank)
			R->Render();
	}

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
			printf("Hp : %d \n", player->GetHp());
			printf("Immu : %d\n", player->GetImmu());
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
	// �÷��̾�� ���� �浹�� �÷��̾� ������ SetGround �Լ��� true ����
	if (BoundingBox::AABB(player->GetCollision(), ground->GetCollision()) == true)
	{
		player->SetGroud(true);
	}
	// �÷��̾��� ground�� Ȱ���� ��� �÷��̾��� ��ġ�� �׶���� �浹�����ʴ� �������� ����
	if (player->GetGround())
	{
		Vector3 g_pos = ground->GetPosition();
		Vector3 p_pos = player->GetPosition();
		player->SetPositionY(g_pos.y + 25.1f);
	}
}

void Avoid_N_Survive::SetHPposition()
{
	// �÷��̾��� ü�º��� ���� ������ ��ġ �̵�
	int php = player->GetHp();
	if (player->GetHp() <= 4)
	{
		hp[php]->SetPositionY(hp[php]->GetPosition().y * 2);
	}
}

void Avoid_N_Survive::GameOver()
{
	if (!death && player->GetHp() == 0)
	{
		death = true;
		Sounds::Get()->Stop("BGM");
	}
}

void Avoid_N_Survive::Reset()
{
	Sounds::Get()->Play("BGM", 0.2f);
	// �÷��̾� ���� �ʱ�ȭ
	player->Sethp(5);
	player->SetPosition(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0));
	// �׶��� ���� �ʱ�ȭ
	ground->SetPositionY(10);
	ground->Setalpha(1);
	// ���� �� �ð� �ʱ�ȭ
	pscore = 0;
	playtime_s = 0;
	playtime_m = 0;
	// ���� ��� �ʱ�ȭ
	pattern = false;
	pTime = 0;
	pNumber = 0;
	fallcount = 0;
	onsound = false;
	// �� ��ü ���� �ʱ�ȭ
	for (Enemy* E : enemy)
	{
		E->SetPosition(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0));
		E->Setalpha(0.f);
		E->SetMoveNum(0);
	}
	// ü�� �ʱ�ȭ
	hp[0]->SetPosition(Vector3(50, WinMaxHeight - 50, 0));
	hp[1]->SetPosition(Vector3(75 + 5, WinMaxHeight - 50, 0));
	hp[2]->SetPosition(Vector3(100 + 10, WinMaxHeight - 50, 0));
	hp[3]->SetPosition(Vector3(125 + 15, WinMaxHeight - 50, 0));
	hp[4]->SetPosition(Vector3(150 + 20, WinMaxHeight - 50, 0));
	death = false;
}

void Avoid_N_Survive::Rank()
{
	if (playtime_s < 20)
	{
		rank[6]->SetPosition(Vector3(WinMaxWidth * 0.5 + 50, WinMaxHeight * 0.5f - 100, 0));
	}
	else
	{
		rank[6]->SetPosition(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0));
	}
	if (playtime_s > 39)
	{
		rank[7]->SetPosition(Vector3(WinMaxWidth * 0.5 + 50, WinMaxHeight * 0.5f - 100, 0));
	}
	else
	{
		rank[7]->SetPosition(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0));
	}
	// ��ũ ���� ���
	{
		rank[playtime_m]->SetPosition(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5 - 100, 0));
	}
}

void Avoid_N_Survive::Hit()
{
	// �÷��̾�� �� ��ü�� �浹�� ü�� ���� �� �������� �ο�
	for (Enemy* E : enemy)
	{
		if (BoundingBox::AABB(player->GetCollision(), E->GetCollision()) == true && !player->GetImmu())
		{
			player->SetImmu(true);
			player->Sethp(player->GetHp() - 1);
			// �÷��̾� ü�¸�ŭ hp �̹��� ���
			SetHPposition();
		}
	}
}

void Avoid_N_Survive::AddSounds()
{
	// ���� BGM
	Sounds::Get()->addSound("BGM", SoundPath + L"ANS.mp3", true);
	// ȿ����
	Sounds::Get()->addSound("UpSound", SoundPath + L"tower.mp3");
}

void Avoid_N_Survive::AddImages()
{
	// ���ھ� �̹���
	scoreimg = new TextureRect(Vector3(WinMaxWidth * 0.5 - 100, WinMaxHeight * 0.5 - 100, 0), Vector3(128, 72, 1), 0.0f, TexturePath + L"Score.png");
	// ���� ���� �̹���
	img_GameOver = new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(1280, 720, 1), 0.0f, TexturePath + L"GameOver.png");
	// ��ũ �̹���
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"F.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"E.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"D.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"C.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"B.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"A.png"));

	// + - �̹���
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"-.png")); // [6]
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"+.png")); // [7]

}

void Avoid_N_Survive::CreateHP()
{
	// ü�� �̹��� ����
	hp.push_back(new TextureRect(Vector3(50, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(75 + 5, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(100 + 10, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(125 + 15, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(150 + 20, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
}

void Avoid_N_Survive::CreateEnemy()
{
	// ����ü ����
	for (int i = 0; i < 10; i++)
	{
		enemy.push_back(new Enemy(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
		enemy[i]->SetColor(Values::Red);
		enemy[i]->Setalpha(0.f);
	}
}

void Avoid_N_Survive::RandomPattern()
{
	// ���� ���� �ο�
	if (pattern)
	{
		pNumber = Random::GetRandomInt(1, 1);
		if (pNumber == 1)
		{
			Firstpattern();
		}
	}
}

void Avoid_N_Survive::Firstpattern()
{
	// ����ž �Ʒ�
	Vector3 g_pos = ground->GetPosition();
	Vector3 p_pos = player->GetPosition();
	if (!onsound)
	{
		Sounds::Get()->Play("UpSound", 0.2f);
		onsound = true;
	}
	// �׶��� ���ݾ� ���� �̵�
	if (g_pos.y < WinMaxHeight - 100)
	{
		g_pos.y += 120 * Time::Delta();
		ground->SetPosition(g_pos);
	}

	// �׶����� ��ġ�� WinMaxHeight-100 �̻��϶�
	if (ground->GetPosition().y >= WinMaxHeight - 100)
	{

		// �׶��� ���İ� ������
		if (ground->GetAlpha() >= 0.f)
		{
			ground->Setalpha(ground->GetAlpha() - 0.005f);
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
				E->Setalpha(E->GetAlpha() + 0.007f);
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
			fallcount++;
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
	// ���� ���� �ڵ�
	if (fallcount > 5)
	{
		pNumber = 0;
		pattern = false;
		onsound = false;
		ground->SetPositionY(10);
		ground->Setalpha(1.f);
		for (Enemy* E : enemy)
		{
			E->SetMoveNum(0);
			E->SetPosition(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0));
			E->Setalpha(0);
		}
	}


}


