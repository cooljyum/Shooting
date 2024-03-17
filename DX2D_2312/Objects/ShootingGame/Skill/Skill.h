#pragma once

class Skill : public GameObject
{
public:
	Skill(int key, Transform* owner);
	virtual ~Skill();

	virtual void LevelUp();

protected:
	SkillData data;

	Transform* owner;
};