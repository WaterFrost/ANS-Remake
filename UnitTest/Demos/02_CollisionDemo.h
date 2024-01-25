#pragma once
class CollisionDemo : public IObject
{
	// IObject을(를) 통해 상속됨
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

	void MoveEnemys();
	
	
private:
	
	bool Checkwall = false;
	bool CheckHit = false;
	bool Left = true;

	class Rect* player;
	class Rect* goal;
	class Rect* start;
	class Rect* road;
	class Rect* wall;
	class Rect* enemy;
	vector<class Rect*> Players;
	vector<class Rect*> Roads;
	vector<class Rect*> Walls;
	vector<class Rect*> Enemys;
};