#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
class Enemy : public Rect
{
public:
	Enemy(Vector3 position,Vector3 size,float rotation);
	~Enemy();

};