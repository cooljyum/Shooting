#include "Framework.h"

Item::Item(ItemData data): data(data)
{
	wstring path = L"Resources/Textures/Shooting3/Item/";
	SetTexture(path + data.textureFile);

	collider = new CircleCollider(size.x * 0.5f);
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

	Collision();

	UpdateWorld();
	collider->UpdateWorld();
}

void Item::Render()
{
	Quad::Render();
	collider->Render();

	switch (data.level)
	{
	case 1:
		material->SetColor(1, 1, 1);
		break;
	case 2:
		material->SetColor(1, 1, 0);
		break;
	case 3:
		material->SetColor(0, 1, 0);
		break;
	case 4:
		material->SetColor(0, 1, 1);
		break;
	case 5:
		material->SetColor(1, 0, 0);
		break;
	}
}

void Item::Spawn(const Vector2& pos)
{
	SetActive(true);
	this->SetLocalPosition(pos);
}

void Item::Spawn(const Vector2& pos, ItemData data)
{
	//Èì..
}

void Item::Collision()
{
	Plane* plane = (Plane*)target;
	if (collider->IsCollision(plane->GetCollider()))
	{
		if(this->data.type > 0)
			UIManager::Get()->GetInVen()->AddItem(this);
		SetActive(false);
	}
}
