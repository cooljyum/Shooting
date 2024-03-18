#pragma once

class Item : public Quad
{
public:
	Item(ItemData data);
	~Item();

	void Update();
	void Render() override;

	void Spawn(const Vector2& pos);
	void Spawn(const Vector2& pos, ItemData data);

	void Collision();

	void SetTarget(Transform* transform) { target = transform; }

	ItemData GetData() { return data; }

protected:
	ItemData data;

	Transform* target;

	Collider* collider;
};