

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 11일 일요일  오전 4:30:35. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "GameInfo_Loader.h"


void CGameInfo_Loader::saveTimeToXMLFile(void)
{
    // 시스템 시간값을 가져올 변수 선언
    SYSTEMTIME systemTime;

    // 시스템 시간값 구조체 초기화
    ZeroMemory(&systemTime, sizeof(SYSTEMTIME));

    // 로컬 시간값 가져옴
    GetLocalTime(&systemTime);

    // 디버그시 디버그 타임 엘레먼트를 갱신
    // 릴리즈시 릴리즈 타임 엘레먼트를 갱신
#ifdef _DEBUG
    _saveLatestDebugingTime(systemTime);
#else
    _saveLatestReleasingTime(systemTime);
#endif

}

void CGameInfo_Loader::loadWindowAppName(wchar_t *wcsAppName)
{
    // XML 핸들 객체
    TiXmlDocument *cpTinyDoc = nullptr;

    //  windowsize 정보 엘레먼트
	TiXmlElement *eleWindowName = nullptr;

    // 에러코드를 저장할 객체
    std::stringstream errCode;

    cpTinyDoc = _openDocument();

    eleWindowName = cpTinyDoc->RootElement()->FirstChildElement("Name");

    // 엘레먼트를 찾지 못한다면 XML파일이 손상 되거나 잘못되었다는 말이므로 런타임 에러 throw
    if (nullptr == eleWindowName){

        errCode << "Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<Name>)";
        throw std::runtime_error(errCode.str());

    }

	// const char* -> wchar_t*
    mbstowcs(wcsAppName, eleWindowName->GetText(), strlen(eleWindowName->GetText()) + 1);

    if (_closeDocument(cpTinyDoc)){
#ifdef _DEBUG
        Debug::consoleMessage("Window app Name loaded completely.");
#endif
    }
}

void CGameInfo_Loader::loadWindowSize(const std::string &windowType, Window::stWinInfo *winInfo)
{
    // XML 핸들 객체
    TiXmlDocument *cpTinyDoc = nullptr;
    
    //  windowsize 정보 엘레먼트
    TiXmlElement *eleWindowSize = nullptr;

    // 에러코드를 저장할 객체
    std::stringstream errCode;

	if (0 == windowType.compare("FULL SCREEN")){
		
		winInfo->bIsFullScreen = true;
		winInfo->iScreenSize_X = 0;
		winInfo->iScreenSize_Y = 0;

	}
	else{
		winInfo->bIsFullScreen = false;

		cpTinyDoc = _openDocument();

		eleWindowSize = cpTinyDoc->RootElement()->FirstChildElement("Windows")->FirstChildElement(windowType.c_str());

		// 엘레먼트를 찾지 못한다면 XML파일이 손상 되거나 잘못되었다는 말이므로 런타임 에러 throw
		if (nullptr == eleWindowSize){

			errCode << "Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<" << windowType << ">)";
			throw std::runtime_error(errCode.str());

		}


		winInfo->iScreenSize_X = eleWindowSize->FirstAttribute()->IntValue();
		winInfo->iScreenSize_Y = eleWindowSize->FirstAttribute()->Next()->IntValue();

		if (_closeDocument(cpTinyDoc)){
#ifdef _DEBUG
			Debug::consoleMessage("Window size loaded completely.");
#endif
		}
	}
    
}

TiXmlDocument* CGameInfo_Loader::_openDocument(void)
{
    // XML 핸들 객체
    TiXmlDocument *cpTinyDoc = new TiXmlDocument;

    cpTinyDoc->LoadFile(PATH_XML::GAME_INFO.c_str());
    // 파일 오픈 실패시 런타임 에러 throw
    if (TiXmlElement::TIXML_ERROR_OPENING_FILE == cpTinyDoc->ErrorId()){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Open Fail)");

    }

    return cpTinyDoc;
}

bool CGameInfo_Loader::_closeDocument(TiXmlDocument* cpTinyDoc)
{
    // 저장하는 성공 여부 판단 플래그
    bool bIsSaveSuccess = false;

    if (nullptr != cpTinyDoc){

        if (cpTinyDoc->SaveFile()){

            bIsSaveSuccess = true;

        }

        delete cpTinyDoc;
        cpTinyDoc = nullptr;
    }

    return bIsSaveSuccess;
}


void CGameInfo_Loader::_saveLatestDebugingTime(const SYSTEMTIME &systemTime)
{
    // 시스템 타임을 스트링형으로 저장할 스트림 객체 선언
    std::stringstream strTime;

    // 시스템 타임을 스트링형으로 저장
    strTime << systemTime.wYear << '-' << systemTime.wMonth << '-' << systemTime.wDay << ' '
        << systemTime.wHour << ':' << systemTime.wMinute << ':' << systemTime.wSecond;

    // XML파일을 다루기 위해 document 객체 선언
    TiXmlDocument *cpTinyDoc = _openDocument();
    

    // 루트 엘레먼트에서 "LatestDebugingTime" 이라는 엘레먼트를 찾음
    TiXmlElement *cpEle = cpTinyDoc->RootElement()->FirstChildElement("LatestDebugingTime");


    // 엘레먼트를 찾지 못한다면 XML파일이 손상 되거나 잘못되었다는 말이므로 런타임 에러 throw
    if (nullptr == cpEle){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<LatestDebugingTime>)");

    }

    // 원래 있던 디버깅 타임 정보를 지움
    cpEle->Clear();

    // 디버깅 타임 정보를 씀
    cpEle->LinkEndChild(new TiXmlText(strTime.str().c_str()));

    // Document 저장
    if (_closeDocument(cpTinyDoc)){

#ifdef _DEBUG
        Debug::consoleMessage("Opening XML file and Updating Debug time is successfully completed.");
#endif
    }
}


void CGameInfo_Loader::_saveLatestReleasingTime(const SYSTEMTIME &systemTime)
{
    // 시스템 타임을 스트링형으로 저장할 스트림 객체 선언
    std::stringstream strTime;

    // 시스템 타임을 스트링형으로 저장
    strTime << systemTime.wYear << '-' << systemTime.wMonth << '-' << systemTime.wDay << ' '
        << systemTime.wHour << ':' << systemTime.wMinute << ':' << systemTime.wSecond;

    // XML파일을 다루기 위해 document 객체 선언
    TiXmlDocument *cpTinyDoc = _openDocument();    

    // 루트 엘레먼트에서 "LatestReleasingTime" 이라는 엘레먼트를 찾음
    TiXmlElement *cpEle = cpTinyDoc->RootElement()->FirstChildElement("LatestReleasingTime");


    // 엘레먼트를 찾지 못한다면 XML파일이 손상 되거나 잘못되었다는 말이므로 런타임 에러 throw
    if (nullptr == cpEle){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<LatestReleasingTime>)");

    }

    // 원래 있던 링리징 타임 정보를 지움
    cpEle->Clear();

    // 릴리징 타임 정보를 씀
    cpEle->LinkEndChild(new TiXmlText(strTime.str().c_str()));

    // Document 저장
    _closeDocument(cpTinyDoc);
}


