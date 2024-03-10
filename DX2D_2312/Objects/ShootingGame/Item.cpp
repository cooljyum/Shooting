#include "Framework.h"

Item::Item() : Quad(L"Resources/Textures/Shooting2/itemHealth.png")
{
	collider = new CircleCollider(SIZE);
	collider->SetParent(this);

	SetActive(false);
}

Item::Item(wstring textureFile) : Quad(textureFile)
{
	collider = new CircleCollider(SIZE);
	collider->SetParent(this);

	SetActive(false);
}

Item::~Item()
{
	delete collider;
}

void Item::Update()
{
	if (!IsActive()) return;

	//Translate(GetRight() * speed * DELTA);

	if (localPosition.x < -SIZE || localPosition.x > SCREEN_WIDTH + SIZE)
		SetActive(false);

	if (localPosition.y < -SIZE || localPosition.y > SCREEN_HEIGHT + SIZE)
		SetActive(false);

	UpdateWorld();
	collider->UpdateWorld();
}

void Item::Render()
{
	Quad::Render();
	collider->Render();
	
}

void Item::Spawn(const Vector2& pos, const Vector2& direction)
{
	SetActive(true);

	SetLocalPosition(pos);
	//localRotation.z = direction.Angle();
	UpdateWorld();
}
