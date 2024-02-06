#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/Avoid_N_Survive.h"

void Program::Init()
{
	States::Create();
	// Create Buffer
	{
		vpb = new VPBuffer();

		// View ��� ����
		{
			D3DXMatrixLookAtLH
			(
				&view,
				&Vector3(0, 0, 0), // ī�޶� ��ġ(����)
				&Vector3(0, 0, 1), // ī�޶� �ٶ󺸴� ����
				&Vector3(0, 1, 0)  // ī�޶��� ���� ����
			);
		}

		// Projection ��� ����
		{
			// ���� ���� ���
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,				// ���� ���� ��ġ
				(float)WinMaxWidth, // ������ ���� ��ġ
				0.0f,				// �Ʒ��� ���� ��ġ
				(float)WinMaxHeight,// ���� ���� ��ġ
				0,					// �Ͼ� (���� ����)
				1					// ��	(���� ��)
			);
		}

		// ���� ����
		vpb->SetView(view);
		vpb->SetProj(proj);
	}

//	Push(new RectDemo);
//	Push(new TextureDemo);
//	Push(new CollisionDemo);
//	Push(new ShadedDemo);
//	Push(new AnimDemo);
	Push(new Avoid_N_Survive);
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
