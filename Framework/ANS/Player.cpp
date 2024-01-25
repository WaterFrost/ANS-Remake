#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotation)
	: Rect(position,size, rotation)
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
	if (Keyboard::Get()->Press(VK_SPACE) || !jump)
	{
		float jumptime = 0.0f;
		jumptime += Time::Delta();
		float oldpy = GetPositionY();
		if (jumptime < 3.0f)
		{
			position.y = 100 * Time::Delta();
		}
	}

}