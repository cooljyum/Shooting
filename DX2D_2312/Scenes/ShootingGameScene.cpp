#include "Framework.h"
#include "ShootingGameScene.h"

ShootingGameScene::ShootingGameScene()
{
	bg = new BackGround();
	bg->SetLocalPosition(CENTER);

	plane = new Plane();
	plane->SetLocalPosition(CENTER);	
\
	BulletManager::Get();
	EnemyManager::Get()->SetTarget(plane);
	ItemManager::Get();
}

ShootingGameScene::~ShootingGameScene()
{
	BulletManager::Delete();
	EnemyManager::Delete();
	ItemManager::Delete();
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
