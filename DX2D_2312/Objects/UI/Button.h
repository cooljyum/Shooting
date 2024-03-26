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
	Button(wstring path = L"Resources / Textures / Shooting3 / UI / equipTxt_B.png");
	Button(wstring textureFile = L"Resources/Textures/UI/Button.png", bool isAdd = false);
	Button(wstring path, Vector2 pos, bool isAdd = false);
	~Button();
	void Update() override;
	
	void Render() override;
	void PostRender();

	void Collision();

	void ClickEvent();

	void SetEvent(Event event = nullptr) { clickEvent = event; }
	void SetIntEvent(IntParamEvent event, int param)
	{
		clickIntParamEvent = event, intParam = param;
	}
	void SetObjectEvent(ObjectParamEvent event, void* param)
	{
		clickObjectParamEvent = event, objectParam = param;
	}

	void SetText(string text) { this->text = text; }
	void SetTextData(string color, string style)
	{
		textColor = color, textStyle = style;
	}

	void SetFrontImg(wstring textureFile) { this->frontImg->SetTexture(textureFile); isFront = true; }
	void SetFrontImgActive(bool isActive) { frontImg->SetActive(isActive); }

private:
	RectCollider* collider;
	FloatValueBuffer* valueBuffer;

	Sprite* frontImg;
	bool isFront;

	State state = NORMAL;

	Event clickEvent = nullptr;
	IntParamEvent clickIntParamEvent = nullptr;
	ObjectParamEvent clickObjectParamEvent = nullptr;


	bool isDownCheck = false;

	string text;
	string textColor = "Black";
	string textStyle = "Button";

	int intParam = 0;
	void* objectParam = nullptr;
};