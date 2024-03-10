#pragma once

class ItemManager : public Singleton<ItemManager>, public PoolingManager<Item>
{
private:
	enum Type
	{
		HEALTTH, MAGNET, BOMB
	};

private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;

	ItemManager();
	~ItemManager();

public:
	bool Collision(string key, Collider* collider);

	Item* CollisionTarget(string key, Collider* collider);

public:
	void Spawn(const Vector2& pos, const Vector2& direction);
};