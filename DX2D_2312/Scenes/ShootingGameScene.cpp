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

	SetBG();
}

ShootingGameScene::~ShootingGameScene()
{
	BulletManager::Delete();
	EnemyManager::Delete();
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
}

void ShootingGameScene::SetBG()
{
	CAM->SetFix(false);

	wstring path = L"Resources/Textures/Shooting/";
	background = new Background(path + L"background.png");
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
