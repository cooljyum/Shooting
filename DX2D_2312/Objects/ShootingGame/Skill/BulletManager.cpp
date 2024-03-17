#include "Framework.h"

BulletManager::BulletManager()
{
	totalObject["EnemyBullet"].resize(POOL_SIZE);

	for (GameObject*& bullet : totalObject["EnemyBullet"])
		bullet = new BaseBullet(L"Resources/Textures/Shooting/enemyBullet.png");

	totalObject["PlayerBullet"].resize(POOL_SIZE);

	for (GameObject*& bullet : totalObject["PlayerBullet"])
		bullet = new BaseBullet(L"Resources/Textures/Shooting/playerBullet2.png");

	totalObject["WheelBullet"].resize(5);

	for (GameObject*& bullet : totalObject["WheelBullet"])
		bullet = new WheelBullet();
}

BulletManager::~BulletManager()
{
}

Bullet* BulletManager::Collision(string key, Collider* collider)
{
	for (GameObject* bullet : totalObject[key])
	{
		if (((Bullet*)bullet)->GetCollider()->IsCollision(collider))
		{
			return (Bullet*)bullet;
		}
	}

	return nullptr;
}

void BulletManager::Fire(const Vector2& pos, const Vector2& direction, float power, float speed)
{
	Pop("EnemyBullet")->Fire(pos, direction, power, speed);
}

void BulletManager::Fire(const Vector2& pos, const Vector2& direction, SkillData data)
{
	Pop("PlayerBullet")->Fire(pos, direction, data);
}
