#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	:Rect(position, size, rotation)
{
}

Player::~Player()
{
}

void Player::Control()
{
	// 좌우 이동
	if (Keyboard::Get()->Press(VK_LEFT) || Keyboard::Get()->Press('A'))
	{
		position.x -= 200 * Time::Delta();
		if (Keyboard::Get()->Press(VK_RIGHT) || Keyboard::Get()->Press('D') && !moveR)
			position.x += 400 * Time::Delta();
	}

	else if (Keyboard::Get()->Press(VK_RIGHT) || Keyboard::Get()->Press('D'))
	{
		moveR = true;
		position.x += 200 * Time::Delta();
	}
	if (Keyboard::Get()->Up('D'))
	{
		moveR = false;
	}
	// 점프
	if (Keyboard::Get()->Down(VK_SPACE) && ground && !jump)
	{
		ground = false;
		jump = true;
	}
	if (jump)
	{
		if (jumptime <= 0.25f)
		{
			jumptime = jumptime + Time::Delta();
			SetPositionY(GetPosition().y + (jumpPower - jumpPower * Time::Delta()));
		}
		else if (jumptime > 0.25f)
		{
			jump = false;
			fall = true;
		}
	}
	if (fall)
	{
		SetPositionY(GetPosition().y - jumpPower);
		jumpPower = jumpPower + Time::Delta();
	}
	if (ground)
	{
		fall = false;
		jump = false;
		jumptime = 0.0f;
		jumpPower = 3.0f;
	}
}