#include "stdafx.h"
#include "03_ShadedDemo.h"


void ShadedDemo::Init()
{
	st = new ShadedTexture(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
		Vector3(500, 500, 1), 0.0f, TexturePath + L"sample.jpg");
}

void ShadedDemo::Destroy()
{
	SAFE_DELETE(st);
}

void ShadedDemo::Update()
{
	st->Update();
}

void ShadedDemo::Render()
{
	st->Render();
}

void ShadedDemo::PostRender()
{
}

void ShadedDemo::GUI()
{
	st->GUI();
}
