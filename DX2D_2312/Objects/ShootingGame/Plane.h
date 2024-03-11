#pragma once

class Plane : public Quad
{
private:
	const int SIZE = 50;
	const int SKILL_SIZE = 120;
	const Vector2 REACTION_SIZE = { 500.0f, 500.0f }; 

	const float CURSOR_OFFSET = 50.0f;

	const float MAGNET_SPEED = 20.0f;
	const float MAGNET_INTERVAL = 5.0f;
	const float BOMB_INTERVAL = 0.5f;
private:
	enum ItemSkill 
	{
		Magnet, Bomb
	};
public:
	Plane();
	~Plane();

	void Update();
	void Render();
	
	CircleCollider* GetCollider() { return collider; }
	RectCollider* GetReactionCollider() { return reactionCollider; }

	CircleCollider* GetSkillCollider() { return skillCollider; }

	void Collision();

private:
	void CreateObject();
	void UpdateObject();

	void AddItem(int index) { itemsSlot[index]++; }
	void SubItem(int index) { itemsSlot[index]--; }
	void SetUseItem(int index, bool isTrue) { useItems[index] = isTrue; }

	void Move();
	void Fire();
	void Skill();


private:
	float speed = 100.0f;

	float playMagnetTime = 0.0f;
	float playBombTime = 0.0f;

	bool useItems[2] = { false, false };

	Quad* cursor;

	CircleCollider* collider;
	RectCollider* reactionCollider;

	Quad* skillCursor;
	Quad* skillImg;
	CircleCollider* skillCollider;

public:
	static int health;
	static int score;

	static int itemsSlot[2];
};