#pragma once

class BulletManager : public Singleton<BulletManager>, public PoolingManager<Bullet>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 100;	

	BulletManager();
	~BulletManager();

public:
	bool Collision(string key, Collider* collider);

public:
	void Fire(const Vector2& pos, const Vector2& direction, bool isEnemy = false);
};