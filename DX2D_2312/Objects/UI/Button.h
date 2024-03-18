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

	void SetEvent(function<void()> event = nullptr) { this->event = event; }

	void SetFrontImg(wstring textureFile) { this->frontImg->SetTexture(textureFile); isFront = true; }
	void SetFrontImgActive(bool isActive) { frontImg->SetActive(isActive); }

private:
	RectCollider* collider;
	FloatValueBuffer* valueBuffer;

	Sprite* frontImg;
	bool isFront;

	function<void()> event;
};