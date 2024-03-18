#pragma once

class ItemManager : public Singleton<ItemManager>, public PoolingManager<Item>
{
private:
	const float SPAWN_INTERVAL = 1.0f;

private:
	friend class Singleton;

	ItemManager();

public:
	void Update();

	void SetTarget(Transform* transform);

	void Spawn(Vector2 pos);

private:
	vector<Item*> items;
};