#include "Framework.h"
#include "ShootingGameScene.h"

ShootingGameScene::ShootingGameScene()
{
	plane = new Plane();
	plane->SetLocalPosition(CENTER);	

	BulletManager::Get();
	EnemyManager::Get()->SetTarget(plane);
}

ShootingGameScene::~ShootingGameScene()
{
	BulletManager::Delete();
	EnemyManager::Delete();
}

void ShootingGameScene::Update()
{	
	EnemyManager::Get()->Update();
}

void ShootingGameScene::Render()
{
}

void ShootingGameScene::PostRender()
{
}
