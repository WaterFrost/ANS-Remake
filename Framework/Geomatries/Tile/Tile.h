#pragma once

class Tile
{
public:

	// Setter
	void Setposition(Vector3 position) { this->position = position; }
	void SetStartUV(Vector2 startUV) { this->startUV = startUV; }
	void SetEndUV(Vector2 endUV) { this->endUV = endUV; }
	void SetColor(Color color) { this->color = color; }
	void SetIndex(uint index) { this->index = index; }
	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }

	// Getter
	Vector3 Getposition() { return position; }
	Vector2 GetStartUV() { return startUV; }
	Vector2 GetEndUV() { return endUV; }
	Color GetColor() { return color; }
	uint GetIndex() { return index; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	Vector3 position = Values::ZeroVec3;
	// 그림이 그려지지 않은 공간의 색
	Color color = Values::Black;

	Vector2 startUV = Values::ZeroVec2;
	Vector2 endUV = Values::ZeroVec2;

	ID3D11ShaderResourceView* srv = nullptr;

	// 정상적이지 않은 값을 넣어줌
	// 이상한 그림이 그려지지 않게 하기위해 존재하지 않는 값을 삽입
	uint index = -1;
};