#include "Framework.h"

Bullet::Bullet() : Quad(L"Resources/Textures/Shooting/playerBullet2.png")
{
	collider = new CircleCollider(SIZE);
	collider->SetParent(this);

	SetActive(false);
}

Bullet::~Bullet()
{
	delete collider;
}

void Bullet::Update()
{
	if (!IsActive()) return;
	
	Translate(GetRight() * speed * DELTA);

	if (localPosition.x < -SIZE || localPosition.x > SCREEN_WIDTH + SIZE)
		SetActive(false);

	if (localPosition.y < -SIZE || localPosition.y > SCREEN_HEIGHT + SIZE)
		SetActive(false);

	UpdateWorld();
	collider->UpdateWorld();
}

void Bullet::Render()
{
	Quad::Render();
	collider->Render();
}

void Bullet::Fire(const Vector2& pos, const Vector2& direction)
{
	SetActive(true);

	SetLocalPosition(pos);
	localRotation.z = direction.Angle();
	UpdateWorld();
}
