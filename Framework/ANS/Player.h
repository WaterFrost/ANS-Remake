#pragma once
class Player : public Rect
{
public:
	Player(Vector3 position, Vector3 size, float rotation);
	~Player();

	void Control();
	
	// Setter
	void Sethp(int point) { hp = point; }
	// Getter
	int GetHp() { return hp; }
private:
	int hp = 5;

	float immudelay = 0;

	bool immu = false;
	bool moveR = false;
	bool jump = false;
};