#pragma once

class Button : public Quad
{
public:
	Button(wstring path, Vector2 pos);
	~Button();
	void Update() override;
	
	void Render() override;
	void PostRender();
	void Collision();

	void SetEvent(Event clickEvent = nullptr) { this->clickEvent = clickEvent; }

	void SetFrontImg(wstring textureFile) { this->frontImg->SetTexture(textureFile); isFront = true; }
	void SetFrontImgActive(bool isActive) { frontImg->SetActive(isActive); }

private:
	RectCollider* collider;
	FloatValueBuffer* valueBuffer;

	Sprite* frontImg;
	bool isFront;

	Event clickEvent = nullptr;
};