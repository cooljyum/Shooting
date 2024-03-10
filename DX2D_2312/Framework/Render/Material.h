#pragma once

class Material
{
public:
	Material();
	Material(wstring textureFile, wstring shaderFile = L"PixelUV.hlsl");
	
	void Set();

	void SetTexture(wstring file);

	void SetVertexShader(wstring file);
	void SetPixelShader(wstring file);

	Texture* GetTexture() { return texture; }
private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	Texture* texture = nullptr;
};