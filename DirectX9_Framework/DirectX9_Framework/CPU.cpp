

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 7일 토요일  오후 7:46:52. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "CPU.h"


void CCPU::initialize(void)
{
	PDH_STATUS status;

	// 시스템 CPU 사용량을 가져올 수 있는 없는지에 대한 여부를 나타내는 Flag
	m_bCanReadCPU = true;

	// CPU 사용량을 가져오기 위한 쿼리 객체를 생성
	status = PdhOpenQuery(NULL, 0, &m_hQuery);

	if (ERROR_SUCCESS != status){

		m_bCanReadCPU = false;

	}

	// 쿼리를 모든 CPU를 대상으로 설정
	status = PdhAddCounter(m_hQuery, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_hCounter);
	
	if (status != ERROR_SUCCESS){
	
		m_bCanReadCPU = false;

	}

	m_lCPUusage = GetTickCount();

	m_lCPUusage = 0;
}


void CCPU::update(void)
{

	PDH_FMT_COUNTERVALUE value;

	if (m_bCanReadCPU){
		// 매 프레임 마다 질의하지 않고 1초 간격으로 질의를 하는 방식으로
		// 질의 횟수를 줄임에 따라 성능 향상 도모
		if ((m_ulLastSampleTime + 1000) < GetTickCount()){
		
			m_ulLastSampleTime = GetTickCount();

			PdhCollectQueryData(m_hQuery);
			PdhGetFormattedCounterValue(m_hCounter, PDH_FMT_LONG, NULL, &value);

			m_lCPUusage = value.longValue;

		}

	}

}


void CCPU::deinitialize(void)
{
	if (m_bCanReadCPU){
	
		PdhCloseQuery(m_hQuery);

	}

	m_bCanReadCPU = false;
}