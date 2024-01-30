#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size, float rotation)
	:Rect(position, size, rotation)
{
}

Enemy::~Enemy()
{
}

void Enemy::GetRandomPosition(int minX, int maxX, int minY, int maxY)
{
	SetPosition(Vector3(Random::GetRandomInt(minX, maxX), Random::GetRandomInt(minY, maxY), 0));
}

void Enemy::Move()
{
	if (MoveR)
	{
		SetPositionX(GetPositionX() + 1);
	}
	else if (!MoveR)
	{
		SetPositionX(GetPositionX() - 1);
	}
}
