#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy(Vector3 position, Vector3 size, float rotation)
	:Rect(position,size,rotation)
{
}

Enemy::~Enemy()
{
}
