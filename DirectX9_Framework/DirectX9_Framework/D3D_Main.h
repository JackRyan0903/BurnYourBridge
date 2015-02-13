

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 21일 수요일  오전 12:07:20. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

#include <d3d9.h>
#include <d3dx9tex.h>
#include "stdafx.h"


class CD3D_Main : public DesignPattern::CSingleton < CD3D_Main >
{
public:
	void initialize(HWND &hWnd, const std::shared_ptr<Window::stWinInfo> &winInfo);
	

	void beginScene(void);
	
	
	void endScene(void);
	

	void deinitialize(void);

public:
	CD3D_Main()
	{
		m_hD3D = nullptr;
		m_hD3DDevice = nullptr;
	}
	~CD3D_Main()
	{
		if (m_hD3DDevice){

			m_hD3DDevice->Release();			

		}
		if (m_hD3D){			

			m_hD3D->Release();

		}

		m_hD3DDevice = nullptr;
		m_hD3D = nullptr;
	}

	LPDIRECT3DDEVICE9 getD3DDevicePtr()
	{
		return m_hD3DDevice;
	}

private:

	//================================================================================//
	//  @복사 생성자
	//  @설명
	//		객체 복사 방지 private
	//		객체 복사 시 묵시적 형변환을 막기위해 explicit 키워드 사용
	//================================================================================//
	explicit CD3D_Main(const CD3D_Main& copy){}

	//================================================================================//
	//  @연산자 오버로딩=
	//  @설명
	//		객체 복사 방지 private
	//================================================================================//
	CD3D_Main& operator=(const CD3D_Main& copy){}

private:
	LPDIRECT3D9 m_hD3D;
	LPDIRECT3DDEVICE9 m_hD3DDevice;

	D3DPRESENT_PARAMETERS m_d3dPresentParam;
	
};

