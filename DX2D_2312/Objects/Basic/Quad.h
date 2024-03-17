#pragma once

class Quad : public GameObject
{
public:
	Quad(Vector2 size = { 100, 100 }, bool isAdd = true);
	Quad(wstring textureFile, bool isAdd = true);
	~Quad();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(wstring textureFile);

	Vector2 GetSize() { return size * GetGlobalScale(); }

private:
	void MakeMesh();

protected:
	Mesh<VertexUV>* mesh;	

	Vector2 size;	
};
