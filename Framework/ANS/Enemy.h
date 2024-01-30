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
	void SetMoveR(bool R) { MoveR = R; }
	// getter
	bool Getter() { return MoveR; }

private:
	
	bool MoveR = false;
};