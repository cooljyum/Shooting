#include "Framework.h"

int Plane::health = 100;

Plane::Plane() : Quad(L"Resources/Textures/Shooting2/playerFace.png")
{
	//colorBuffer->SetColor(Random(0.0f, 1.0f), Random(0.0f, 1.0f), Random(0.0f, 1.0f));

	//pivot = { -100, -100 };

	collider = new CircleCollider(70);
	collider->SetParent(this);

	cursor = new Quad(L"Resources/Textures/Shooting/cursor.png");
	cursor->SetParent(this);
	cursor->Translate(Vector2::Right() * 50.0f);
}

Plane::~Plane()
{
	delete collider;
	delete cursor;
}

void Plane::Update()
{
	//if (KEY->Press('W'))
	//	Translate(Vector2::Up() * speed * DELTA);
	//if (KEY->Press('S'))
	//	Translate(Vector2::Down() * speed * DELTA);
	//if (KEY->Press('A'))
	//	Translate(Vector2::Left() * speed * DELTA);
	//if (KEY->Press('D'))
	//	Translate(Vector2::Right() * speed * DELTA);
	//
	//Vector2 direction = mousePos - localPosition;
	//localRotation.z = direction.Angle();

	//localPosition = mousePos;

	if (KEY->Press('A'))
		localRotation.z += DELTA;

	if (KEY->Press('D'))
		localRotation.z -= DELTA;

	if (KEY->Press('W'))
		Translate(GetRight() * speed * DELTA);

	Fire();
	Collision();

	UpdateWorld();
	collider->UpdateWorld();

	cursor->UpdateWorld();
}

void Plane::Render()
{
	Quad::Render();
	collider->Render();
	cursor->Render();

	collider->RenderUI();
}

void Plane::Collision()
{
	if (ItemManager::Get()->Collision("HealthItem", collider))
	{
		//SetActive(false);
	}
}

void Plane::Fire()
{
	if (KEY->Down(VK_LBUTTON))
	{
		BulletManager::Get()->Fire(cursor->GetGlobalPosition(), GetRight());
	}
}
