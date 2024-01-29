#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "ANS/Player.h"
class Player : public Rect
{
public:

	Player(Vector3 position, Vector3 size, float rotation);
	~Player();

	void Control();
	void Immu();
	void IsWall();
	// Setter
	void Sethp(int point) { hp = point; }
	void SetGroud(bool state) { ground = state; }
	void SetJumpScale(float power) { jumpPower = power; }
	void SetImmu(bool set) { immu = set; }

	// Getter
	int GetHp() { return hp; }
	float GetJumpPower() { return jumpPower; }
	bool GetGround() { return ground; }
	bool GetImmu() { return immu; }
private:
	
	// 플레이어 상태
	int hp = 5;

	bool jump = false;
	bool doublejump = false;
	bool fall = false;
	bool ground = true;

	// 무적관련
	float immudelay = 0.0f;
	bool immu = false;

	// 이동관련
	bool moveR = false;

	// 점프 관련
	float jumptime = 0.f;
	float jumpPower = 2.5f;
	

	
};