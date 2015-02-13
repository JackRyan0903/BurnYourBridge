

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 1월 23일 금요일  오후 8:07:27. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "D3D_Main.h"

void CD3D_Main::initialize(HWND &hWnd, const std::shared_ptr<Window::stWinInfo> &winInfo)
{
	BOOL bIsWindowed;



	if (winInfo->bIsFullScreen){

		bIsWindowed = FALSE;

	}
	else{

		bIsWindowed = TRUE;

	}

	m_hD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_hD3D){

#ifdef _DEBUG
		Debug::consoleMessage("Direct3D Object initialized successfuly.");
#endif

	}
	else{

		throw std::runtime_error("Direct3D Object initialization is failed.");

	}

	D3DFORMAT format;
	D3DDEVTYPE devicetype; //We'll need this and format later
	if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, bIsWindowed) != D3D_OK)
		//Best format, almost always works
	{
		if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_HAL, D3DFMT_X1R5G5B5, D3DFMT_X1R5G5B5, bIsWindowed) != D3D_OK) {
			if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_HAL, D3DFMT_R5G6B5, D3DFMT_R5G6B5, bIsWindowed) != D3D_OK) {
				devicetype = D3DDEVTYPE_REF;
				if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_REF, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, bIsWindowed) != D3D_OK) {
					if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_REF, D3DFMT_X1R5G5B5, D3DFMT_X1R5G5B5, bIsWindowed) != D3D_OK) {
						if (m_hD3D->CheckDeviceType(0, D3DDEVTYPE_REF, D3DFMT_R5G6B5, D3DFMT_R5G6B5, bIsWindowed) != D3D_OK) {
							//Error - No valid format or device detected!
							//You need to decide what to do - if it is windowed, you can try using D3DFMT_UNKNOWN
						}
						else {
							format = D3DFMT_R5G6B5;
						}
					}
					else {
						format = D3DFMT_X1R5G5B5;
					}
				}
				else {
					format = D3DFMT_X8R8G8B8;
				}
			}
			else {
				devicetype = D3DDEVTYPE_HAL;
				format = D3DFMT_R5G6B5;
			}
		}
		else {
			devicetype = D3DDEVTYPE_HAL;
			format = D3DFMT_X1R5G5B5;
		}
	}
	else {
		devicetype = D3DDEVTYPE_HAL;
		format = D3DFMT_X8R8G8B8;
	}



	m_d3dPresentParam.BackBufferWidth = winInfo->iScreenSize_X;
	m_d3dPresentParam.BackBufferHeight = winInfo->iScreenSize_Y;
	m_d3dPresentParam.BackBufferFormat = format;
	m_d3dPresentParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dPresentParam.MultiSampleQuality = 0;
	m_d3dPresentParam.hDeviceWindow = hWnd;
	m_d3dPresentParam.Windowed = bIsWindowed;
	m_d3dPresentParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dPresentParam.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	m_d3dPresentParam.BackBufferCount = 1;
	m_d3dPresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dPresentParam.EnableAutoDepthStencil = FALSE;
	m_d3dPresentParam.Flags = 0;

	if (0 == m_hD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dPresentParam, &m_hD3DDevice)){

#ifdef _DEBUG
		Debug::consoleMessage("Direct3D device createed successfuly.");
#endif

	}
	else{

		throw std::runtime_error("Direct3D device creating is failed.");

	}

}


void CD3D_Main::beginScene(void)
{

	m_hD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(25, 25, 25), 1.0f, 0);

	m_hD3DDevice->BeginScene();
	
}

void CD3D_Main::endScene(void)
{

	m_hD3DDevice->EndScene();

	m_hD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);

}


void CD3D_Main::deinitialize(void)
{
	if (m_hD3DDevice){

		m_hD3DDevice->Release();
		m_hD3DDevice = nullptr;
	}

	if (m_hD3D){

		m_hD3D->Release();
		m_hD3D = nullptr;
	}
}
