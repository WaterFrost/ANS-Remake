#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "ANS/Player.h"
class Avoid_N_Survive : public IObject
{
	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

	// ANS �����Լ�
	void IsGround(); // ground �� player Ȯ��
private:

	// �׸� ����
	Player* player;
	Rect* ground;

	// ���� ����
	
	// �÷��� �ð�
	float deltatime = 0.0f;
	int playtime_s = 0;
	int playtime_m = 0;
};