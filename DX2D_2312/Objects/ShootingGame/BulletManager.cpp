#include "Framework.h"

BulletManager::BulletManager()
{
	CreateObjects("PlayerBullet", POOL_SIZE);
	CreateObjects("EnemyBullet", POOL_SIZE);
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

void BulletManager::Fire(const Vector2& pos, const Vector2& direction, bool isEnemy)
{
	if(isEnemy)
		Pop("EnemyBullet")->Fire(pos, direction);
	else
		Pop("PlayerBullet")->Fire(pos, direction);
}
