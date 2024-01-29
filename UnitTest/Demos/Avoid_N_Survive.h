#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "ANS/Player.h"
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
	void GameTimer(); // 게임시간 측정후 시간 출력 및 패턴 출력 용도
	void IsGround(); // ground 와 player 확인
	void Firstpattern(); // 첫번째 패턴
private:

	// 그림 관련
	Player* player;
	Rect* ground;

	// 변수 관련
	
	// 플레이 시간
	float deltatime = 0.f;
	int playtime_s = 0;
	int playtime_m = 0;
	// 패턴 활성화 전용
	bool pattern = false;
	int pTime = 0;
};