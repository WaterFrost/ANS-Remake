#include "Framework.h"
#include "Camera.h"


const Vector3 Camera::GetMPosition()
{
	Vector3 MPos = Mouse::Get()->GetPosition();

	MPos += position;

	return MPos;
}

Camera::Camera()
{
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
}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}

void Camera::Update()
{
	Move();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	// Ÿ���� ������
	if (target != nullptr)
	{
		position.x = target->GetPosition().x - WinMaxWidth * 0.5f;
		position.y = target->GetPosition().y - WinMaxHeight * 0.5f;
	}
	// Ÿ���� ������
	else
	{
		if (Keyboard::Get()->Press(VK_SHIFT))
		{
			if (Keyboard::Get()->Press(VK_UP))
			{
				position.y += cameraSpd * Time::Delta();
			}
			else if (Keyboard::Get()->Press(VK_DOWN))
			{
				position.y -= cameraSpd * Time::Delta();
			}
			if (Keyboard::Get()->Press(VK_RIGHT))
			{
				position.x += cameraSpd * Time::Delta();
			}
			else if (Keyboard::Get()->Press(VK_LEFT))
			{
				position.x -= cameraSpd * Time::Delta();
			}
		}
	}
	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH
	(
		&view,
		&position, // ī�޶� ��ġ(����)
		&(position + Vector3(0, 0, 1)), // ī�޶� �ٶ󺸴� ����
		&Vector3(0, 1, 0)  // ī�޶��� ���� ����
	);

	cout << position.x << ' ' << position.y << endl;
	cout << endl;
	
	globalMPos = Mouse::Get()->GetPosition();
	cout << globalMPos.x << ' ' << globalMPos.y << endl;
	vpb->SetView(view);
}