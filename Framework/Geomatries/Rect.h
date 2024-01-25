#pragma once

class AlphaBuffer : public ShaderBuffer
{
public:
	AlphaBuffer()
		:ShaderBuffer(&data, sizeof(Data))
	{
		data.alpha = 1;
	}

	float GetAlpha() { return data.alpha; }
	
	void SetAlpha(float alpha) { data.alpha = alpha; }

	struct Data
	{
		float alpha;
		Vector3 temp;
	};

private:
	Data data;
};

class Rect
{

public:
	Rect(Vector3 position, Vector3 size, float rotation);
	~Rect();

	void Update();
	void Render();
	void GUI();

	void UpdateColor();
	void UpdateWorld();
	void SetColor(Color color);
	
	// Setter
	void SetPosition(Vector3 position) { this->position = position; }
	void SetPositionX(float X) { position.x = X; }
	void SetPositionY(float Y) { position.y = Y; }
	void Setsize(Vector3 size) { this->size = size; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void Setalpha(float alpha) { ab->SetAlpha(alpha); }
	//Getter
	Vector3 GetPosition() { return position; }
	float GetPositionX() { return position.x; }
	float GetPositionY() { return position.y; }
	Vector3 Getsize() { return size; }
	float GetRotation() { return rotation; }
	float GetAlpha() { return ab->GetAlpha(); }

	string MakeLabel(string preFix);
	BoundingBox* GetCollision() { return collision; }

protected:

	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer* ib = nullptr;

	InputLayout* il = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	Vector3 position;
	Vector3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer* wb = nullptr;

	RectEdge* edge = nullptr;
	BoundingBox* collision = nullptr;

	Vector3 verticesPosition[4];
	

	AlphaBuffer* ab = nullptr;
};