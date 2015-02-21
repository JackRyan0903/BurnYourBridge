

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 19일 목요일  오전 1:40:23. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "Sprite.h"


void CSprite::initialize(LPDIRECT3DDEVICE9 lpDevice)
{
	int iStringLen = 0;
	wchar_t *wcsFileName = nullptr;

	iStringLen = m_strFileName.length() + 1;
	wcsFileName = new wchar_t[iStringLen];

	mbstowcs(wcsFileName, m_strFileName.c_str(), iStringLen);

	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(lpDevice, wcsFileName, m_iWidth, m_iHeight, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &m_lpTexture))){
	
		if (wcsFileName){
				
			delete wcsFileName;
			wcsFileName = nullptr;

		}
		
		throw std::runtime_error(std::string(m_strName + " is failed to initialize. <Texture>"));

	}
	

	if (wcsFileName){

		delete wcsFileName;
		wcsFileName = nullptr;

	}
	
	if (!SUCCEEDED(D3DXCreateSprite(lpDevice, &m_lpSprite))){
		
		throw std::runtime_error(std::string(m_strName + " is failed to initialize. <Sprite>"));

	}

#ifdef _DEBUG

	Debug::consoleMessage(m_strName + " is initialized completely.");

#endif

}


void CSprite::rener()
{

	if (m_lpTexture && m_lpSprite){
	
		m_lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_lpSprite->Draw(m_lpTexture, nullptr, nullptr, &m_vec3Position, m_col);
	
		m_lpSprite->End();

	}

}


void CSprite::deinitialize()
{

	if (m_lpSprite){
	
		m_lpSprite->Release();
		m_lpSprite = nullptr;

	}

	if (m_lpTexture){
	
		m_lpTexture->Release();
		m_lpTexture = nullptr;
	
	}

}