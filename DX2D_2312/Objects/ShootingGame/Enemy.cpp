#include "Framework.h"

Enemy::Enemy() : Quad(L"Resources/Textures/Shooting2/enemy_.png")
{
	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);

	SetActive(false);
	
}

Enemy::Enemy(wstring textureFile) : Quad(textureFile)
{
	collider = new CircleCollider(size.x * 0.5f);
	collider->SetParent(this);

	SetActive(false);
}

Enemy::~Enemy()
{
	delete collider;
}

void Enemy::Update()
{
    if (!IsActive()) return;

    Quad::Update();
    collider->UpdateWorld();
    Plane* plane = (Plane*)target;
    Vector2 direction = target->GetGlobalPosition() - this->GetGlobalPosition();


    if (!type)
    {
        Rotate(rotSpeed * DELTA);
        Translate(direction.Normalized() * moveSpeed * DELTA);
    }
    else
    {
        if (collider->IsCollision(plane->GetReactionCollider()))
        {
            playTime += DELTA;
            if (playTime >= FIRE_INTERVAL)
            {
                playTime -= FIRE_INTERVAL;
                BulletManager::Get()->Fire(this->GetGlobalPosition(), direction.Normalized(), true);
            }
        }
        else
            Translate(direction.Normalized() * moveSpeed * DELTA);

        if (BulletManager::Get()->Collision("EnemyBullet", plane->GetCollider()))
            Plane::health--;
    }

    if (collider->IsCollision(plane->GetCollider()))
    {
        Die();
        Plane::health--;
    }

    if (collider->IsCollision(plane->GetSkillCollider()))
        Die();

    if (BulletManager::Get()->Collision("PlayerBullet", collider))
        Die();
    
}

void Enemy::Render()
{
	Quad::Render();
	collider->Render();
}

void Enemy::Die()
{
    SetActive(false);
    Plane::score++;
    if (Random(0, 2))
        ItemManager::Get()->Spawn(GetGlobalPosition(), GetRight());
}
