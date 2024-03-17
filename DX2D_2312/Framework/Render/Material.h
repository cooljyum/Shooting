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
	ColorBuffer* GetColor() { return colorBuffer; }

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	ColorBuffer* colorBuffer;

	Texture* texture = nullptr;
};