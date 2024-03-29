#include "Framework.h"
#include "IShader.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
    Clear();
}

void VertexShader::Create(const wstring path, const string entryName)
{
    // 쉐이더 경로와 엔트리 이름을 저장
    this->path = path;
    this->entryName = entryName;

    // 쉐이더 컴파일을 vs(버텍스 쉐이더)5.0 버전으로 해라
    CompileShader(path, entryName, "vs_5_0", &blob);

    // 버택스 쉐이더 생성
    HRESULT hr = DEVICE->CreateVertexShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void VertexShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
    DC->VSSetShader(shader, nullptr, 0);
}
