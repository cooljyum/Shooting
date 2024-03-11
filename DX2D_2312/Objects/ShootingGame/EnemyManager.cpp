#include "Framework.h"

EnemyManager::EnemyManager()
{
	CreateObjects("CloseRangeEnemy", 50,  L"Resources/Textures/Shooting2/CloseRangeEnemy.png");
	CreateObjects("DistantRangeEnemy", 50, L"Resources/Textures/Shooting2/DistantRangeEnemy.png");
	
}

void EnemyManager::Update()
{
	playTime += DELTA;

	if (playTime >= SPAWN_INTERVAL)
	{
		playTime -= SPAWN_INTERVAL;

		Enemy* enemy;

		if(Random(0, 2))
			enemy = Pop("CloseRangeEnemy");
		else
			enemy = Pop("DistantRangeEnemy");

		enemy->SetActive(true);
		enemy->SetLocalPosition(GetRandomPos());
		enemy->Update();
	}
}

void EnemyManager::SetTarget(Transform* transform)
{
	for (GameObject* enemy : totalObject["CloseRangeEnemy"])
	{
		((Enemy*)enemy)->SetTarget(transform);
		((Enemy*)enemy)->SetType(Enemy::CLOSE);
	}

	for (GameObject* enemy : totalObject["DistantRangeEnemy"])
	{
		((Enemy*)enemy)->SetTarget(transform);
		((Enemy*)enemy)->SetType(Enemy::DISTANT);
	}
}

Quad* EnemyManager::GetClosestEnemy(Vector2 pos)
{
	float minDistance = FLT_MAX;
	Quad* selectEnemy = nullptr;

	for (GameObject* enemy : totalObject["CloseRangeEnemy"])
	{
		if (!((Enemy*)enemy)->IsActive()) continue;

		float distance = (((Enemy*)enemy)->GetGlobalPosition() - pos).SqrMagnitude();
		
		if (minDistance > distance)
		{
			minDistance = distance;
			selectEnemy = ((Enemy*)enemy);
		}
	}

	for (GameObject* enemy : totalObject["DistantRangeEnemy"])
	{
		if (!((Enemy*)enemy)->IsActive()) continue;

		float distance = (((Enemy*)enemy)->GetGlobalPosition() - pos).SqrMagnitude();

		if (minDistance > distance)
		{
			minDistance = distance;
			selectEnemy = ((Enemy*)enemy);
		}
	}

	return selectEnemy;
}
Vector2 EnemyManager::GetRandomPos()
{
	Direction direction = (Direction)Random(0, 4);

	float x = Random(0, SCREEN_WIDTH);
	float y = Random(0, SCREEN_HEIGHT);

	switch (direction)
	{
	case GameMath::Direction::UP:
		return Vector2(x, SCREEN_HEIGHT);
	case GameMath::Direction::DOWN:
		return Vector2(x, 0);
	case GameMath::Direction::LEFT:
		return Vector2(0, y);
	case GameMath::Direction::RIGHT:
		return Vector2(SCREEN_WIDTH, y);	
	}

	return Vector2();
}
