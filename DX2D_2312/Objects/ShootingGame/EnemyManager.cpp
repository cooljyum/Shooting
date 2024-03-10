#include "Framework.h"

EnemyManager::EnemyManager()
{
	CreateObjects("CloseRangeEnemy", 50,  L"Resources/Textures/Shooting2/enemy_.png");
	CreateObjects("DistantRangeEnemy", 50, L"Resources/Textures/Shooting2/enemy.png");
	
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
