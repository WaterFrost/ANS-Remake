#pragma once

class TextureRect
{
public:
    TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
    TextureRect(Vector3 position, Vector3 size, float rotation);
    ~TextureRect();

    void Update();
    void Render();

    void GUI();
    
    void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
    void SetShader(wstring shaderPath);

    Vector3 GetPosition() { return this->position; }
    void SetPosition(Vector3 newPos) { this->position = newPos; }


protected:
    vector<VertexTexture> vertices;
    VertexBuffer* vb = nullptr;

    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    InputLayout* il = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    D3DXMATRIX world;
    D3DXMATRIX S, R, T;

    WorldBuffer* wb = nullptr;

    Vector3 position;
    Vector3 size;
    float rotation;

    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11RasterizerState* rs = nullptr;

    D3D11_MAPPED_SUBRESOURCE subResource;
};