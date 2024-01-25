#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, .0f)
{
	SetShader(ShaderPath + L"VertexTexture.hlsl");

	animator = new Animator();
	Texture2D* srcTex = new Texture2D(TexturePath + L"Character.png");
	AnimationClip* RunD = new AnimationClip(L"RunD", srcTex, 4, Values::ZeroVec2, { srcTex->GetWidth(), srcTex->GetHeight() * 0.25f });
	AnimationClip* RunU = new AnimationClip(L"RunU", srcTex, 4, { 0, srcTex->GetHeight() * 0.25f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f }, true);
	AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 4, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() * 0.75f }, true);
	AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 4, { 0, srcTex->GetHeight() * 0.75f }, { srcTex->GetWidth(), srcTex->GetHeight() }, true);

	// 애니메이션 저장
	animator->AddAnimClip(RunD);
	animator->AddAnimClip(RunU);
	animator->AddAnimClip(RunL);
	animator->AddAnimClip(RunR);
	animator->SetCurrentAnimClip(L"RunL");

	SAFE_DELETE(srcTex);

	// Sampler
	{
		// 선형 보간
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// point sampling
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);
		
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}
}

AnimationRect::~AnimationRect()
{

}

void AnimationRect::Update()
{
	if (Keyboard::Get()->Down('W'))
	{
		animator->SetCurrentAnimClip(L"RunU");
	}
	else if (Keyboard::Get()->Down('S'))
	{
		animator->SetCurrentAnimClip(L"RunD");
	}
	else if (Keyboard::Get()->Down('A'))
	{
		animator->SetCurrentAnimClip(L"RunL");
	}
	else if (Keyboard::Get()->Down('D'))
	{
		animator->SetCurrentAnimClip(L"RunR");
	}
	animator->Update();

	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		// uv 좌표로 봤을 때 3번이 0,0지점
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);

	__super::Update();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();

	//DC->PSSetSamplers(0, 1, &point[0]);
	//DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFF);
}
