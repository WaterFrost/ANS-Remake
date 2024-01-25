#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // verteices
    {
        vertices.assign(4, VertexColor());

        // 좌하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].color = color;

        // 우상단
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].color = color;

        // 우하단
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].color = color;

        // 좌상단
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].color = color;
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
        vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());
    }

    // Wolrd
    {
        wb = new WorldBuffer();
    }
    for (int i = 0; i < 4; i++)
        verticesPosition[i] = vertices[i].position;

    edge = new RectEdge();
    collision = new BoundingBox();

    ab = new AlphaBuffer();
}

Rect::~Rect()
{
    SAFE_DELETE(ab);

    SAFE_DELETE(collision);
    SAFE_DELETE(edge);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);

}

void Rect::Update()
{
    if (Keyboard::Get()->Press(VK_F5))
    {
        if(ab->GetAlpha()<1.0f)
        {
            ab->SetAlpha(ab->GetAlpha() + 0.01f);
        }
    }
    if (Keyboard::Get()->Press(VK_F6))
    {
        if (ab->GetAlpha() > 0.0f)
        {
            ab->SetAlpha(ab->GetAlpha() - 0.01f);
        }
    }
    UpdateWorld();
    collision->UpdataCollisionData(world, verticesPosition);
   
}

void Rect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();
    ab->SetPSBuffer(0);

    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI()
{
}
//void Rect::Move()
//{
//
//    if (Keyboard::Get()->Press(VK_UP))
//        position.y += 200 * Time::Delta();
//    else if (Keyboard::Get()->Press(VK_DOWN))
//        position.y -= 200 * Time::Delta();
//
//    if (Keyboard::Get()->Press(VK_LEFT))
//    {
//        position.x -= 200 * Time::Delta();
//        if (Keyboard::Get()->Press(VK_RIGHT)&& !moveR)
//            position.x += 400 * Time::Delta();
//    }
//       
//    else if (Keyboard::Get()->Press(VK_RIGHT))
//    {
//        moveR = true;
//        position.x += 200 * Time::Delta();
//    }
//    if (Keyboard::Get()->Up(VK_RIGHT))
//    {
//        moveR = false;
//    }
//       
//}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subResource;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
    {
        for (VertexColor& v : vertices)
        {
            v.color = color;
        }
        memcpy(subResource.pData, vertices.data(),
            vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLabel(string preFix)
{
    return string();
}

void Rect::UpdateWorld()
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

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}
