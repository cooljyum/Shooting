#include "Framework.h"

Material::Material()
{
	vertexShader = Shader::AddVS(L"VertexUV.hlsl");
	pixelShader = Shader::AddPS(L"PixelUV.hlsl");
}

Material::Material(wstring textureFile, wstring shaderFile)
{
	vertexShader = Shader::AddVS(L"VertexUV.hlsl");
	pixelShader = Shader::AddPS(shaderFile);

	texture = Texture::Add(textureFile);
}

void Material::Set()
{
	if (texture)
		texture->PSSet(0);

	vertexShader->Set();
	pixelShader->Set();
}

void Material::SetTexture(wstring file)
{
	texture = Texture::Add(file);
}

void Material::SetVertexShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
}

void Material::SetPixelShader(wstring file)
{
	pixelShader = Shader::AddPS(file);
}
