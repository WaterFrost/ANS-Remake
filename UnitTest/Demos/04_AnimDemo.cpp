#include "stdafx.h"
#include "04_AnimDemo.h"

void AnimDemo::Init()
{
	ar = new AnimationRect(Vector3(WinMaxWidth * 0.5, WinMaxHeight * 0.5, 0), Vector3(500, 500, 1));
}

void AnimDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void AnimDemo::Update()
{
	ar->Update();
}

void AnimDemo::Render()
{
	ar->Render();
}

void AnimDemo::PostRender()
{
}

void AnimDemo::GUI()
{
}
