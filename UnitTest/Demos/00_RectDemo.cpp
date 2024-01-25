#include "stdafx.h"
#include "00_RectDemo.h"

#include "Geomatries/Rect.h"

void RectDemo::Init()
{
    rect = new Rect(Vector3(500, 200, 0), Vector3(100, 100, 1), 0.0f);
}

void RectDemo::Destroy()
{
    SAFE_DELETE(rect);
}

void RectDemo::Update()
{
    rect->Update();
}

void RectDemo::Render()
{
    rect->Render();
}

void RectDemo::PostRender()
{
}

void RectDemo::GUI()
{
}
