#pragma once

class Plane : public Quad
{
private:
	struct ItemAbility
	{
		float attack = 0;
		float defense = 0;
		float hp = 0;
		float speed = 0;
	};

public:
	Plane();
	~Plane();

	void Update();
	void Render();
	void PostRender();

	void AddAbility(float attack, float defense, float hp, float speed);

	float GetDefense() { return itemAbility.defense; }
	float GetAttack() { return itemAbility.attack; }
	
	CircleCollider* GetCollider() { return collider; }
	Quad* GetCursor() { return cursor; }

	vector<Item*> GetEuipItems() { return equipItems; };
	void SetEuipItems(int idx, Item* item) { equipItems[idx]=item; };

private:
	void Collision();
	
	void Damage(int damage);

private:
	float speed = 200.0f;

	CircleCollider* collider;
	Quad* cursor;

	vector<Skill*> skills;

	int hp = 100;
	int maxHp = 100;

	ProgressBar* hpBar;
	ItemAbility itemAbility;

	vector<Item*> equipItems;

	Vector2 hpBarOffset;
};