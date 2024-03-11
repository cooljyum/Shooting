#pragma once

class Bullet : public Quad
{
private:
	const float SIZE = 15.0f;

public:
	Bullet();
	Bullet(wstring textureFile);
	~Bullet();

	void Update();
	void Render();

	void Fire(const Vector2& pos, const Vector2& direction);

	CircleCollider* GetCollider() { return collider; }

private:
	float speed = 300.0f;
	Vector2 velocity;

	CircleCollider* collider;
};