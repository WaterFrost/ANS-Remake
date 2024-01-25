#include "stdafx.h"
#include "Avoid_N_Survive.h"


void Avoid_N_Survive::Init()
{
	player = new Player(Vector3(WinMaxWidth * 0.5f, WinMaxHeight*0.5f, 0), Vector3(30, 30, 1), 0.0f);
	player->SetColor(Values::Green);
	player->Update();
}

void Avoid_N_Survive::Destroy()
{
	SAFE_DELETE(player);
}

void Avoid_N_Survive::Update()
{ 
	player->Control();

	player->Update();  
}

void Avoid_N_Survive::Render()
{
	player->Render();
}

void Avoid_N_Survive::PostRender()
{
}

void Avoid_N_Survive::GUI()
{
}
