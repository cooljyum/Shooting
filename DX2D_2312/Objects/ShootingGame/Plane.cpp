#include "Framework.h"

Plane::Plane() : Quad(L"Resources/Textures/Shooting/player.png")
{
	//colorBuffer->SetColor(Random(0.0f, 1.0f), Random(0.0f, 1.0f), Random(0.0f, 1.0f));

	//pivot = { -100, -100 };

	collider = new CircleCollider(70);
	collider->SetParent(this);

	cursor = new Quad(L"Resources/Textures/Shooting/cursor.png");
	cursor->SetParent(this);
	cursor->Translate(Vector2::Right() * 50.0f);

	skills.push_back(new BaseSkill(this));
	skills.push_back(new WheelSkill(this));

	wstring hpFront = L"Resources/Textures/UI/hp_bar.png";
	wstring hpBack = L"Resources/Textures/UI/hp_bar_BG.png";

	hpBar = new ProgressBar(hpFront, hpBack);
	hpBar->SetLocalPosition({ CENTER_X, SCREEN_HEIGHT * 0.9f });	
	hpBar->UpdateWorld();
}

Plane::~Plane()
{
	delete collider;
	delete cursor;
	delete hpBar;

	for (Skill* skill : skills)
		delete skill;
}

void Plane::Update()
{
	if (KEY->Down('1'))
		skills[0]->LevelUp();

	if (KEY->Press('W'))
		Translate(Vector2::Up() * speed * DELTA);
	if (KEY->Press('S'))
		Translate(Vector2::Down() * speed * DELTA);
	if (KEY->Press('A'))
		Translate(Vector2::Left() * speed * DELTA);
	if (KEY->Press('D'))
		Translate(Vector2::Right() * speed * DELTA);
	//
	//Vector2 direction = mousePos - localPosition;
	//localRotation.z = direction.Angle();

	//localPosition = mousePos;

	//if (KEY->Press('A'))
	//	localRotation.z += DELTA;
	//
	//if (KEY->Press('D'))
	//	localRotation.z -= DELTA;
	//
	//if (KEY->Press('W'))
	//	Translate(GetRight() * speed * DELTA);

	Collision();

	UpdateWorld();
	collider->UpdateWorld();

	cursor->UpdateWorld();
}

void Plane::Render()
{
	Quad::Render();
	collider->Render();
	cursor->Render();	
}

void Plane::PostRender()
{
	collider->RenderUI();

	string str = "HP : " + to_string(hp);
	ImGui::Text(str.c_str());

	hpBar->Render();
}

void Plane::Collision()
{
	Bullet* bullet = BulletManager::Get()->Collision("EnemyBullet", collider);

	if (bullet)
	{
		bullet->SetActive(false);
		hp--;
	}
}
