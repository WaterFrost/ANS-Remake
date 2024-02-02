#include "stdafx.h"
#include "Avoid_N_Survive.h"


void Avoid_N_Survive::Init()
{
	// 사운드 추가
	AddSounds();

	// 이미지 추가
	AddImages();

	// 음악 재생
	Sounds::Get()->Play("BGM", 0.2f);

	// 플레이어 생성및 색상지정
	player = new Player(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(30, 30, 1), 0.0f);
	player->SetColor(Values::Green);
	player->Update();

	// 그라운드 생성 및 색상지정
	ground = new Rect(Vector3(WinMaxWidth * 0.5, 10, 0), Vector3(WinMaxWidth, 20, 1), 0.0f);
	ground->SetColor(Values::Green);
	ground->Update();


	// 체력이미지 생성
	CreateHP();
	// 적 생성
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
		// 게임 시간 관련 함수 모음
		GameTime();
		// 랜덤 패턴 부여 함수
		RandomPattern();
		// 플레이어 움직임 관련 함수 불러오기
		player->Control();
		player->IsWall();
		// 플레이어 무적 판정
		player->Immu();
		// 충돌 판정
		Hit();

		// 플레이어와 땅 충돌 확인
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
			printf("Hp : %d \n", player->GetHp());
			printf("Immu : %d\n", player->GetImmu());
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
	// 플레이어와 땅의 충돌시 플레이어 내부의 SetGround 함수에 true 전달
	if (BoundingBox::AABB(player->GetCollision(), ground->GetCollision()) == true)
	{
		player->SetGroud(true);
	}
	// 플레이어의 ground가 활성일 경우 플레이어의 위치를 그라운드와 충돌하지않는 조금위로 변경
	if (player->GetGround())
	{
		Vector3 g_pos = ground->GetPosition();
		Vector3 p_pos = player->GetPosition();
		player->SetPositionY(g_pos.y + 25.1f);
	}
}

void Avoid_N_Survive::SetHPposition()
{
	// 플레이어의 체력보다 높은 순서는 위치 이동
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
	// 플레이어 상태 초기화
	player->Sethp(5);
	player->SetPosition(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0));
	// 그라운드 상태 초기화
	ground->SetPositionY(10);
	ground->Setalpha(1);
	// 점수 및 시간 초기화
	pscore = 0;
	playtime_s = 0;
	playtime_m = 0;
	// 패턴 기록 초기화
	pattern = false;
	pTime = 0;
	pNumber = 0;
	fallcount = 0;
	onsound = false;
	// 적 객체 상태 초기화
	for (Enemy* E : enemy)
	{
		E->SetPosition(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0));
		E->Setalpha(0.f);
		E->SetMoveNum(0);
	}
	// 체력 초기화
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
	// 랭크 글자 출력
	{
		rank[playtime_m]->SetPosition(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5 - 100, 0));
	}
}

void Avoid_N_Survive::Hit()
{
	// 플레이어거 적 개체와 충돌시 체력 감소 및 무적판정 부여
	for (Enemy* E : enemy)
	{
		if (BoundingBox::AABB(player->GetCollision(), E->GetCollision()) == true && !player->GetImmu())
		{
			player->SetImmu(true);
			player->Sethp(player->GetHp() - 1);
			// 플레이어 체력만큼 hp 이미지 출력
			SetHPposition();
		}
	}
}

void Avoid_N_Survive::AddSounds()
{
	// 메인 BGM
	Sounds::Get()->addSound("BGM", SoundPath + L"ANS.mp3", true);
	// 효과음
	Sounds::Get()->addSound("UpSound", SoundPath + L"tower.mp3");
}

void Avoid_N_Survive::AddImages()
{
	// 스코어 이미지
	scoreimg = new TextureRect(Vector3(WinMaxWidth * 0.5 - 100, WinMaxHeight * 0.5 - 100, 0), Vector3(128, 72, 1), 0.0f, TexturePath + L"Score.png");
	// 게임 오버 이미지
	img_GameOver = new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(1280, 720, 1), 0.0f, TexturePath + L"GameOver.png");
	// 랭크 이미지
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"F.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"E.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"D.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"C.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"B.png"));
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 3, WinMaxHeight * 3, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"A.png"));

	// + - 이미지
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"-.png")); // [6]
	rank.push_back(new TextureRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(38, 67, 1), 0.0f, TexturePath + L"+.png")); // [7]

}

void Avoid_N_Survive::CreateHP()
{
	// 체력 이미지 생성
	hp.push_back(new TextureRect(Vector3(50, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(75 + 5, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(100 + 10, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(125 + 15, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
	hp.push_back(new TextureRect(Vector3(150 + 20, WinMaxHeight - 50, 0), Vector3(25, 50, 1), 0.0f, TexturePath + L"playerHP.png"));
}

void Avoid_N_Survive::CreateEnemy()
{
	// 적객체 생성
	for (int i = 0; i < 10; i++)
	{
		enemy.push_back(new Enemy(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
		enemy[i]->SetColor(Values::Red);
		enemy[i]->Setalpha(0.f);
	}
}

void Avoid_N_Survive::RandomPattern()
{
	// 랜덤 패턴 부여
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
	// 모형탑 훈련
	Vector3 g_pos = ground->GetPosition();
	Vector3 p_pos = player->GetPosition();
	if (!onsound)
	{
		Sounds::Get()->Play("UpSound", 0.2f);
		onsound = true;
	}
	// 그라운드 조금씩 위로 이동
	if (g_pos.y < WinMaxHeight - 100)
	{
		g_pos.y += 120 * Time::Delta();
		ground->SetPosition(g_pos);
	}

	// 그라운드의 위치가 WinMaxHeight-100 이상일때
	if (ground->GetPosition().y >= WinMaxHeight - 100)
	{

		// 그라운드 알파값 내리기
		if (ground->GetAlpha() >= 0.f)
		{
			ground->Setalpha(ground->GetAlpha() - 0.005f);
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
				E->Setalpha(E->GetAlpha() + 0.007f);
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
			fallcount++;
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
	// 패턴 종료 코드
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


