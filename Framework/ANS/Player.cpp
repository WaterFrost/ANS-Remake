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
	if (Keyboard::Get()->Up(VK_RIGHT) || Keyboard::Get()->Up('D'))
	{
		moveR = false;
	}

	// 더블 점프 기능 구현
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

	// 점프 기능 활성화
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
		jumptime = jumptime + 10 * Time::Delta();
		if (jumptime > 3)
			jumptime = 3;
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
	// 아래에 아무것도 없고 점프 상태가 아닐때
	else if (!ground && !jump)
	{
		fall = true;
	}
}

void Player::Immu()
{
	// 플레이어 무적시간 설정
	if (immu)
	{
		immudelay += Time::Delta();
		SetColor(Values::Blue);
		if (immudelay > 0.5f)
		{
			immu = false;
			immudelay = 0.0f;
			SetColor(Values::Green);
		}
	}
}

void Player::IsWall()
{
	if (GetPositionX() >= WinMaxWidth-15)
		SetPositionX(WinMaxWidth-15);
	else if (GetPositionX() <= 15)
		SetPositionX(15);
}
