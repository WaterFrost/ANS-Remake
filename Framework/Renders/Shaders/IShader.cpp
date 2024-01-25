#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // 컴파일러 오류 메세지를 저장할 Blob 포인터
    ID3DBlob* error = nullptr;

    // 쉐이더 파일을 컴파일하고, 결과를 Blob 포인터로 전달 받음
    // HRESULT는 Dx를 통해 무언가를 만들때 에러가 발생하는지 아닌지 확인해주는 용도
    HRESULT hr = D3DCompileFromFile
    (
        path.c_str(),                   // 컴파일할 쉐이더 파일 경로
        nullptr,                        // 쉐이더 파일의 헤더를 나타내는 포인터
        nullptr,                        // Include 인터페이스를 구현한 클래스를 사용해 쉐이더 
                                        // 파일에서 다른 파일을 include할때 사용할 수 있는 컨택스트
        entryName.c_str(),              // 컴파일할 쉐이더 파일에서 최조 진입점으로 사용할 함수 이름
        profile.c_str(),                // 컴파일할 쉐이더 파일에서 사용할 프로필 이름
        D3DCOMPILE_ENABLE_STRICTNESS,   // 엄격한 컴파일 옵션 / 경고 메세지를 레벨 1로 설정
        0,                              // 디버그 정보가 포함된 컴파일 결과를 생성하기 위한 옵션
        blob,                           // 컴파일 결과를 저장할 blob 포인터 주소값
        &error                          // 컴파일러 오류 메세지를 저장할 blob 포인터 주소값
    );
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);            // I로 시작하는 인터페이스 변수들은 전부 릴리즈 해줘야 한다.
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    // HRESULT가 실패했을 경우
    if (FAILED(hr))
    {
        // error가 존재할 경우
        if (error)
        {
            // error 메세지를 문자열로 가져와서 메세지 박스로 error를 출력
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // 프로그램 중단
        CHECK(false);
    }
}

/*
ID3DBlob
- 메모리에 할당된 데이터 덩어리
- 대표적으로 쉐이더 코드나 버퍼 데이터 등
- 메모리에 할당된 데이터 덩이를 조작하고 정보를 추출할 수 있음
- I로 시작하는 인터페이스 이기 때문에 직접 만들어 쓰는것이 아닌 이미 만들어져 있는
것을 빌려 오는 개념
- 그렇기에 해당 Blob의 데이터를 임의적으로 만들어 낼순 없다.
*/