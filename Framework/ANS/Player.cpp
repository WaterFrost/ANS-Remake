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
		position.x -= 300 * Time::Delta();
		if (Keyboard::Get()->Press(VK_RIGHT) || Keyboard::Get()->Press('D') && !moveR)
			position.x += 600 * Time::Delta();
	}

	else if (Keyboard::Get()->Press(VK_RIGHT) || Keyboard::Get()->Press('D'))
	{
		moveR = true;
		position.x += 300 * Time::Delta();
	}
	if (Keyboard::Get()->Up('D'))
	{
		moveR = false;
	}

	// 더블 점프 활성 
	if (jump && !doublejump && Keyboard::Get()->Down(VK_SPACE))
	{
		doublejump = true;
		jumptime = 0.0f;
	}
	if (fall && !doublejump && Keyboard::Get()->Down(VK_SPACE))
	{
		fall = false;
		jumptime = 0.0f;
		jump = true;
		doublejump = true;
	}

	// 점프 활성화
	if (Keyboard::Get()->Down(VK_SPACE) && ground)
	{
		ground = false;
		jump = true;
	}
	// 점프 활성시
	if (jump)
	{
		jumptime = jumptime + 3*Time::Delta();
		SetPositionY(GetPosition().y + (jumpPower - jumptime));
		if (jumptime >= jumpPower)
		{
			jumptime = 0.0f;
			jump = false;
			fall = true;
		}
	}
	
	// 낙하 활성시
	if (fall)
	{
		jumptime = jumptime + 10*Time::Delta();
		SetPositionY(GetPosition().y - jumptime);
	}

	// 바닥 활성시
	if (ground)
	{
		fall = false;
		jump = false;
		doublejump = false;
		jumptime = 0.0f;
	}
}