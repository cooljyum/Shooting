#include "Framework.h"

ItemManager::ItemManager()
{
	CreateObjects("HealthItem", POOL_SIZE);
}

ItemManager::~ItemManager()
{
}

void ItemManager::SetTarget(Transform* transform)
{

}

bool ItemManager::Collision(string key, Collider* collider)
{
	for (GameObject* bullet : totalObject[key])
	{
		if (((Item*)bullet)->GetCollider()->IsCollision(collider))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

void ItemManager::Spawn(const Vector2& pos, const Vector2& direction)
{
	Pop("HealthItem")->Spawn(pos, direction);
}
