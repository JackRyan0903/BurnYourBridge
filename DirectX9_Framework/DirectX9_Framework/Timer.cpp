

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 8일 일요일  PM 10:35:04. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "Timer.h"

void CTimer::initialize(void)
{	

	// 고해상도 타이머를 시스템이 지원하는지에 대한 여부를 알아봄
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_i64Frequency);
	
	// 실패할 경우 에러 throw
	if (m_i64Frequency == 0){

		return throw std::runtime_error(std::string("This system doesn't support performacne timers."));

	}
	
	// 주파수 단위 틱이 매 밀리 초 마다 몇번이나 불리는지 계산
	m_fTicksPerMs = (float)(m_i64Frequency / 1000);

	// 시작 시간 저장
	QueryPerformanceCounter((LARGE_INTEGER*)&m_i64StartTime);

}


void CTimer::update(void)
{

	INT64 currentTime;
	float timeDifference;

	// 현재 시간 저장
	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	// 시작 시간에서 현재 시간을 빼줌 = 지난 시간
	timeDifference = (float)(currentTime - m_i64StartTime);

	// 지난 시간을 앞에서 구해놓은 주파수 단위 틱으로 나누어 줌으로 써 정확한 프레임 타임을 구함
	m_fFrameTime = timeDifference / m_fTicksPerMs;

	// 시작 시간 초기화
	m_i64StartTime = currentTime;

}


void CTimer::deinitialize(void)
{

	m_fTicksPerMs = 0;
	m_fFrameTime = 0;
	m_i64Frequency = 0;
	m_i64StartTime = 0;

}