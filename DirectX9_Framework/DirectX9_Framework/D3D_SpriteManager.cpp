


/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
// @author    정성화
// @e-mail    JackRyan0903@gmail.com
// @Copyright 2015년 2월 19일 목요일  오전 5:12:26. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/

#include "D3D_SpriteManager.h"


void CD3D_SpriteManager::loadSpriteInfoFromVector(Resources::VecSpriteInfo vecSpriteInfo)
{

	for (auto iter = vecSpriteInfo.begin(); iter != vecSpriteInfo.end(); ++iter){
	
		if ("UI" == (*iter)->getType()){
						
			m_vSprites.push_back(new CSprite_UI((*iter)->getSpriteName(), (*iter)->getFileName(), (*iter)->getPosX(), (*iter)->getPosY(), (*iter)->getWidth(), (*iter)->getHeigth()));
			
		}

	}

}

void CD3D_SpriteManager::initialize(LPDIRECT3DDEVICE9 lpDevice)
{

	for (auto iter = m_vSprites.begin(); iter != m_vSprites.end(); ++iter){
	
		(*iter)->initialize(lpDevice);

	}

}


void CD3D_SpriteManager::render()
{

	for (auto iter = m_vSprites.begin(); iter != m_vSprites.end(); ++iter){

		(*iter)->rener();

	}

}


void CD3D_SpriteManager::deinitialize()
{

	for (auto iter = m_vSprites.begin(); iter != m_vSprites.end(); ++iter){

		(*iter)->deinitialize();

	}

}