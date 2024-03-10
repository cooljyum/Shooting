#include "Framework.h"

BulletManager::BulletManager()
{
	CreateObjects("PlayerBullet", POOL_SIZE);
}

BulletManager::~BulletManager()
{
}

bool BulletManager::Collision(string key, Collider* collider)
{
	for (GameObject* bullet : totalObject[key])
	{
		if (((Bullet*)bullet)->GetCollider()->IsCollision(collider))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

void BulletManager::Fire(const Vector2& pos, const Vector2& direction)
{
	Pop("PlayerBullet")->Fire(pos, direction);
}
