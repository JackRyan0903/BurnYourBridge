

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 9일 금요일  오전 5:41:32. Jack Ryan all rights reserved.
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
	// 윈도우 초기화
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

		// 메세지가 있는 경우
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		// 종료 메시지인 경우
		if (WM_QUIT == msg.message){

			break;

		}
		else{

			// 게임 루프
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

    // 윈도우 닫음.
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
	// winInfo로부터 포인터를 받아와 멤버 변수에 주소 값을 저장함.
	m_pWinInfo = winInfo.get();

	int posX, posY;
	int iScreenWidth = 0;
	int iScreenHeight = 0;

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;


	// 이 어플리케이션의 인스턴스를 가져옴.
	m_hInstance = GetModuleHandle(NULL);

	// 어플리케이션의 이름을 설정.
	m_strAppName = m_pWinInfo->wcsAppName;

	// 윈도우 클래스를 기본 설정으로 맞춤.
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

	// 윈도우 클래스를 등록.
	RegisterClassEx(&wc);

	// 모니터 화면의 해상도를 가져옴.
	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 풀스크린 모드 변수의 값에 따라 화면 설정.
	if (m_pWinInfo->bIsFullScreen)
	{
		// 만약 풀스크린 모드라면 화면 크기를 데스크톱 크기에 맞추고 색상을 32bit로 설정.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)iScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)iScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 풀스크린에 맞는 디스플레이 설정.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// 윈도우의 위치를 화면의 왼쪽 위로 설정.
		posX = posY = 0;

		m_pWinInfo->iScreenSize_X = iScreenWidth;
		m_pWinInfo->iScreenSize_Y = iScreenHeight;
	}
	else
	{

		iScreenWidth = m_pWinInfo->iScreenSize_X;
		iScreenHeight = m_pWinInfo->iScreenSize_Y;

		// 창을 모니터의 중앙에 오도록 설정.
		posX = (GetSystemMetrics(SM_CXSCREEN) - iScreenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - iScreenHeight) / 2;
	}

	// 설정한 것을 가지고 창을 만들고 그 핸들을 멤버 변수로 저장.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_strAppName, m_strAppName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, iScreenWidth, iScreenHeight, NULL, NULL, m_hInstance, NULL);

	// 윈도우를 화면에 표시하고 포커스 줌.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	// 마우스 커서를 표시하지 않음.
	ShowCursor(false);

	return;
}

void CSystemClass::shutdownWindows(void)
{
	// 마우스 커서를 표시.
	ShowCursor(true);

	// 풀스크린 모드를 빠져나올 때 디스플레이 설정을 바꿈.
	if (m_pWinInfo){

		if (m_pWinInfo->bIsFullScreen)
		{

			ChangeDisplaySettings(NULL, 0);

		}

	}

	// 창을 제거.
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;

	// 어플리케이션 인스턴스를 제거.
	UnregisterClass(m_strAppName, m_hInstance);
	m_hInstance = nullptr;

	return;
}