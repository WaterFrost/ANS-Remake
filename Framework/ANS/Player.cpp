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
	if (Keyboard::Get()->Down(VK_SPACE) && !jump)
	{
		Oldpos = GetPosition();
		jump = true;
	}
	if (jump)
	{
		if (jumptime <= 0.25f)
		{
			jumptime = jumptime + Time::Delta();
			SetPositionY(GetPosition().y + 20*jumptime);
		}
		else if (jumptime > 0.25f)
		{
			jump = false;
			fall = true;
		}
	}
	if (fall)
	{
		if (GetPosition().y >= Oldpos.y)
		{
			SetPositionY(GetPosition().y - jumptime*20);
			if (GetPosition().y <= Oldpos.y)
			{
				SetPositionY(Oldpos.y);
				fall = false;
				jump = false;
				jumptime = 0.0f;
			}
		}

	}
}