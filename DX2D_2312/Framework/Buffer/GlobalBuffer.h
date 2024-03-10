#pragma once
//Global Buffer

class ColorBuffer : public ConstBuffer
{
public:	
	ColorBuffer() : ConstBuffer(&color, sizeof(Float4))
	{
	}

	void SetColor(float r, float g, float b, float a = 1.0f)
	{
		color = { r, g, b, a };
	}

	Float4 GetColor() { return color; }

private:
	Float4 color = { 1, 1, 1, 1 };
};

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer() : ConstBuffer(&matrix, sizeof(Matrix))
	{
		matrix = XMMatrixIdentity();
	}

	void Set(Matrix value)
	{
		matrix = XMMatrixTranspose(value);
	}

private:
	Matrix matrix;
};