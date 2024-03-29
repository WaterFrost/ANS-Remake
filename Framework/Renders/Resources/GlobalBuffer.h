#pragma once
#include "Framework.h"

// WVP 행렬 정의

class WorldBuffer : public ShaderBuffer
{
public:
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		// 행렬 초기화
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(Matrix world)
	{
		// 핼렬 전치(열과 행을 바꿈)
		D3DXMatrixTranspose(&data.world, &world);
	}

	struct Data
	{
		Matrix world;
	};
private:
	Data data;
};

class VPBuffer : public ShaderBuffer
{
public:
	VPBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}

	void SetView(Matrix view)
	{
		// 핼렬 전치(열과 행을 바꿈)
		D3DXMatrixTranspose(&data.view, &view);
	}

	void SetProj(Matrix projection)
	{
		// 핼렬 전치(열과 행을 바꿈)
		D3DXMatrixTranspose(&data.projection, &projection);
	}

	struct Data
	{
		Matrix view;
		Matrix projection;
	};

private:
	Data data;
};

/*
WVP : World, View , Projection
- 3D 모델을 2D 스크린 좌표로 변환하는 과정중 하나

1. World
- 모델의 정점을 세계 좌표계에서 지역 좌표계로 변환하는 것을 의미
- 모델의 위치, 회전 및 크기를 조정

2. View
- 카메라의 위치, 방향 및 시야를 나타내는 행렬
- 세계 좌표계에서 카마라가 바라보는 방향을 나타냄
- 카메라의 위치와 방향을 변경

3. Projection
- 3D 공간을 2D 스크린 좌표로 변환하는 것을 의미
- 시야각, 종횡비, 크리핑 평면 등을 고려하여 수행
*/