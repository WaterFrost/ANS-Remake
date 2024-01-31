#pragma once
#include "Geomatries/Rect.h"
#include "Geomatries/TextureRect.h"
#include "ANS/Player.h"
#include "ANS/Enemy.h"
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
	void GameTime(); // ���ӽð� ������ �ð� ��� �� ���� ��� �뵵
	void IsGround(); // ground �� player Ȯ��
	void SetHPposition();
	
	// ���� ���� �Լ�
	void CreateHP();
	void CreateEnemy();

	// ���� ���� �Լ�
	void RandomPattern(); // ���� ���� �ο� �Լ�
	void Firstpattern(); // ù��° ����
	void Secondpattern(); // �ι�° ����
private:

	// �׸� ����
	Player* player;
	Rect* ground;
	vector<TextureRect*> hp;
	vector<Enemy*> enemy;

	// ���� ����
	
	// �÷��� �ð�
	float deltatime = 0.f;
	int playtime_s = 0;
	int playtime_m = 0;
	// ���� Ȱ��ȭ ����
	bool pattern = false;
	int pTime = 0;
	int pNumber = 0;

	// ���Ѽ� ����
	int fallcount = 0;
	
	bool onsound = false;
	bool Isvisible = true;

};