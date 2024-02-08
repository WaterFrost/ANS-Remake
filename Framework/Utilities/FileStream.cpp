#include "Framework.h"
#include "FileStream.h"

FileStream::FileStream(string path, uint flags)
	:flag(flags)
{
	int iosFlags = ios::binary;

	// 쓰기 / 읽기 모드로 열리는지 확인
	iosFlags |= flags && FILE_STREAM_WRITE ? ios::out : 0;

	iosFlags |= flags && FILE_STREAM_READ ? ios::in : 0;
	if (flags & FILE_STREAM_WRITE)
	{
		// 출력 파일 스트림 오픈
		out.open(path, iosFlags);
		// 만약 파일스트림이 비정상이면
		if (out.fail())
		{
			// 스트림조차 실패시 경로이슈
			out.flush(); // 데이터 지우기
			out.close(); // 스트림 닫기
			assert(false);
		}
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.open(path, iosFlags);
		if(in.fail())
		{
			in.clear(); // 데이터 삭제
			in.close(); // 스트림 닫기
			assert(false);
		}
	}
}

FileStream::~FileStream()
{
	if (flag & FILE_STREAM_WRITE)
	{
		// 쓰기모드 파일 데이터 지우고 닫기
		out.flush();
		out.close();
	}
	else if (flag & FILE_STREAM_READ)
	{
		// 읽기모드 파일 데이터 지우고 닫기
		in.clear();
		in.close();
	}
}
