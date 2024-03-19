#include "Framework.h"

Enemy::Enemy(EnemyData data) : data(data)
{
	wstring path = L"Resources/Textures/Shooting3/Enemy/";
	SetTexture(path + data.textureFile);

	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);

	SetActive(false);

	path = L"Resources/Textures/Shooting3/UI/";
	wstring front = path + L"EnemyHpBar.png";
	wstring back = path + L"HpBarBg.png";

	hpBar = new ProgressBar(front, back);
	hpBarOffset = { 0, -size.y * 0.6f };
	hpBar->SetActive(false);
	ObjectManager::Get()->Add(hpBar);
	//hpBar->SetParent(this);
	//hpBar->Translate(Vector2::Up() * size.y * 0.5f);
}

Enemy::~Enemy()
{
	delete collider;
	delete hpBar;
}

void Enemy::Update()
{
	if (!IsActive()) return;

	direction = target->GetGlobalPosition() - localPosition;

	Move();

	hpBar->SetLocalPosition(localPosition + hpBarOffset);

	Quad::Update();
	collider->UpdateWorld();

	Collision();	
	RemoveHitCollider();
}

void Enemy::Render()
{
	Quad::Render();
	collider->Render();
}

void Enemy::Spawn()
{
	SetActive(true);
	hpBar->SetActive(true);
	hpBar->SetAmount(1.0f);

	hp = data.maxHp;

	Quad::Update();
	collider->UpdateWorld();
}

void Enemy::Move()
{		
	//Rotate(data.speed * 0.1f * DELTA);
	Translate(direction.Normalized() * data.speed * DELTA);
}

void Enemy::Collision()
{
	Plane* plane = (Plane*)target;
	if (collider->IsCollision(plane->GetCollider()))
		Dead();

	Damage("PlayerBullet");
	Damage("WheelBullet");
}

void Enemy::RemoveHitCollider()
{
	vector<Collider*>::iterator iter = hitColliders.begin();

	for (; iter != hitColliders.end();)
	{
		if (collider->IsCollision(*iter))
		{
			iter++;
		}
		else//�����������
		{
			iter = hitColliders.erase(iter);			
		}
	}

}

void Enemy::Damage(string key)
{
	Bullet* bullet = BulletManager::Get()->Collision(key, collider);

	if (bullet == nullptr) return;

	SkillData skillData = bullet->GetData();
	int type = skillData.key / 100;

	switch (type)
	{
	case 1:
		bullet->SetActive(false);
		break;
	case 2:
	{
		for (Collider* hitCollider : hitColliders)
		{
			if (hitCollider == bullet->GetCollider())
				return;
		}

		hitColliders.push_back(bullet->GetCollider());
	}
		break;
	}
	Plane* plane = (Plane*)target;
	hp -= (skillData.power + plane->GetAttack()*0.1f);
	hpBar->SetAmount((float)hp / (float)data.maxHp);

	if (hp <= 0)
		Dead();
}

void Enemy::Dead()
{
	SetActive(false);
	hpBar->SetActive(false);

	//if (Random(0, 2))
	ItemManager::Get()->Spawn(localPosition);
}
