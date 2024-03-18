#pragma once

class Button : public Quad
{
private:
	enum State
	{
		NORMAL, OVER, DOWN
	};

	const Float4 NORMAL_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
	const Float4 OVER_COLOR = { 0.9f, 0.9f, 0.9f, 0.9f };
	const Float4 DOWN_COLOR = { 0.5f, 0.5f, 0.5f, 0.5f };

public:
	Button(wstring path);
	Button(wstring path, Vector2 pos);
	~Button();
	void Update() override;
	
	void Render() override;
	void PostRender();
	void Collision();

	void ClickEvent();

	void SetEvent(Event clickEvent = nullptr) { this->clickEvent = clickEvent; }

	void SetFrontImg(wstring textureFile) { this->frontImg->SetTexture(textureFile); isFront = true; }
	void SetFrontImgActive(bool isActive) { frontImg->SetActive(isActive); }

private:
	RectCollider* collider;
	FloatValueBuffer* valueBuffer;

	Sprite* frontImg;
	bool isFront;

	State state = NORMAL;

	Event clickEvent = nullptr;

	bool isDownCheck = false;
};