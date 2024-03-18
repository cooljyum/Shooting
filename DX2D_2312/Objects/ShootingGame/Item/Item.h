#pragma once

class Item : public Quad
{
public:
	Item(ItemData data);
	~Item();

	void Update();
	void Render() override;

	void Spawn(Vector2 pos);

	void Collision();

	void SetTarget(Transform* transform) { target = transform; }

	ItemData GetData() { return data; }

protected:
	ItemData data;

	Transform* target;

	Collider* collider;
};