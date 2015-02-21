

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 19일 목요일  오전 3:06:48. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once
#include "Sprite.h"
class CSprite_UI :
	public CSprite
{
public:
	void update();

public:
	CSprite_UI(const std::string &strSpriteName, const std::string &strFileName, const float &fPosX, const float &fPosY, const int &iWidth, const int &iHeight)
		: CSprite(strSpriteName, strFileName, fPosX, fPosY, iWidth, iHeight)
	{
	
	}
	~CSprite_UI()
	{
	
	}
};

