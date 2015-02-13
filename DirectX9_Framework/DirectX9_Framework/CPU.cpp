

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    ����ȭ
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015�� 2�� 7�� �����  ���� 7:46:52. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "CPU.h"


void CCPU::initialize(void)
{
	PDH_STATUS status;

	// �ý��� CPU ��뷮�� ������ �� �ִ� �������� ���� ���θ� ��Ÿ���� Flag
	m_bCanReadCPU = true;

	// CPU ��뷮�� �������� ���� ���� ��ü�� ����
	status = PdhOpenQuery(NULL, 0, &m_hQuery);

	if (ERROR_SUCCESS != status){

		m_bCanReadCPU = false;

	}

	// ������ ��� CPU�� ������� ����
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
		// �� ������ ���� �������� �ʰ� 1�� �������� ���Ǹ� �ϴ� �������
		// ���� Ƚ���� ���ӿ� ���� ���� ��� ����
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