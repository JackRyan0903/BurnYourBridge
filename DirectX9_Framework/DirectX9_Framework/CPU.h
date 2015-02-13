

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    ����ȭ
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015�� 2�� 7�� �����  ���� 7:45:46. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @��ũ
/*  @����
/*      1. #pragma comment(lib, "pdh.lib")
/*          : Pdh.h
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#pragma comment(lib, "pdh.lib")

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @����
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include <Pdh.h>						// CPU Usage
#include "DesignPattern.h"

//================================================================================//
//  @Ŭ����
//	@����
//		�ǽð� CPU��뷮�� ������ ������ �����ϴ� Ŭ����
//  @���� �Լ�
//      1. initialize() : Ŭ���� �ʱ�ȭ (��� ���� �ʱ�ȭ �� CPU ��뷮�� ���� �� �� �ִ� ���� ���� ���� �˻�)
//      2. update() : Ŭ���� ������Ʈ (CPU��뷮�� ������)
//      3. deinitialize() : Ŭ���� ����
//================================================================================//
class CCPU :
	public DesignPattern::CSingleton < CCPU >
{
public:
	void initialize(void);
	void update(void);
	void deinitialize(void);

public:
	CCPU()
	{

		m_bCanReadCPU = false;
		m_lCPUusage = 0;
		m_ulLastSampleTime = 0;		
		
		m_hQuery = nullptr;
		m_hCounter = nullptr;

	}
	~CCPU()
	{

		if (m_bCanReadCPU){

			PdhCloseQuery(m_hQuery);

		}

		m_bCanReadCPU = false;
		m_lCPUusage = 0;
		m_ulLastSampleTime = 0;

		m_hQuery = nullptr;
		m_hCounter = nullptr;

	}

	int getCPUusagePercentage(void) const{
		
		int iUsage = 0;

		if (m_bCanReadCPU){

			iUsage = (int)m_lCPUusage;

		}
		
		return iUsage;
	}

private:
	//================================================================================//
	//  @���� ������
	//  @����
	//		��ü ���� ���� private
	//		��ü ���� �� ������ ����ȯ�� �������� explicit Ű���� ���
	//================================================================================//
	explicit CCPU(const CCPU& copy){}

	//================================================================================//
	//  @������ �����ε�=
	//  @����
	//		��ü ���� ���� private
	//================================================================================//
	CCPU& operator=(const CCPU& copy){}

private:
	bool m_bCanReadCPU;
	long m_lCPUusage;
	unsigned long m_ulLastSampleTime;
	
	HQUERY m_hQuery;
	HCOUNTER m_hCounter;
	
};

