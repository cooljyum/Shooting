#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingGameScene.h"
#include "Scenes/CollisionScene.h"

GameManager::GameManager()
{
	Create();

	//SCENE->Add("Start", new TutorialScene());
	SCENE->Add("Start", new ShootingGameScene());
	//SCENE->Add("Start", new CollisionScene());

	SCENE->ChangeScene("Start");
}

GameManager::~GameManager()
{
	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	ObjectManager::Get()->Update();
	SCENE->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	ObjectManager::Get()->Render();
	SCENE->Render();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
	SceneManager::Delete();	
	Keyboard::Delete();
	Timer::Delete();

	Shader::Delete();
	Texture::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
