#include "Framework.h"

int Plane::health = 100;
int Plane::score = 0;

int Plane::itemsSlot[2] = {0, 5};

Plane::Plane() : Quad(L"Resources/Textures/Shooting2/playerFace.png")
{
	CreateObject();
}

Plane::~Plane()
{
	delete cursor;
	delete collider;
	delete reactionCollider;
	delete skillCursor;
	delete skillImg;
	delete skillCollider;
}

void Plane::Update()
{
	Move();
	Fire();
	Collision();
	Skill();

	UpdateWorld();
	UpdateObject();
}

void Plane::Render()
{
	Quad::Render();
	
	cursor->Render();

	collider->Render();
	reactionCollider->Render();
	
	skillCursor->Render();
	skillImg->Render();
	skillCollider->Render();

	collider->RenderUI();
}

void Plane::Collision()
{
	if (ItemManager::Get()->Collision("HealthItem", collider))
		health++;

	if (ItemManager::Get()->Collision("MagnetItem", collider))
		AddItem(ItemSkill::Magnet);

	if (ItemManager::Get()->Collision("BombItem", collider))
		AddItem(ItemSkill::Bomb);

	Item* healthItem = ItemManager::Get()->CollisionTarget("HealthItem", reactionCollider);
	if (useItems[ItemSkill::Magnet] && healthItem != nullptr)
	{
		Vector2 direction = localPosition - healthItem->GetGlobalPosition();
		healthItem->SetLocalPosition(SLerp(healthItem->GetGlobalPosition(), localPosition, MAGNET_SPEED * DELTA));
	}

	Item* bombItem = ItemManager::Get()->CollisionTarget("BombItem", reactionCollider);
	if (useItems[ItemSkill::Magnet] && bombItem != nullptr)
	{
		Vector2 direction = localPosition - bombItem->GetGlobalPosition();
		bombItem->SetLocalPosition(SLerp(bombItem->GetGlobalPosition(), localPosition, MAGNET_SPEED * DELTA));
	}
}

void Plane::CreateObject()
{
	cursor = new Quad(L"Resources/Textures/Shooting/cursor.png");
	cursor->SetParent(this);
	cursor->Translate(Vector2::Up() * 50.0f);

	collider = new CircleCollider(70);
	collider->SetParent(this);
	reactionCollider = new RectCollider({ 500,500 });
	reactionCollider->SetParent(this);

	skillCursor = new Quad(L"Resources/Textures/Shooting/cursor.png");
	skillCursor->SetActive(false);
	skillCollider = new CircleCollider(120);
	skillCollider->SetActive(false);
	skillImg = new Quad(L"Resources/Textures/Shooting2/BombSkill.png");
	skillImg->SetActive(true);
	skillImg->SetParent(skillCollider);
}

void Plane::UpdateObject()
{
	cursor->UpdateWorld();

	collider->UpdateWorld();
	reactionCollider->UpdateWorld();
	
	skillCursor->UpdateWorld();
	skillImg->UpdateWorld();
	skillCollider->UpdateWorld();
}

void Plane::Move()
{
	if (KEY->Press('A'))
		localRotation.z += DELTA;

	if (KEY->Press('D'))
		localRotation.z -= DELTA;

	if (KEY->Press('W'))
		Translate(GetUp() * speed * DELTA);

	if (KEY->Press('S'))
		Translate(GetDown() * speed * DELTA);
}

void Plane::Fire()
{
	if (KEY->Down(VK_LBUTTON) && !useItems[ItemSkill::Bomb])
	{
		BulletManager::Get()->Fire(cursor->GetGlobalPosition(), GetUp());
	}

	if (itemsSlot[ItemSkill::Magnet] && KEY->Down('M'))
	{
		SetUseItem(ItemSkill::Magnet, true);
		SubItem(ItemSkill::Magnet);
	}

	if (itemsSlot[ItemSkill::Bomb] && KEY->Down('B'))
	{
		SetUseItem(ItemSkill::Bomb, true);
		SubItem(ItemSkill::Bomb);
	}
}

void Plane::Skill()
{
	if (useItems[ItemSkill::Magnet]) 
	{
		playMagnetTime += DELTA;

		if (playMagnetTime >= MAGNET_INTERVAL)
		{
			playMagnetTime -= MAGNET_INTERVAL;
			SetUseItem(ItemSkill::Magnet, false);
		}
	}

	if (useItems[ItemSkill::Bomb])
	{
		if (playBombTime <= 0.0f)
		{
			skillCursor->SetLocalPosition(mousePos);
			skillCursor->SetActive(true);

			if (KEY->Down(VK_LBUTTON))
			{
				skillCursor->SetActive(false);

				skillCollider->SetActive(true);
				skillCollider->SetLocalPosition(mousePos);
				skillCollider->SetLocalRotation(0,0,0);
				
				playBombTime += DELTA;
			}
		}
		else 
		{
			playBombTime += DELTA;
			skillCollider->Rotate(10.0f*DELTA);
			if (playBombTime >= BOMB_INTERVAL)
			{
				playBombTime = 0.0f;
				skillCollider->SetActive(false);

				SetUseItem(ItemSkill::Bomb, false);
			}
		}
	}
}
