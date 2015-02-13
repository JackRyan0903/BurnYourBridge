

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 9일 금요일  오전 5:33:01. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @정의
/*	@설명
/*		1. WIN32_LEAN_AND_MEAN : 자주 사용하는 api를 제외한 나머지 api들의 참조는 생략
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#define WIN32_LEAN_AND_MEAN

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @포함
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include "stdafx.h"
#include "Graphics.h"
#include "FPS.h"
#include "CPU.h"
#include "Timer.h"

//================================================================================//
//  @클래스
//	@설명
//		Window 초기화 및 윈도우 메시지 루프 관리 클래스
//  @포함 함수
//      1. initialize() : 윈도우 초기화
//      2. messageLoop() : 윈도우 메시지 루프
//      3. deinitialize() : 윈도우 종료 시 메모리 해제
//================================================================================//
class CSystemClass : public DesignPattern::CSingleton < CSystemClass >
{
public:
	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : public
	//  @설명 : Window::stWinInfo 구조체를 매개변수로 받아 System Class를 초기화 하는 함수
	//	@매개변수
	//		1. const std::shared_ptr<Window::stWinInfo> & : Window 정보를 가지고 있는 구조체.
	//			※ 여기서 구조체 내의 변수들은 반드시 유효한 값을 가지고 있어야 함.
	//================================================================================//
	void initialize(const shrdWININFO &winInfo);

	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : public
	//  @설명 : Window 메시지를 PeekMessage()로 처리하고 메시지가 없을 때에는 게임 루프를 진행.	
	//================================================================================//
	void messageLoop(void);

	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : public
	//  @설명 : Window 소멸 시 호출 되는 함수, 메모리 해제 및 윈도우 창을 제거.
	//================================================================================//
	void deinitialize(void);

	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : public
	//  @설명 : Window Message를 처리하는 콜백 함수.
	//================================================================================//
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	CSystemClass()
	{

		m_pWinInfo = nullptr;
		m_strAppName = nullptr;
		m_hInstance = nullptr;
		m_hWnd = nullptr;

		m_cpGraphics = nullptr;
		m_cpFPS = nullptr;
		m_cpCPU = nullptr;
		m_cpTimer = nullptr;

	}


	~CSystemClass()
	{

		if (m_cpGraphics){

			m_cpGraphics->deinitialize();
			m_cpGraphics = nullptr;

		}

		if (m_cpFPS){

			m_cpFPS->deinitialize();
			m_cpFPS = nullptr;

		}

		if (m_cpCPU){

			m_cpCPU->deinitialize();
			m_cpCPU = nullptr;

		}

		if (m_cpTimer){

			m_cpTimer->deinitialize();
			m_cpTimer = nullptr;

		}

	}

private:
	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : private
	//  @설명 : Window Class 구조체를 직접 초기화 해주는 함수.
	//	@매개변수 : 위에 내용과 동일하므로 주석 생략
	//================================================================================//
	void initializeWindows(const shrdWININFO &winInfo);

	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : private
	//  @설명 : 게임 루프.
	//	@반환값
	//		- bool : 게임 루프 도중 종료 메시지를 받을 시 true를 반환, 그 외 경우 false.
	//================================================================================//
	bool update(void);

	//================================================================================//
	//  @멤버 함수
	//	@접근 지정 : private
	//  @설명 : 게임 루르.
	//	@반환값
	//		- bool : 게임 루프 도중 종료 메시지를 받을 시 true를 반환, 그 외 경우 false.
	//================================================================================//
	void shutdownWindows(void);

	//================================================================================//
	//  @복사 생성자
	//  @설명
	//		객체 복사 방지 private
	//		객체 복사 시 묵시적 형변환을 막기위해 explicit 키워드 사용
	//================================================================================//
	explicit CSystemClass(const CSystemClass& copy){}

	//================================================================================//
	//  @연산자 오버로딩=
	//  @설명
	//		객체 복사 방지 private
	//================================================================================//
	CSystemClass& operator=(const CSystemClass& copy){}

private:
	Window::stWinInfo *m_pWinInfo;
	wchar_t *m_strAppName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	//InputClass* m_Input;
	CGraphics* m_cpGraphics;
	CFPS *m_cpFPS;
	CCPU *m_cpCPU;
	CTimer *m_cpTimer;
};


static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{
	// 윈도우가 제거되었는지 확인합니다.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// 윈도우가 닫히는지 확인합니다.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// 다른 모든 메세지들은 system 클래스의 메세지 처리기에 전달합니다.
	default:
	{
		return CSystemClass::getInstancePtr()->MessageHandler(hWnd, message, wParam, lParam);
	}

	}
}