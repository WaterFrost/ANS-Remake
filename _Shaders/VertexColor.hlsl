
// VertexInput 구조체 정의
struct VertexInput
{
	// position이라는 변수가 POSITION0 스트림의 위치에 대한 정보를 저장한다.
	float4 position : POSITION0;	// 정점 위치
	float4 color	: COLOR0;		// 정점 색상
};

// PixelInput 구조체 정의
struct PixelInput
{
	// SV는 시스템 상의 세멘틱 값
	float4 position : SV_POSITION0; // 정점 위치
	float4 color	: COLOR0; // 정점 색상
};

// 상수 버퍼 레지스터 b0에 할당된 월드 행렬을 저장하는 상수 버퍼
cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

// 상수 버퍼 레지스터 b1에 할당된 뷰 행렬과, 프로젝션 행렬을 저장하는 상수 버퍼
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);		// 정점의 위치에 월드 행렬을 곱함
	output.position = mul(output.position, _view);		// 결과에 뷰 행렬을 곱함
	output.position = mul(output.position, _projection);// 결과에 포르젝션 행렬을 곱함
	// 이 순서대로 행렬을 곱해주면 글로벌 공간상의 좌표를 알아낼수 있다.
	
	// 색상은 그대로 전달
	output.color = input.color;
	return output;
}

cbuffer AlphaBuffer : register(b0)
{
    float alpha;
}

float4 PS(PixelInput input)	: SV_Target
{
    float4 color = input.color;
    color.r = mul(color.r, alpha);
    color.g = mul(color.g, alpha);
    color.b = mul(color.b, alpha);
    color.a = mul(color.a, alpha);
	
	return color;
}

/*
Semantic : 세멘틱
- HLSL 셰이더에서 데이터의 의미를 지정하는 데 사용되는 문자
- 셰이더가 입력 데이터와 출력 데이터를 올바르게 해석하고 처리할 수 있도록 해준다.
- 변수 이름 뒤에 : 과 함깨 지정
- 시스템 값 세멘틱은 SV_ 접두사로 시작하며, Direct3D에서 정의된 특별한 의미를 지닌다.
- 시스템 값 세멘틱은 셰이더 스테이지 간에 데이터를 전달하는데 사용된다.
(VS에서 output로 보낸 PixelInput값을 PS에서 SV_Target으로 잡아와 사용했다.)

slot
- GPU에서 사용하는 상수 버퍼, 텍스처, 샘플러 등의 자원들을 식별하는 인덱스
- 각 슬롯은 고유한 번호를 가지며, 해당 자원의 유형과 역할에 따라 다르게 할당한다.
- register라는 키워드를 사용하여 지정
- 각 자원이 어떤 슬롯에 할당 될 것인지는 명시적으로 지정할 수 있다.
- 주요 슬롯
	1) 상수 버퍼 슬롯
	- 상수 데이터를 저장하는데 사용되며, VS와 PS에서 공유될 수 있다.
	- 상서 버퍼 슬롯은 register(b#)을 사용하여 지정

	2) 텍스쳐 슬롯
	- 이미지 데이터를 저장하는데 사용
	- 텍스처 버퍼 슬롯은 register(t#)을 사용하여 지정

	3) 샘플러 슬롯
	- 택스처를 샘플링 하는데 사용
	- 샘플링은 그림을 어떻게 불러올 것인지 정도로만 이해해도 충분하다.
	- 샘플러 슬롯은 register(s#)을 사용하여 지정

cbuffer = Constant Buffer : 상수 버퍼
- 셰이더에서 사용하는 전역 변수를 저장하는데 사용
- 각 상수 버퍼 레지스터에는 한 개의 상수 버퍼만 할당할 수 있다.
- 상수 버퍼 내부에는 여러 개의 변수를 선언하는것이 가능하다.
*/