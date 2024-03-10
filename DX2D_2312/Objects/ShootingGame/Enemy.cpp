#include "Framework.h"

Enemy::Enemy() : Quad(L"Resources/Textures/Shooting2/enemy_.png")
{
	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);

	SetActive(false);
	
}

Enemy::Enemy(wstring textureFile) : Quad(textureFile)
{
	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);

	SetActive(false);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::Update()
{
	if (!IsActive()) return;

	if(!type)
		Rotate(rotSpeed * DELTA);
	Vector2 direction = target->GetGlobalPosition() - localPosition;
	Translate(direction.Normalized() * moveSpeed * DELTA);

	Quad::Update();
	collider->UpdateWorld();


	Plane* plane = (Plane*)target;
	if (collider->IsCollision(plane->GetCollider()))
	{
		SetActive(false);
		
		//ItemManager::Get()->Spawn(GetGlobalPosition(), GetRight());
		Plane::health--;
	}

	if (BulletManager::Get()->Collision("PlayerBullet", collider))
	{
		SetActive(false);
		ItemManager::Get()->Spawn(GetGlobalPosition(), GetRight());
	}
}

void Enemy::Render()
{
	Quad::Render();
	collider->Render();
}
