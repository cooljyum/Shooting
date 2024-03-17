#pragma once

struct SkillData
{
	int key;
	string name;
	int level;
	int power;
	float range;
	int amount;
	float duration;
	float speed;
	float knockback;
};

struct EnemyData
{
	int key;
	string name;
	int level;
	int maxHp;
	float power;
	float range;
	float speed;
	int type;
	wstring textureFile;
};

class ShootingDataManager : public Singleton<ShootingDataManager>
{
private:
	friend class Singleton;

	ShootingDataManager();
	~ShootingDataManager() = default;

public:
	SkillData GetSkillData(int key) { return skillDatas[key]; }
	EnemyData GetEnemyData(int key) { return enemyDatas[key]; }

private:
	void LoadSkillData();
	void LoadEnemyDdata();

public:
	map<int, SkillData> skillDatas;
	map<int, EnemyData> enemyDatas;
};