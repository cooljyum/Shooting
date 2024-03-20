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

	if (KEY->Down(VK_F2))
		Collider::OnDraw();

	Environment::Get()->Update();
	ObjectManager::Get()->Update();
	SCENE->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Font::Get()->SetColor("White");
	Font::Get()->SetStyle("Default");

	Font::Get()->GetDC()->BeginDraw(); // 출력 관여 하는 얘

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	Font::Get()->RenderText(fps, {100, SCREEN_HEIGHT-10});

	ImGui::Text(fps.c_str());

	ObjectManager::Get()->Render();
	SCENE->Render();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Font::Get()->GetDC()->EndDraw();
	Device::Get()->Present();

}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Environment::Get();
	Font::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Font::Get()->AddColor("White", 1, 1, 1);
	Font::Get()->AddStyle("Default", L"배달의민족 주아");

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
