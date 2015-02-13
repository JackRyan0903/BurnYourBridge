

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 6일 금요일  오후 9:52:37. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @포함
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include <d3d9.h>
#include <d3dx9core.h>
#include "stdafx.h"


class CD3D_Font : 
	public DesignPattern::CSingleton<CD3D_Font>
{
public:
	void initialize(LPDIRECT3DDEVICE9 lpD3Ddevice)
	{
		if (S_OK == D3DXCreateFont(lpD3Ddevice, 22, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &m_pFont)){
			
#ifdef _DEBUG
			Debug::consoleMessage("Creating Font is success.");
#endif

		}
		else{

			throw std::runtime_error("Creating Font is fail.");

		}

	}

	void drawText(const int &left, const int &top, const int &right, const int &bottom, const char *message, const int &value)
	{
		
		RECT rect;		
		std::stringstream strBuffer;
		wchar_t wcsBuffer[64];		

		strBuffer << message << value;
		
		mbstowcs(wcsBuffer, strBuffer.str().c_str(), strBuffer.str().length() + 1);		

		SetRect(&rect, left, top, right, bottom);
		m_pFont->DrawText(nullptr, wcsBuffer, -1, &rect, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);

	}

	void drawText(const int &left, const int &top, const int &right, const int &bottom, const char *message, const float &value)
	{

		RECT rect;
		std::stringstream strBuffer;
		wchar_t wcsBuffer[64];

		strBuffer << message << value;

		mbstowcs(wcsBuffer, strBuffer.str().c_str(), strBuffer.str().length() + 1);

		SetRect(&rect, left, top, right, bottom);
		m_pFont->DrawText(nullptr, wcsBuffer, -1, &rect, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);

	}

	void drawText(const int &left, const int &top, const int &right, const int &bottom, const char *message, const int &value, const char *message2)
	{

		RECT rect;
		std::stringstream strBuffer;
		wchar_t wcsBuffer[64];

		strBuffer << message << value << message2;

		mbstowcs(wcsBuffer, strBuffer.str().c_str(), strBuffer.str().length() + 1);

		SetRect(&rect, left, top, right, bottom);
		m_pFont->DrawText(nullptr, wcsBuffer, -1, &rect, DT_LEFT | DT_NOCLIP, 0xFFFFFFFF);

	}

	void deinitialize(void)
	{
		if (m_pFont){
			m_pFont->Release();
			m_pFont = nullptr;
		}
	}

public:
	CD3D_Font()
	{
		m_pFont = nullptr;
	}
	~CD3D_Font()
	{
		if (m_pFont){
			m_pFont->Release();
			m_pFont = nullptr;
		}
	}


private:
	//================================================================================//
	//  @복사 생성자
	//  @설명
	//		객체 복사 방지 private
	//		객체 복사 시 묵시적 형변환을 막기위해 explicit 키워드 사용
	//================================================================================//
	explicit CD3D_Font(const CD3D_Font& copy){}

	//================================================================================//
	//  @연산자 오버로딩=
	//  @설명
	//		객체 복사 방지 private
	//================================================================================//
	CD3D_Font& operator=(const CD3D_Font& copy){}

private:
	ID3DXFont *m_pFont;
		
};

