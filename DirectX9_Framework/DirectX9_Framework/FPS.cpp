

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 7일 토요일  오후 7:31:28. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "FPS.h"


void CFPS::initialize(void)
{

	m_iFPS = 0;
	m_iCount = 0;
	m_lStartTime = timeGetTime();

}


void CFPS::update(void)
{
	// 매 프레임마다 count 값을 증가 시킴
	++m_iCount;

	// 시작 시간에서 1000을 더한 즉 1초가 지난 시점이 오면
	if (timeGetTime() >= (m_lStartTime + 1000)){

		// 1초동안 몇 프레임이 불렸는지에 대해 fps 변수에 저장
		m_iFPS = m_iCount;
		// count 값은 다시 초기화
		m_iCount = 0;
		// 시작 시간 현시간부로 재설정
		m_lStartTime = timeGetTime();

	}

}


void CFPS::deinitialize(void)
{

	m_iFPS = 0;
	m_iCount = 0;
	m_lStartTime = 0;

}
