#include "Framework.h"

BaseBullet::BaseBullet(wstring textureFile)
	: Bullet(textureFile)
{
	collider = new CircleCollider(size.x);
	collider->SetParent(this);
}

void BaseBullet::Update()
{
	if (!IsActive()) return;

	Translate(GetRight() * data.speed * DELTA);

	if (!CAM->ContainFrustum(this))
		SetActive(false);

	Bullet::Update();
}
