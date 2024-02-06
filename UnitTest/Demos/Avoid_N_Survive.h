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
	void SetHPposition(); // �÷��̾� ü�¿� ���� �̹��� ���
	void GameOver(); // ���� ���� ���
	void Reset(); // ���ӿ����� RŰ�� ���� �����
	void Rank(); // �÷��� �ð��� ���� ��ũ���
	void Hit(); // �ǰ�����
	
	// ���� ���� �Լ�
	void AddSounds(); // ���� �߰�
	void AddImages(); // �̹��� �߰�
	void CreateHP(); // ü�� ����
	void CreateEnemy(); // �� ��ü ����
	

	// ���� ���� �Լ�
	void RandomPattern(); // ���� ���� �ο� �Լ�
	void Firstpattern(); // ù��° ����
	void Secondpattern(); // �ι�° ����
private:

	// �׸� ����
	Player* player;
	Rect* ground;

	// �̹���
	TextureRect* scoreimg;
	TextureRect* img_GameOver;

	vector<TextureRect*> hp;
	vector<TextureRect*> rank;
	vector<Enemy*> enemy;

	// ���� �÷��� ����
	bool death = false;
	// ���� ����
	int pscore = 0;

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