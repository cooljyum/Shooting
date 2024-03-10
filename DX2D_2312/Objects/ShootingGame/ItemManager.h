#pragma once

class ItemManager : public Singleton<ItemManager>, public PoolingManager<Item>
{
private:
	friend class Singleton;

	const UINT POOL_SIZE = 50;

	ItemManager();
	~ItemManager();

public:
	void Update();

	void SetTarget(Transform* transform);

public:
	bool Collision(string key, Collider* collider);

public:
	void Spawn(const Vector2& pos, const Vector2& direction);
};