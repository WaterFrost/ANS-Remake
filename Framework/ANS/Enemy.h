#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
class Enemy : public Rect
{
public:
	Enemy(Vector3 position,Vector3 size,float rotation);
	~Enemy();

	void GetRandomPosition(int minX, int maxX, int minY, int maxY);
	void Move();

	// setter
	void SetMoveNum(int move) { moveNum = move; }
	void SetSpeed(int speed) { movespeed = speed; }
	// getter
	bool GetMoveNum() { return moveNum; }
private:
	
	int moveNum = 0;
	int movespeed = 100;
};