#include "Framework.h"

ItemManager::ItemManager()
{
	CreateObjects("HealthItem", POOL_SIZE, L"Resources/Textures/Shooting2/itemHealth.png");
	CreateObjects("MagnetItem", POOL_SIZE, L"Resources/Textures/Shooting2/itemMagnet.png");
	CreateObjects("BombItem", POOL_SIZE, L"Resources/Textures/Shooting2/itemBomb.png");
}

ItemManager::~ItemManager()
{
}

bool ItemManager::Collision(string key, Collider* collider)
{
	for (GameObject* item : totalObject[key])
	{
		if (((Item*)item)->GetCollider()->IsCollision(collider))
		{
			item->SetActive(false);
			return true;
		}
	}

	return false;
}

Item* ItemManager::CollisionTarget(string key, Collider* collider)
{
	for (GameObject* item : totalObject[key])
	{
		if (((Item*)item)->GetCollider()->IsCollision(collider))
		{
			return (Item*)item;
		}
	}

	return nullptr;
}

void ItemManager::Spawn(const Vector2& pos, const Vector2& direction)
{
	int rand = Random(0, 10);

	if (rand < 5)
		Pop("HealthItem")->Spawn(pos, direction);
	else if(rand < 7)
		Pop("MagnetItem")->Spawn(pos, direction);
	else
		Pop("BombItem")->Spawn(pos, direction);
}
