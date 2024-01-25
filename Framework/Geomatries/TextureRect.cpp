#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
    : position(position), size(size), rotation(rotation)
{
    // verteices
    {
        vertices.assign(4, VertexTexture());

        // 좌하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // 우상단
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // 우하단
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // 좌상단
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }

    // VertexShader
    {
        vs = new VertexShader();
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
    }

    // Wolrd
    {
        wb = new WorldBuffer();
    }

    // Rasterizer State
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

        // CullMode : 보이지 않는 면을 어떻게 그릴 것이냐 처리
        // Cull_Back = 뒷면을 그리지 않겠다
        desc.CullMode = D3D11_CULL_BACK;
        
        // FillMode : 정점과 정점을 연결후 내부를 어떻게 채울꺼냐
        // Fill_Solid = 가득 체워라
        desc.FillMode = D3D11_FILL_SOLID;

        // 그리는 방향 설정 / false = 시계 방향
        desc.FrontCounterClockwise = false;

        HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
        CHECK(hr);
    }

    // ShaderResourceView
    {
        HRESULT hr = D3DX11CreateShaderResourceViewFromFile
        (
            DEVICE,
            path.c_str(),
            nullptr,
            nullptr,
            &srv,
            nullptr
        );
        CHECK(hr);
    }
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // verteices
    {
        vertices.assign(4, VertexTexture());

        // 좌하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // 우상단
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // 우하단
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // 좌상단
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }

    // VertexShader
    {
        vs = new VertexShader();
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
    }

    // Wolrd
    {
        wb = new WorldBuffer();
    }
}

TextureRect::~TextureRect()
{
    SAFE_RELEASE(srv);
    SAFE_RELEASE(rs);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void TextureRect::Update()
{
    // Scale
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // Rotation
    D3DXMatrixRotationZ(&R, rotation);
    // Translation
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT순으로 곱하지 않으면 터짐
    world = S * R * T;
    wb->SetWorld(world);
}

void TextureRect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    DC->PSSetShaderResources(0, 1, &srv);
    DC->RSSetState(rs);

    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
}

void TextureRect::SetShader(wstring shaderPath)
{
    vs->Clear();
    ps->Clear();

    vs->Create(shaderPath, "VS");
    ps->Create(shaderPath, "PS");
}
