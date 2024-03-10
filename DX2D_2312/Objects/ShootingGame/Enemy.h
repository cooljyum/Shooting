#pragma once

class Enemy : public Quad
{
public: 
	enum Type
	{
		CLOSE, DISTANT
	};

public:
	Enemy();
	Enemy(wstring textureFile);
	~Enemy();

	void Update() override;
	void Render() override;

	CircleCollider* GetCollider() { return collider; }

	void SetTarget(Transform* transform) { target = transform; }
	void SetType(Type type) { this->type = type; }

private:
	float moveSpeed = 50.0f;
	float rotSpeed = 10.0f;

	CircleCollider* collider;

	Transform* target;
	Type type = CLOSE;
};