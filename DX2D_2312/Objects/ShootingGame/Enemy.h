#pragma once

class Enemy : public Quad
{
public:
	Enemy();
	~Enemy();

	void Update() override;
	void Render() override;

	CircleCollider* GetCollider() { return collider; }

	void SetTarget(Transform* transform) { target = transform; }

private:
	float moveSpeed = 50.0f;
	float rotSpeed = 10.0f;

	CircleCollider* collider;

	Transform* target;
};