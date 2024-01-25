#include "Framework.h"
#include "BoundingBox.h"


BoundingBox::BoundingBox()
{
	edge = new RectEdge();
	data = new AxisData();
}

BoundingBox::~BoundingBox()
{
	SAFE_DELETE(data);
	SAFE_DELETE(edge);
}

void BoundingBox::UpdataCollisionData(const Matrix world, const Vector3 verticesLocalPosition[])
{
	// AABB
	{
		// World Position Update
		{
			D3DXVec3TransformCoord(&edge->LT, &verticesLocalPosition[3], &world);
			D3DXVec3TransformCoord(&edge->LB, &verticesLocalPosition[0], &world);
			D3DXVec3TransformCoord(&edge->RT, &verticesLocalPosition[1], &world);
			D3DXVec3TransformCoord(&edge->RB, &verticesLocalPosition[2], &world);
		}
	}
	// OBB
	{
		// Center Position Vector (중심점)
		{
			data->centerPos = Vector3
			(
				(edge->LT.x + edge->LB.x + edge->RT.x + edge->RB.x) * 0.25f,
				(edge->LT.y + edge->LB.y + edge->RT.y + edge->RB.y) * 0.25f,
				0
			);
			
		}

		// Axis Vector (축 좌표)
		{
			D3DXVec3TransformNormal(&data->axisDir[x], &Values::RightVec, &world);
			D3DXVec3TransformNormal(&data->axisDir[y], &Values::UpVec, &world);
			
			D3DXVec3Normalize(&data->axisDir[x], &data->axisDir[x]);
			D3DXVec3Normalize(&data->axisDir[y], &data->axisDir[y]);
		}
		// Axis Length (축 길이 : 판정 범위)
		{
			Vector3 unitAxis[2] = { data->axisDir[x],data->axisDir[y] };

			Vector3 verticesPos[4] = { edge->LT , edge->LB , edge->RT , edge->RB };

			float minValues[2] = { INT_MAX,INT_MAX };
			float maxValues[2] = { INT_MIN,INT_MIN };

			for (int i = 0; i < 4; i++)
			{
				Vector3 point = verticesPos[i];
				for (int j = 0; j < 2; j++)
				{
					float projection = D3DXVec3Dot(&point, &unitAxis[j]);

					if (projection < minValues[j])
					{
						minValues[j] = projection;
					}
					if (projection > maxValues[j])
					{
						maxValues[j] = projection;
					}
				}
			}
			data->axisLen[x] = (maxValues[x] - minValues[x]) * 0.5f;
			data->axisLen[y] = (maxValues[y] - minValues[y]) * 0.5f;
		}
	}
}

bool BoundingBox::AABB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr) 
		return false;
	RectEdge aEdge = *a->edge;
	RectEdge bEdge = *b->edge;

	if (
		aEdge.RB.x >= bEdge.LT.x && aEdge.LT.x <= bEdge.RB.x &&
		aEdge.LT.y >= bEdge.RB.y && aEdge.RB.y <= bEdge.LT.y
		)
		return true;
	else 
		return false;
}

bool BoundingBox::OBB(BoundingBox* a, BoundingBox* b)
{
	if (a == nullptr || b == nullptr)
		return false;

	AxisData ad = *a->data;
	AxisData bd = *b->data;

	Vector3 centerDir, axis;
	float centerProjDist, r1, r2;
	centerDir = ad.centerPos - bd.centerPos;

	// a Rect : X axis
	{
		axis = ad.axisDir[x];
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[x];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			 abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);
		
		if (centerProjDist > r1 + r2)
			return false;
	}
	// a Rect : Y axis
	{
		axis = ad.axisDir[y];
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = ad.axisLen[y];
		r2 = abs(D3DXVec3Dot(&bd.axisDir[x], &axis) * bd.axisLen[x]) +
			abs(D3DXVec3Dot(&bd.axisDir[y], &axis) * bd.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}
	// b Rect : X axis
	{
		axis = bd.axisDir[x];
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[x];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}
	// b Rect : Y axis
	{
		axis = bd.axisDir[y];
		centerProjDist = abs(D3DXVec3Dot(&centerDir, &axis));

		r1 = bd.axisLen[y];
		r2 = abs(D3DXVec3Dot(&ad.axisDir[x], &axis) * ad.axisLen[x]) +
			abs(D3DXVec3Dot(&ad.axisDir[y], &axis) * ad.axisLen[y]);

		if (centerProjDist > r1 + r2)
			return false;
	}
	return true;
}
