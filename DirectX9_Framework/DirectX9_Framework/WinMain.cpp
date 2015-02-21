

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 2일 금요일  오전 5:00:51. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/

#include "GameInfo_Loader.h"
#include "SystemClass.h"
#include "D3D_SpriteManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Window::shrdWININFO WIN_INFO(new Window::stWinInfo);
	Resources::VecSpriteInfo SPRITES_INFO;

    try{

        CGameInfo_Loader::getInstancePtr()->saveTimeToXMLFile();

        CGameInfo_Loader::getInstancePtr()->loadWindowAppName(WIN_INFO->wcsAppName);
        //CGameInfo_Loader::getInstancePtr()->loadWindowSize("window_4-to-3", WIN_INFO);
		CGameInfo_Loader::getInstancePtr()->loadWindowSize("FULL SCREEN", WIN_INFO);

		CGameInfo_Loader::getInstancePtr()->loadSpriteInfo(WIN_INFO, SPRITES_INFO);
		CD3D_SpriteManager::getInstancePtr()->loadSpriteInfoFromVector(SPRITES_INFO);		

        CSystemClass::getInstancePtr()->initialize(WIN_INFO);
        CSystemClass::getInstancePtr()->messageLoop();
        
    }
    catch (std::runtime_error &errMessage){

#ifdef _DEBUG
        Debug::consoleMessage(errMessage.what());
#else
        wchar_t buffer[128];
        mbstowcs(buffer, errMessage.what(), strlen(errMessage.what())+1);
        MessageBox(nullptr, buffer, L"Error Occur !!!", MB_ICONWARNING);
#endif

		CSystemClass::getInstancePtr()->deinitialize();
    }

    return 0;
}