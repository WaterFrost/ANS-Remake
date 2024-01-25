#include "Framework.h"
#include "IShader.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
    Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
    // 쉐이더 경로와 엔트리 이름을 저장
    this->path = path;
    this->entryName = entryName;

    // 쉐이더 컴파일을 ps(픽셀 쉐이더)5.0 버전으로 해라
    CompileShader(path, entryName, "ps_5_0", &blob);

    // 버택스 쉐이더 생성
    HRESULT hr = DEVICE->CreatePixelShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void PixelShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
    DC->PSSetShader(shader, nullptr, 0);
}
