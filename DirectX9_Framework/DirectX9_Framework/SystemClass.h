

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    ����ȭ
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015�� 1�� 9�� �ݿ���  ���� 5:33:01. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @����
/*	@����
/*		1. WIN32_LEAN_AND_MEAN : ���� ����ϴ� api�� ������ ������ api���� ������ ����
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#define WIN32_LEAN_AND_MEAN

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @����
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include "stdafx.h"
#include "Graphics.h"
#include "FPS.h"
#include "CPU.h"
#include "Timer.h"

//================================================================================//
//  @Ŭ����
//	@����
//		Window �ʱ�ȭ �� ������ �޽��� ���� ���� Ŭ����
//  @���� �Լ�
//      1. initialize() : ������ �ʱ�ȭ
//      2. messageLoop() : ������ �޽��� ����
//      3. deinitialize() : ������ ���� �� �޸� ����
//================================================================================//
class CSystemClass : public DesignPattern::CSingleton < CSystemClass >
{
public:
	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : public
	//  @���� : Window::stWinInfo ����ü�� �Ű������� �޾� System Class�� �ʱ�ȭ �ϴ� �Լ�
	//	@�Ű�����
	//		1. const std::shared_ptr<Window::stWinInfo> & : Window ������ ������ �ִ� ����ü.
	//			�� ���⼭ ����ü ���� �������� �ݵ�� ��ȿ�� ���� ������ �־�� ��.
	//================================================================================//
	void initialize(const shrdWININFO &winInfo);

	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : public
	//  @���� : Window �޽����� PeekMessage()�� ó���ϰ� �޽����� ���� ������ ���� ������ ����.	
	//================================================================================//
	void messageLoop(void);

	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : public
	//  @���� : Window �Ҹ� �� ȣ�� �Ǵ� �Լ�, �޸� ���� �� ������ â�� ����.
	//================================================================================//
	void deinitialize(void);

	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : public
	//  @���� : Window Message�� ó���ϴ� �ݹ� �Լ�.
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
	//  @��� �Լ�
	//	@���� ���� : private
	//  @���� : Window Class ����ü�� ���� �ʱ�ȭ ���ִ� �Լ�.
	//	@�Ű����� : ���� ����� �����ϹǷ� �ּ� ����
	//================================================================================//
	void initializeWindows(const shrdWININFO &winInfo);

	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : private
	//  @���� : ���� ����.
	//	@��ȯ��
	//		- bool : ���� ���� ���� ���� �޽����� ���� �� true�� ��ȯ, �� �� ��� false.
	//================================================================================//
	bool update(void);

	//================================================================================//
	//  @��� �Լ�
	//	@���� ���� : private
	//  @���� : ���� �縣.
	//	@��ȯ��
	//		- bool : ���� ���� ���� ���� �޽����� ���� �� true�� ��ȯ, �� �� ��� false.
	//================================================================================//
	void shutdownWindows(void);

	//================================================================================//
	//  @���� ������
	//  @����
	//		��ü ���� ���� private
	//		��ü ���� �� ������ ����ȯ�� �������� explicit Ű���� ���
	//================================================================================//
	explicit CSystemClass(const CSystemClass& copy){}

	//================================================================================//
	//  @������ �����ε�=
	//  @����
	//		��ü ���� ���� private
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
	// �����찡 ���ŵǾ����� Ȯ���մϴ�.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// �����찡 �������� Ȯ���մϴ�.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// �ٸ� ��� �޼������� system Ŭ������ �޼��� ó���⿡ �����մϴ�.
	default:
	{
		return CSystemClass::getInstancePtr()->MessageHandler(hWnd, message, wParam, lParam);
	}

	}
}