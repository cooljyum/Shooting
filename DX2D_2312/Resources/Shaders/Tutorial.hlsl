//Shader : Shade + er - GPU Program
//Sementic : �Ű������� ��ȯ �ڷ����� ��� ���̴��� ��Ÿ���� ��ǥ
//SV : System Value

float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

float4 PS() : SV_TARGET
{
    return float4(1, 1, 0, 1);
}