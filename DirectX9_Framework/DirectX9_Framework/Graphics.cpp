

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 1월 26일 월요일  오후 6:03:22. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "Graphics.h"

#include "Sprite_UI.h"

void CGraphics::render(const int &iFPS, const int &iCPU, const float &fFrameTime) const
{	

	m_cpD3DMain->beginScene();

	m_cpD3DSpriteMgr->render();


#ifdef _DEBUG
	m_cpD3DFont->drawText(100, 100, 10, 20, "FPS : ", iFPS);
	m_cpD3DFont->drawText(100, 120, 10, 40, "CPU : ", iCPU, "%");
	m_cpD3DFont->drawText(100, 140, 10, 60, "FrameTime : ", fFrameTime);
#endif	

	m_cpD3DMain->endScene();

}


void CGraphics::initialize(HWND &hWnd, const Window::shrdWININFO &winInfo)
{

	m_cpD3DMain = CD3D_Main::getInstancePtr();

	m_cpD3DMain->initialize(hWnd, winInfo);

	m_cpD3DFont = CD3D_Font::getInstancePtr();

	m_cpD3DFont->initialize(m_cpD3DMain->getD3DDevicePtr());

	m_cpD3DSpriteMgr = CD3D_SpriteManager::getInstancePtr();

	m_cpD3DSpriteMgr->initialize(m_cpD3DMain->getD3DDevicePtr());

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