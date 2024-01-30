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
	// 게임 시간 관련 함수 모음
	GameTime();
	// 랜덤 패턴 부여 함수
	RandomPattern();
	// 플레이어 움직임 관련 함수 불러오기
	player->Control();
	player->IsWall();

	// 플레이어와 땅 충돌 확인
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
		// 1초 마다 -1
		deltatime = 0;

		// 패턴 출력 시간 관리
		if (!pattern)
		{
			pTime++;
			if (pTime >= 3)
			{
				pattern = true;
				pTime = 0;
			}
		}

		// 플레이 초 단위 표기
		playtime_s++;
		if (playtime_s < 60 && playtime_m == 0)
		{
			printf("PlayTime : %d second\n", playtime_s);
		}

		// 플레이 분 단위 표기
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
	// 그라운드 조금씩 위로 이동
	if (g_pos.y < WinMaxHeight - 100)
	{
		g_pos.y += 100 * Time::Delta();
		ground->SetPosition(g_pos);
	}

	// 그라운드의 위치가 WinMaxHeight-100 이상일때
	if (ground->GetPosition().y >= WinMaxHeight - 100)
	{
		// 그라운드 알파값 내리기
		if (ground->GetAlpha() >= 0.f)
		{
			ground->Setalpha(ground->GetAlpha() - 0.001f);
		}
		// 그라운드 알파값일정치 이하시 위치 이동 및 플레이어의 그라운드 판정 비활성화
		else if (ground->GetAlpha() <= 0.f)
		{
			ground->SetPositionY(WinMaxHeight * 2);
			player->SetGroud(false);
		}
		// 마지막 적 개체의  포지션 Y값이 화면 밖일때 화면 안쪽 랜덤한 위치 부여
		if (enemy[9]->GetPositionY() > WinMaxHeight)
		{
			for (Enemy* E : enemy)
			{
				E->GetRandomPosition(0, WinMaxWidth, 100, WinMaxHeight - 150);
			}
		}
		// 마지막 적 개체의 알파값이 1보다 작을때 알파값 조정
		if (enemy[4]->GetAlpha() < 1.f)
		{
			for (Enemy* E : enemy)
			{
				E->Setalpha(E->GetAlpha() + 0.001f);
			}
		}
		
		// 마지막 적 객체의 알파값이 1이상일때 이동 활성화
		if (enemy[4]->GetAlpha() >= 1.0f)
		{
			for (Enemy* E : enemy)
			{
				E->Move();
			}
		}
		// 플레이어 Y값이 0이하일때 위로 올리는 코드
		if (p_pos.y < 0)
		{
			p_pos.y = WinMaxHeight + 150;
			player->SetPosition(p_pos);
		}
	}
	//적의위치가 중간 보다 왼쪽일때 오른쪽으로 이동하는 코드 부여
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


