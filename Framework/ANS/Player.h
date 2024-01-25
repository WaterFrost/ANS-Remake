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
	// Setter
	void Sethp(int point) { hp = point; }
	// Getter
	int GetHp() { return hp; }
private:
	int hp = 5;

	float immudelay = 0.0f;
	float gravity = 0.0f;
	// 무적관련
	bool immu = false;
	// 이동관련
	bool moveR = false;
	// 점프 관련
	Vector3 Oldpos = GetPosition();
	float jumptime = 0;
	bool jump = false;
	bool airhop = false;
	bool fall = false;

	
};