#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minValue, int maxValue)
{
	// random_device : 프로그래머가 제어불가한 난수값을 만들어내며 지역에서 벗어나면 자동으로 소멸한다
	// 또한, random_device 는 호출할 때 마다 다른 난수값을 출력.

	random_device randDevice; // 럭키 srand

	//	uniform_int_distribution<자료형> 변수명(최소값,최대값) : 뽑아낼 랜덤값의 자료형,범위를 지정 가능
	//  uniform_int 도 같은 작동방식을 가지지만 모종의 사유로 사용안함
	// () 안에 작성한 최소값과 최대값을 포함하는 랜덤한 수를 출력한다.
	// Ex) intRand(0, 200); 일경우 0 ~ 200 까지 의 숫자가 나온다.

	uniform_int_distribution<int> intRand(minValue, maxValue);
	
	// 랜덤값을 출력하기 위해서는 unoform과 rand_device를 조합하여 출력된 데이터를 변수에 넣어줘야한다.
	// 이때 변수에 넣어주기 전까지는 변수의 데이터로써 인식되지 않기 때문에 해당 데이터를 다이렉트로 연산,변형시 오류가 발생할수있다.
	// 추가로 intRand(randDevice)의 똑같은 형태의 데이터를 여러번 호출해 여러번 집어넣어도 매번 다른 결과값의 데이터가 들어간다.

	int aValue = intRand(randDevice);

	return aValue;
}

float Random::GetRandomFloat(float minValue, float maxValue)
{
	random_device randDevice;

	// 실수형의 랜덤갑을 얻기 위해서는 uniform_real 형태의클래스를 사용하면 된다.
	// 주의사한은 실수형의 범위는 일반적인 정수형과 달리 표시할수있는 자릿수의 모든값이 랜덤의 범위에 들어가기 때문에 실질적인 제어가 매우 어렵고 매우 작은 값들을 관리해야 하기에 추천하지 않음
	// Ex) floatRand(0.0f,1.0f)
	//0.0000000 ~ 1.0000000 까지의 범위이기 떄문
	uniform_real_distribution<float> floatRand(minValue, maxValue);

	float aValue = floatRand(randDevice);
	return aValue;
}
