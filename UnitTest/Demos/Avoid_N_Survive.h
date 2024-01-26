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
	void IsGround(); // ground 와 player 확인
private:
	// 그림 관련
	Player* player;
	Rect* ground;

	// 변수 관련

};