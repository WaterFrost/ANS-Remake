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

		// View 행렬 생성
		{
			D3DXMatrixLookAtLH
			(
				&view,
				&Vector3(0, 0, 0), // 카메라 위치(원점)
				&Vector3(0, 0, 1), // 카메라가 바라보는 방향
				&Vector3(0, 1, 0)  // 카메라의 위쪽 방향
			);
		}

		// Projection 행렬 생성
		{
			// 직교 투영 행렬
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,				// 왼쪽 면의 위치
				(float)WinMaxWidth, // 오른쪽 면의 위치
				0.0f,				// 아래쪽 면의 위치
				(float)WinMaxHeight,// 위쪽 면의 위치
				0,					// 니어 (깊이 시작)
				1					// 파	(깊이 끝)
			);
		}

		// 버퍼 세팅
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
	// 타겟이 있을때
	if (target != nullptr)
	{
		position.x = target->GetPosition().x - WinMaxWidth * 0.5f;
		position.y = target->GetPosition().y - WinMaxHeight * 0.5f;
	}
	// 타겟이 없을때
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
		&position, // 카메라 위치(원점)
		&(position + Vector3(0, 0, 1)), // 카메라가 바라보는 방향
		&Vector3(0, 1, 0)  // 카메라의 위쪽 방향
	);

	cout << position.x << ' ' << position.y << endl;
	cout << endl;
	
	globalMPos = Mouse::Get()->GetPosition();
	cout << globalMPos.x << ' ' << globalMPos.y << endl;
	vpb->SetView(view);
}