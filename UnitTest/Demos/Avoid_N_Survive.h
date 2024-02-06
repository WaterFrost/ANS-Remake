#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "ANS/Player.h"
#include "ANS/Enemy.h"
class Avoid_N_Survive : public IObject
{
	// IObject을(를) 통해 상속됨
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

	// ANS 관련함수
	void GameTime(); // 게임시간 측정후 시간 출력 및 패턴 출력 용도
	void IsGround(); // ground 와 player 확인
	void SetHPposition(); // 플레이어 체력에 따른 이미지 출력
	void GameOver(); // 게임 오버 출력
	void Reset(); // 게임오버시 R키를 눌러 재시작
	void Rank(); // 플레이 시간에 따른 랭크출력
	void Hit(); // 피격판정
	
	// 생성 관련 함수
	void AddSounds(); // 사운드 추가
	void AddImages(); // 이미지 추가
	void CreateHP(); // 체력 생성
	void CreateEnemy(); // 적 객체 생성
	

	// 패턴 관련 함수
	void RandomPattern(); // 랜덤 패턴 부여 함수
	void Firstpattern(); // 첫번째 패턴
	void Secondpattern(); // 두번째 패턴
private:

	// 그림 관련
	Player* player;
	Rect* ground;

	// 이미지
	TextureRect* scoreimg;
	TextureRect* img_GameOver;

	vector<TextureRect*> hp;
	vector<TextureRect*> rank;
	vector<Enemy*> enemy;

	// 게임 플레이 관련
	bool death = false;
	// 점수 관련
	int pscore = 0;

	// 플레이 시간
	float deltatime = 0.f;
	int playtime_s = 0;
	int playtime_m = 0;

	// 패턴 활성화 전용
	bool pattern = false;
	int pTime = 0;
	int pNumber = 0;

	// 이한석 패턴
	int fallcount = 0;
	
	bool onsound = false;
	bool Isvisible = true;

};