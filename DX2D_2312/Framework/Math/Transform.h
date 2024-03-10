#pragma once

class Transform
{
public:
	Transform();
	~Transform() = default;

	void UpdateWorld();
	void RenderUI();

	bool IsActive();

	void Translate(Vector2 direction) { localPosition += direction; }
	void Rotate(float value) { localRotation.z += value; }

	Vector2 GetRight() { return right.Normalized(); }
	Vector2 GetLeft() { return right.Normalized() * -1.0f; }
	Vector2 GetUp() { return up.Normalized(); }
	Vector2 GetDown() { return up.Normalized() * -1.0f; }

	Vector2 GetGlobalPosition() { return globalPosition; }
	Vector2 GetGlobalScale() { return globalScale; }

	string GetTag() { return tag; }	

	void SetLocalPosition(Vector2 pos) { localPosition = pos; }
	void SetLocalRotation(float x, float y, float z) { localRotation = { x, y, z }; }
	void SetLocalScale(Vector2 scale) { localScale = scale; }
	void SetPivot(Vector2 pivot) { this->pivot = pivot; }

	void SetParent(Transform* transform) { parent = transform; }
	void SetActive(bool isActive) { this->isActive = isActive; }

	void SetTag(string tag) { this->tag = tag; }

protected:
	string tag;	

	Vector2 localPosition;
	Float3 localRotation;
	Vector2 localScale = { 1, 1 };	
	Vector2 pivot;

	Matrix world;	
	
private:
	bool isActive = true;

	Transform* parent = nullptr;

	Matrix S, R, T;
	Matrix P, IP;
	XMFLOAT4X4 matWorld;

	Vector2 globalPosition, globalScale;
	Vector2 right, up;
};