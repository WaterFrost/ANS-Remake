#include "stdafx.h"
#include "TestDemo.h"

void TestDemo::Init()
{
	ar = new AnimationRect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(500, 500, 1));
	ar->Setalpha(0.5f);
}

void TestDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void TestDemo::Update()
{
	ar->Update();
}

void TestDemo::Render()
{
	ar->Render();
}

void TestDemo::PostRender()
{
}

void TestDemo::GUI()
{
}
