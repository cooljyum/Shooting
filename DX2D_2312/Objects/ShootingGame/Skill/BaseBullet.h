#pragma once

class BaseBullet : public Bullet
{
public:
    BaseBullet(wstring textureFile);

    void Update() override;
};