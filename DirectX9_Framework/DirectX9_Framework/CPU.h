

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 7일 토요일  오후 7:45:46. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @링크
/*  @설명
/*      1. #pragma comment(lib, "pdh.lib")
/*          : Pdh.h
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#pragma comment(lib, "pdh.lib")

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @포함
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include <Pdh.h>						// CPU Usage
#include "DesignPattern.h"

//================================================================================//
//  @클래스
//	@설명
//		실시간 CPU사용량을 가져와 변수에 저장하는 클래스
//  @포함 함수
//      1. initialize() : 클래스 초기화 (멤버 변수 초기화 및 CPU 사용량을 가져 올 수 있는 지에 대한 여부 검사)
//      2. update() : 클래스 업데이트 (CPU사용량을 가져옴)
//      3. deinitialize() : 클래스 종료
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
	//  @복사 생성자
	//  @설명
	//		객체 복사 방지 private
	//		객체 복사 시 묵시적 형변환을 막기위해 explicit 키워드 사용
	//================================================================================//
	explicit CCPU(const CCPU& copy){}

	//================================================================================//
	//  @연산자 오버로딩=
	//  @설명
	//		객체 복사 방지 private
	//================================================================================//
	CCPU& operator=(const CCPU& copy){}

private:
	bool m_bCanReadCPU;
	long m_lCPUusage;
	unsigned long m_ulLastSampleTime;
	
	HQUERY m_hQuery;
	HCOUNTER m_hCounter;
	
};

