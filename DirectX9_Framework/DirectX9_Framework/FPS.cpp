

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    ����ȭ
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015�� 2�� 7�� �����  ���� 7:31:28. Jack Ryan all rights reserved.
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
	// �� �����Ӹ��� count ���� ���� ��Ŵ
	++m_iCount;

	// ���� �ð����� 1000�� ���� �� 1�ʰ� ���� ������ ����
	if (timeGetTime() >= (m_lStartTime + 1000)){

		// 1�ʵ��� �� �������� �ҷȴ����� ���� fps ������ ����
		m_iFPS = m_iCount;
		// count ���� �ٽ� �ʱ�ȭ
		m_iCount = 0;
		// ���� �ð� ���ð��η� �缳��
		m_lStartTime = timeGetTime();

	}

}


void CFPS::deinitialize(void)
{

	m_iFPS = 0;
	m_iCount = 0;
	m_lStartTime = 0;

}
