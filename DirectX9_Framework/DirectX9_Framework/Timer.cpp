

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    ����ȭ
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015�� 2�� 8�� �Ͽ���  PM 10:35:04. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "Timer.h"

void CTimer::initialize(void)
{	

	// ���ػ� Ÿ�̸Ӹ� �ý����� �����ϴ����� ���� ���θ� �˾ƺ�
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_i64Frequency);
	
	// ������ ��� ���� throw
	if (m_i64Frequency == 0){

		return throw std::runtime_error(std::string("This system doesn't support performacne timers."));

	}
	
	// ���ļ� ���� ƽ�� �� �и� �� ���� ����̳� �Ҹ����� ���
	m_fTicksPerMs = (float)(m_i64Frequency / 1000);

	// ���� �ð� ����
	QueryPerformanceCounter((LARGE_INTEGER*)&m_i64StartTime);

}


void CTimer::update(void)
{

	INT64 currentTime;
	float timeDifference;

	// ���� �ð� ����
	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	// ���� �ð����� ���� �ð��� ���� = ���� �ð�
	timeDifference = (float)(currentTime - m_i64StartTime);

	// ���� �ð��� �տ��� ���س��� ���ļ� ���� ƽ���� ������ ������ �� ��Ȯ�� ������ Ÿ���� ����
	m_fFrameTime = timeDifference / m_fTicksPerMs;

	// ���� �ð� �ʱ�ȭ
	m_i64StartTime = currentTime;

}


void CTimer::deinitialize(void)
{

	m_fTicksPerMs = 0;
	m_fFrameTime = 0;
	m_i64Frequency = 0;
	m_i64StartTime = 0;

}