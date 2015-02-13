

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 1월 26일 월요일  오후 6:03:22. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "Graphics.h"


void CGraphics::render(const int &iFPS, const int &iCPU, const float &fFrameTime) const
{	

	m_cpD3DMain->beginScene();

#ifdef _DEBUG
	m_cpD3DFont->drawText(0, 0, 10, 20, "FPS : ", iFPS);
	m_cpD3DFont->drawText(0, 20, 10, 40, "CPU : ", iCPU, "%");
	m_cpD3DFont->drawText(0, 40, 10, 60, "FrameTime : ", fFrameTime);
#endif

	m_cpD3DMain->endScene();

}


void CGraphics::initialize(HWND &hWnd, const shrdWININFO &winInfo)
{

	m_cpD3DMain = CD3D_Main::getInstancePtr();

	m_cpD3DMain->initialize(hWnd, winInfo);

	m_cpD3DFont = CD3D_Font::getInstancePtr();

	m_cpD3DFont->initialize(m_cpD3DMain->getD3DDevicePtr());

}


void CGraphics::update(const int &iFPS, const int &iCPU, const float &fFrameTime)
{	
	
	render(iFPS, iCPU, fFrameTime);

}


void CGraphics::deinitialize(void)
{

	m_cpD3DMain->deinitialize();

	m_cpD3DFont->deinitialize();

}