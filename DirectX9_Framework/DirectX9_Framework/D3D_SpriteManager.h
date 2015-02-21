

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 19일 목요일  오전 3:55:42. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once
#include "stdafx.h"
#include "Sprite_UI.h"


class CD3D_SpriteManager :
	public DesignPattern::CSingleton < CD3D_SpriteManager >
{
public:
	void loadSpriteInfoFromVector(Resources::VecSpriteInfo vecSpriteInfo);
	void initialize(LPDIRECT3DDEVICE9 lpDevice);
	void render();
	void deinitialize();

public:
	CD3D_SpriteManager()
	{
	
	}
	~CD3D_SpriteManager()
	{

		m_vSprites.clear();

	}

private:
	//================================================================================//
	//  @복사 생성자
	//  @설명
	//		객체 복사 방지 private
	//		객체 복사 시 묵시적 형변환을 막기위해 explicit 키워드 사용
	//================================================================================//
	explicit CD3D_SpriteManager(const CD3D_SpriteManager& copy){}

	//================================================================================//
	//  @연산자 오버로딩=
	//  @설명
	//		객체 복사 방지 private
	//================================================================================//
	CD3D_SpriteManager& operator=(const CD3D_SpriteManager& copy){}

private:
	std::vector<CSprite*> m_vSprites;

};

