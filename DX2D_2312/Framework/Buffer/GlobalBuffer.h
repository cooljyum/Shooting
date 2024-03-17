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

	void SetColor(Float4 color)
	{
		this->color = color;
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

//상수버퍼는 16의 배수로만 넘겨야 한다.
class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
	{
	}

	float* Get() { return values; }

private:
	float values[4] = {};
};