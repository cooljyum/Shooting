#pragma once

class Quad : public GameObject
{
public:
	Quad(Vector2 size);
	Quad(wstring textureFile);
	~Quad();

	virtual void Update() override;
	virtual void Render() override;
	void SetTexture(wstring textureFile);
	
private:

	void MakeMesh();

protected:
	Mesh<VertexUV>* mesh;

	ColorBuffer* colorBuffer;

	Vector2 size;	
};
