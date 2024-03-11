#include "Framework.h"

bool Collider::isDraw = true;

Collider::Collider()
{
    material = new Material();
    material->SetVertexShader(L"Vertex.hlsl");
    material->SetPixelShader(L"Pixel.hlsl");

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
    colorBuffer->SetColor(0, 1, 0);

    mesh = new Mesh<Vertex>();
}

Collider::~Collider()
{
    delete material;
    delete mesh;

    delete worldBuffer;
    delete colorBuffer;
}

void Collider::Render()
{
    if (!IsActive()) return;
    if (!isDraw) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
    colorBuffer->SetPS(0);

    material->Set();
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

bool Collider::IsCollision(Collider* collider, Vector2* overlap)
{
    if (!IsActive()) return false;
    if (!collider->IsActive()) return false;

    switch (collider->type)
    {
    case Collider::Type::RECT:
        return IsRectCollision((RectCollider*)collider, overlap);            
    case Collider::Type::CIRCLE:
        return IsCircleCollision((CircleCollider*)collider);        
    }

    return false;
}