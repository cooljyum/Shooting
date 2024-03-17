#include "Framework.h"

WheelBullet::WheelBullet()
    : Bullet(L"Resources/Textures/Shooting/Sword.png")
{
    collider = new RectCollider(size);
    collider->SetParent(this);
}

void WheelBullet::Update()
{
    if (!IsActive()) return;

    Bullet::Update();
}
