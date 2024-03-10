#include "Framework.h"

Environment::Environment()
{
	CreateProjection();
	CreateSamplerState();
	CreateBlendState();
}

Environment::~Environment()
{
	delete viewBuffer;
	delete projectionBuffer;

	samplerState->Release();
	blendState->Release();
}

void Environment::CreateProjection()
{
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();

	Matrix orthographic = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH,
		0.0f, SCREEN_HEIGHT, -1.0f, 1.0f);

	projectionBuffer->Set(orthographic);

	viewBuffer->SetVS(1);
	projectionBuffer->SetVS(2);
}

void Environment::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;		
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;	
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	//LOD(Level Of Detail) : 카메라와의 거리에 따라서 퀄리티를 나누는 기술

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

void Environment::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &blendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}
