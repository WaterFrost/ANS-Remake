#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
	// 매게변수로 받는 요청서, 개수, 블룹 중 하나라도 없으면 프로그램을 폭파시킨다.
	if (!descs || !count || !blob)
		CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,						// InputLayout을 구성하는 각 선언들의 배열
		count,						// InputLayout을 구성하는 선언의 수
		blob->GetBufferPointer(),	// 셰이더 코드를 포함하는 블룹의 대한 포인터
		blob->GetBufferSize(),		// 셰이더 코드 블룹의 크기
		&inputLayout
	);

	// blob = 메모리 블록
}

void InputLayout::SetIA()
{
	// 인풋 어셈플러 스테이지에서 사용할 인풋 레이아웃을 설정
	DC->IASetInputLayout(inputLayout);
}
