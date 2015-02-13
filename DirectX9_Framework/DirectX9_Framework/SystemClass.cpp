

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    ����ȭ
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015�� 1�� 9�� �ݿ���  ���� 5:41:32. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "SystemClass.h"



bool CSystemClass::update(void)
{
	
	m_cpFPS->update();
	m_cpCPU->update();
	m_cpTimer->update();
	
	m_cpGraphics->update(m_cpFPS->getFPS(), m_cpCPU->getCPUusagePercentage(), m_cpTimer->getFrameTime());
	
	return false; 

}


void CSystemClass::initialize(const shrdWININFO &winInfo)
{
	// ������ �ʱ�ȭ
    initializeWindows(winInfo);
 
	m_cpGraphics = CGraphics::getInstancePtr();
	m_cpFPS = CFPS::getInstancePtr();
	m_cpCPU = CCPU::getInstancePtr();
	m_cpTimer = CTimer::getInstancePtr();
	

	m_cpGraphics->initialize(m_hWnd, winInfo);
	m_cpFPS->initialize();
	m_cpCPU->initialize();
	m_cpTimer->initialize();

}


void CSystemClass::messageLoop(void)
{
	MSG msg;
	bool bIsQuit = false;

	ZeroMemory(&msg, sizeof(MSG));

	while (true){

		// �޼����� �ִ� ���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		// ���� �޽����� ���
		if (WM_QUIT == msg.message){

			break;

		}
		else{

			// ���� ����
			bIsQuit = update();

			if (bIsQuit){

				break;

			}

		}

	}

}


void CSystemClass::deinitialize(void)
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

    // ������ ����.
	shutdownWindows();
}


LRESULT CALLBACK CSystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{	
	case WM_KEYDOWN:
		///////////	Code for test	///////////
		//	start
		if (VK_ESCAPE == wParam){
			MessageBox(0, L"ESC", L"Key Down", MB_ICONERROR);
		}
		//	end
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;

}

void CSystemClass::initializeWindows(const shrdWININFO &winInfo)
{
	// winInfo�κ��� �����͸� �޾ƿ� ��� ������ �ּ� ���� ������.
	m_pWinInfo = winInfo.get();

	int posX, posY;
	int iScreenWidth = 0;
	int iScreenHeight = 0;

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;


	// �� ���ø����̼��� �ν��Ͻ��� ������.
	m_hInstance = GetModuleHandle(NULL);

	// ���ø����̼��� �̸��� ����.
	m_strAppName = m_pWinInfo->wcsAppName;

	// ������ Ŭ������ �⺻ �������� ����.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_strAppName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// ������ Ŭ������ ���.
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� ������.
	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Ǯ��ũ�� ��� ������ ���� ���� ȭ�� ����.
	if (m_pWinInfo->bIsFullScreen)
	{
		// ���� Ǯ��ũ�� ����� ȭ�� ũ�⸦ ����ũ�� ũ�⿡ ���߰� ������ 32bit�� ����.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)iScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)iScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ���� �´� ���÷��� ����.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// �������� ��ġ�� ȭ���� ���� ���� ����.
		posX = posY = 0;

		m_pWinInfo->iScreenSize_X = iScreenWidth;
		m_pWinInfo->iScreenSize_Y = iScreenHeight;
	}
	else
	{

		iScreenWidth = m_pWinInfo->iScreenSize_X;
		iScreenHeight = m_pWinInfo->iScreenSize_Y;

		// â�� ������� �߾ӿ� ������ ����.
		posX = (GetSystemMetrics(SM_CXSCREEN) - iScreenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - iScreenHeight) / 2;
	}

	// ������ ���� ������ â�� ����� �� �ڵ��� ��� ������ ����.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_strAppName, m_strAppName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, iScreenWidth, iScreenHeight, NULL, NULL, m_hInstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ�� ��.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	// ���콺 Ŀ���� ǥ������ ����.
	ShowCursor(false);

	return;
}

void CSystemClass::shutdownWindows(void)
{
	// ���콺 Ŀ���� ǥ��.
	ShowCursor(true);

	// Ǯ��ũ�� ��带 �������� �� ���÷��� ������ �ٲ�.
	if (m_pWinInfo){

		if (m_pWinInfo->bIsFullScreen)
		{

			ChangeDisplaySettings(NULL, 0);

		}

	}

	// â�� ����.
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	// ���ø����̼� �ν��Ͻ��� ����.
	UnregisterClass(m_strAppName, m_hInstance);
	m_hInstance = nullptr;

	return;
}