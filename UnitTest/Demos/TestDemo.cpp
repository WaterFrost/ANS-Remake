#include "stdafx.h"
#include "TestDemo.h"

void TestDemo::Init()
{
	ar = new AnimationRect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(500, 500, 1));
	ar->Setalpha(0.5f);
	
	rect = new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(30, 30, 1), 0.0f);
}

void TestDemo::Destroy()
{
	SAFE_DELETE(ar);
	SAFE_DELETE(rect);
}

void TestDemo::Update()
{
	ar->Update();
	rect->Update();
	if(Mouse::Get()->Down())
}

void TestDemo::Render()
{
	ar->Render();
	rect->Render();
}

void TestDemo::PostRender()
{
}

void TestDemo::GUI()
{
}
