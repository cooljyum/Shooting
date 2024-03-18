#include "Framework.h"
#include "ShootingGameScene.h"

ShootingGameScene::ShootingGameScene()
{
	ShootingDataManager::Get();

	plane = new Plane();
	plane->SetLocalPosition(CENTER);		

	CAM->SetTarget(plane);

	BulletManager::Get();
	EnemyManager::Get()->SetTarget(plane);
	ItemManager::Get()->SetTarget(plane);
	InvenManager::Get()->SetTarget(plane);

	SetBG();
}

ShootingGameScene::~ShootingGameScene()
{
	BulletManager::Delete();
	EnemyManager::Delete();
	ItemManager::Delete();
	InvenManager::Delete();
}

void ShootingGameScene::Update()
{	
	if (KEY->Down(VK_ESCAPE))
	{
		Timer::Get()->SetScale(0.0f);
	}

	EnemyManager::Get()->Update();

	background->Update();
}

void ShootingGameScene::Render()
{
}

void ShootingGameScene::PostRender()
{
	plane->PostRender();
	InvenManager::Get()->PostRender();
}

void ShootingGameScene::SetBG()
{
	CAM->SetFix(false);

	wstring path = L"Resources/Textures/Shooting3/";
	background = new Background(path + L"BgCity.png");
	background->SetTarget(plane);
	
	//Quad* bg = new Quad(path + L"bg.png");
	//bg->SetDepth(-10);
	//bg = new Quad(path + L"bg2.png");
	//bg->SetDepth(-9);
	//bg = new Quad(path + L"bg3.png");
	//bg->SetDepth(-8);
	//
	//CAM->SetLeftBottom(bg->GetSize() * -0.5f);
	//CAM->SetRightTop(bg->GetSize() * +0.5f);


}
