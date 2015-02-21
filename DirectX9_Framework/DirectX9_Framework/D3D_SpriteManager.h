

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    ����ȭ
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015�� 2�� 19�� �����  ���� 3:55:42. Jack Ryan all rights reserved.
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
	//  @���� ������
	//  @����
	//		��ü ���� ���� private
	//		��ü ���� �� ������ ����ȯ�� �������� explicit Ű���� ���
	//================================================================================//
	explicit CD3D_SpriteManager(const CD3D_SpriteManager& copy){}

	//================================================================================//
	//  @������ �����ε�=
	//  @����
	//		��ü ���� ���� private
	//================================================================================//
	CD3D_SpriteManager& operator=(const CD3D_SpriteManager& copy){}

private:
	std::vector<CSprite*> m_vSprites;

};

