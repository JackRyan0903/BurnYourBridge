

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 19일 목요일  오전 1:24:17. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @포함
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include "stdafx.h"
#include <d3dx9.h>


//================================================================================//
//  @클래스
//	@설명
//		게임 내에 사용 될 2D 스프라이트 들의 조상 클래스
//  @포함 멤버 함수
//		initialize() : D3D 디바이스 객체 포인터 및 이미지 경로, 이미지 크기를 매개변수로
//						받아서 멤버 변수인 texture와 sprite 객체를 초기화하는 함수
//						texture 생성 시 경로 명이 잘못 됬을 시 에러 throw
//						sprite 객체 생성 실패 시 에러 throw
//		update() : 완전 가상 함수 상속 받는 sprite에 따라 업데이트 할 내용을 구현할 것.
//		render() : 화면에 그림 (반드시 device->beginScene()함수와 device->endScene()함수 사이에 있어야 함)
//		deinitialize() : 초기화 했던 texture 객체와 sprite 객체를 release
//================================================================================//
class CSprite
{
public:
	//================================================================================//
	//  @멤버 함수
	//  @설명 : D3D 디바이스 객체 포인터 및 이미지 경로, 이미지 크기를 매개변수로
	//			받아서 멤버 변수인 texture와 sprite 객체를 초기화하는 함수
	//			texture 생성 시 경로 명이 잘못 됬을 시 에러 throw	
	//			sprite 객체 생성 실패 시 에러 throw
	//	@매개변수
	//		- lpDevice : D3D 디바이스 객체 포인터
	//		- strFileName : 스프라이트로 사용될 이미지 파일 경로 (반드시 유효 해야함)
	//		- iWidth : 이미지의 넓이
	//		- iHeight : 이미지의 높이
	//================================================================================//
	virtual void initialize(LPDIRECT3DDEVICE9 lpDevice);


	//================================================================================//
	//  @멤버 함수
	//  @설명 : 완전 가상 함수 상속 받는 sprite에 따라 업데이트 할 내용을 구현할 것.
	//================================================================================//
	virtual void update() = 0;


	//================================================================================//
	//  @멤버 함수
	//  @설명 : 화면에 그림 (반드시 device->beginScene()함수와 device->endScene()함수 사이에 있어야 함)
	//================================================================================//
	virtual void rener();

	//================================================================================//
	//  @멤버 함수
	//  @설명 : 초기화 했던 texture 객체와 sprite 객체를 release
	//================================================================================//
	virtual void deinitialize();

public:
	//================================================================================//
	//  @생성자
	//  @매개변수
	//		- name : 객체 구분을 하기 위한 고유 이름 ( 중복이 없도록 할 것 )
	//		- x : 객체가 화면에 뿌려질 x위치
	//		- y : 객체가 화면에 뿌려질 y좌표
	//================================================================================//
	CSprite(const std::string &strSpriteName, const std::string &strFileName, const float &fPosX, const float &fPosY, const int &iWidth, const int &iHeight)
		: m_strName(strSpriteName), m_strFileName(strFileName), m_iWidth(iWidth), m_iHeight(iHeight)
	{
		
		m_vec3Position.x = fPosX;
		m_vec3Position.y = fPosY;
		m_vec3Position.z = 0;

		m_col = D3DCOLOR_ARGB(255, 255, 255, 255);

	}

	virtual ~CSprite()
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

	std::string getName()const
	{

		return m_strName;

	}

private:
	int m_iWidth, m_iHeight;

	std::string m_strName;
	std::string m_strFileName;

	LPDIRECT3DTEXTURE9 m_lpTexture;
	LPD3DXSPRITE m_lpSprite;

	D3DXVECTOR3 m_vec3Position;
	D3DCOLOR m_col;

};

