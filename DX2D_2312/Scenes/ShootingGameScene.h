#pragma once

class ShootingGameScene : public Scene
{
public:
	ShootingGameScene();
	~ShootingGameScene();
		
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	BackGround* bg;	
	Plane* plane;	
};