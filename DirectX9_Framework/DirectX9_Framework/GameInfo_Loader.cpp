

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    ����ȭ
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015�� 1�� 11�� �Ͽ���  ���� 4:30:35. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#include "GameInfo_Loader.h"


void CGameInfo_Loader::saveTimeToXMLFile(void)
{
    // �ý��� �ð����� ������ ���� ����
    SYSTEMTIME systemTime;

    // �ý��� �ð��� ����ü �ʱ�ȭ
    ZeroMemory(&systemTime, sizeof(SYSTEMTIME));

    // ���� �ð��� ������
    GetLocalTime(&systemTime);

    // ����׽� ����� Ÿ�� ������Ʈ�� ����
    // ������� ������ Ÿ�� ������Ʈ�� ����
#ifdef _DEBUG
    _saveLatestDebugingTime(systemTime);
#else
    _saveLatestReleasingTime(systemTime);
#endif

}

void CGameInfo_Loader::loadWindowAppName(wchar_t *wcsAppName)
{
    // XML �ڵ� ��ü
    TiXmlDocument *cpTinyDoc = nullptr;

    //  windowsize ���� ������Ʈ
	TiXmlElement *eleWindowName = nullptr;

    // �����ڵ带 ������ ��ü
    std::stringstream errCode;

    cpTinyDoc = _openDocument();

    eleWindowName = cpTinyDoc->RootElement()->FirstChildElement("Name");

    // ������Ʈ�� ã�� ���Ѵٸ� XML������ �ջ� �ǰų� �߸��Ǿ��ٴ� ���̹Ƿ� ��Ÿ�� ���� throw
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

void CGameInfo_Loader::loadWindowSize(const std::string &windowType, Window::shrdWININFO winInfo)
{
    // XML �ڵ� ��ü
    TiXmlDocument *cpTinyDoc = nullptr;
    
    //  windowsize ���� ������Ʈ
    TiXmlElement *eleWindowSize = nullptr;

    // �����ڵ带 ������ ��ü
    std::stringstream errCode;

	if (0 == windowType.compare("FULL SCREEN")){
		
		winInfo->bIsFullScreen = true;
		winInfo->iScreenSize_X = GetSystemMetrics(SM_CXSCREEN);
		winInfo->iScreenSize_Y = GetSystemMetrics(SM_CYSCREEN);

	}
	else{
		winInfo->bIsFullScreen = false;

		cpTinyDoc = _openDocument();

		eleWindowSize = cpTinyDoc->RootElement()->FirstChildElement("Windows")->FirstChildElement(windowType.c_str());

		// ������Ʈ�� ã�� ���Ѵٸ� XML������ �ջ� �ǰų� �߸��Ǿ��ٴ� ���̹Ƿ� ��Ÿ�� ���� throw
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


void CGameInfo_Loader::loadSpriteInfo(const Window::shrdWININFO &winInfo, Resources::VecSpriteInfo &vecSpriteInfo)
{

	std::string strType("");
	std::string strSpriteName("");
	std::string strFileName("");
	std::string strX("");
	std::string strY("");
	
	float fPosX = 0.0f;
	float fPosY = 0.0f;
	int iWidth = 0;
	int iHeight = 0;

	// XML �ڵ� ��ü
	TiXmlDocument *cpTinyDoc = nullptr;

	TiXmlElement *eleSprites = nullptr;
	TiXmlElement *eleSpriteInfo = nullptr;

	TiXmlAttribute *pAttribute = nullptr;

	// �����ڵ带 ������ ��ü
	std::stringstream errCode;

	cpTinyDoc = _openDocument();

	eleSprites = cpTinyDoc->RootElement()->FirstChildElement("Resources")->FirstChildElement("Sprites");

	// ������Ʈ�� ã�� ���Ѵٸ� XML������ �ջ� �ǰų� �߸��Ǿ��ٴ� ���̹Ƿ� ��Ÿ�� ���� throw
	if (nullptr == eleSprites){

		errCode << "Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<Sprites>";
		throw std::runtime_error(errCode.str());

	}

	eleSpriteInfo = eleSprites->FirstChildElement();


	while (eleSpriteInfo){
	
		pAttribute = eleSpriteInfo->FirstAttribute();		
		if (!pAttribute){

			errCode << "Sprite's info is inaccurate, Check " << PATH_XML::GAME_INFO << " File.";
			throw std::runtime_error(errCode.str());

		}

		strType = pAttribute->Value();
		pAttribute = _moveNextAttribute(pAttribute);		

		strSpriteName = pAttribute->Value();
		pAttribute = _moveNextAttribute(pAttribute);

		strFileName = pAttribute->Value();
		pAttribute = _moveNextAttribute(pAttribute);

		strX = pAttribute->Value();
		if ("left" != strX && "mid" != strX && "right" != strX)
		{

			fPosX = (float)pAttribute->DoubleValue();
			pAttribute = _moveNextAttribute(pAttribute);

		}
		else{

			pAttribute = _moveNextAttribute(pAttribute);

		}
		
		strY = pAttribute->Value();
		if ("top" != strY && "mid" != strY && "bottom" != strY)
		{

			fPosY = (float)pAttribute->DoubleValue();
			pAttribute = _moveNextAttribute(pAttribute);

		}			
		else{
		
			pAttribute = _moveNextAttribute(pAttribute);

		}

		iWidth = pAttribute->IntValue();
		pAttribute = _moveNextAttribute(pAttribute);

		iHeight = pAttribute->IntValue();		


		if ("left" == strX){

			fPosX = 0;

		}
		else if ("mid" == strX){

			fPosX = ((winInfo->iScreenSize_X) / 2) - (iWidth / 2);

		}
		else if ("right" == strX){

			fPosX = winInfo->iScreenSize_X - iWidth;
		
		}

		if ("top" == strY){

			fPosY = 0;

		}
		else if ("mid" == strY){

			fPosY = ((winInfo->iScreenSize_Y) / 2) - (iHeight / 2);

		}
		else if ("bottom" == strY){

			fPosY = winInfo->iScreenSize_Y - iHeight;

		}

		vecSpriteInfo.push_back(new Resources::CSpriteInfo(strType, strSpriteName, strFileName, fPosX, fPosY, iWidth, iHeight));

		eleSpriteInfo = eleSpriteInfo->NextSiblingElement();
	}

}


TiXmlDocument* CGameInfo_Loader::_openDocument(void)
{
    // XML �ڵ� ��ü
    TiXmlDocument *cpTinyDoc = new TiXmlDocument;

    cpTinyDoc->LoadFile(PATH_XML::GAME_INFO.c_str());
    // ���� ���� ���н� ��Ÿ�� ���� throw
    if (TiXmlElement::TIXML_ERROR_OPENING_FILE == cpTinyDoc->ErrorId()){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Open Fail)");

    }

    return cpTinyDoc;
}

bool CGameInfo_Loader::_closeDocument(TiXmlDocument* cpTinyDoc)
{
    // �����ϴ� ���� ���� �Ǵ� �÷���
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
    // �ý��� Ÿ���� ��Ʈ�������� ������ ��Ʈ�� ��ü ����
    std::stringstream strTime;

    // �ý��� Ÿ���� ��Ʈ�������� ����
    strTime << systemTime.wYear << '-' << systemTime.wMonth << '-' << systemTime.wDay << ' '
        << systemTime.wHour << ':' << systemTime.wMinute << ':' << systemTime.wSecond;

    // XML������ �ٷ�� ���� document ��ü ����
    TiXmlDocument *cpTinyDoc = _openDocument();
    

    // ��Ʈ ������Ʈ���� "LatestDebugingTime" �̶�� ������Ʈ�� ã��
    TiXmlElement *cpEle = cpTinyDoc->RootElement()->FirstChildElement("LatestDebugingTime");


    // ������Ʈ�� ã�� ���Ѵٸ� XML������ �ջ� �ǰų� �߸��Ǿ��ٴ� ���̹Ƿ� ��Ÿ�� ���� throw
    if (nullptr == cpEle){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<LatestDebugingTime>)");

    }

    // ���� �ִ� ����� Ÿ�� ������ ����
    cpEle->Clear();

    // ����� Ÿ�� ������ ��
    cpEle->LinkEndChild(new TiXmlText(strTime.str().c_str()));

    // Document ����
    if (_closeDocument(cpTinyDoc)){

#ifdef _DEBUG
        Debug::consoleMessage("Opening XML file and Updating Debug time is successfully completed.");
#endif
    }
}


void CGameInfo_Loader::_saveLatestReleasingTime(const SYSTEMTIME &systemTime)
{
    // �ý��� Ÿ���� ��Ʈ�������� ������ ��Ʈ�� ��ü ����
    std::stringstream strTime;

    // �ý��� Ÿ���� ��Ʈ�������� ����
    strTime << systemTime.wYear << '-' << systemTime.wMonth << '-' << systemTime.wDay << ' '
        << systemTime.wHour << ':' << systemTime.wMinute << ':' << systemTime.wSecond;

    // XML������ �ٷ�� ���� document ��ü ����
    TiXmlDocument *cpTinyDoc = _openDocument();    

    // ��Ʈ ������Ʈ���� "LatestReleasingTime" �̶�� ������Ʈ�� ã��
    TiXmlElement *cpEle = cpTinyDoc->RootElement()->FirstChildElement("LatestReleasingTime");


    // ������Ʈ�� ã�� ���Ѵٸ� XML������ �ջ� �ǰų� �߸��Ǿ��ٴ� ���̹Ƿ� ��Ÿ�� ���� throw
    if (nullptr == cpEle){

        throw std::runtime_error("Runtime Error Occur !!!(XML File Get Damaged -> Can't Find Element<LatestReleasingTime>)");

    }

    // ���� �ִ� ����¡ Ÿ�� ������ ����
    cpEle->Clear();

    // ����¡ Ÿ�� ������ ��
    cpEle->LinkEndChild(new TiXmlText(strTime.str().c_str()));

    // Document ����
    _closeDocument(cpTinyDoc);
}


TiXmlAttribute* CGameInfo_Loader::_moveNextAttribute(TiXmlAttribute* pAttribute)
{

	std::stringstream errCode;

	pAttribute = pAttribute->Next();
	if (!pAttribute){

		errCode << "Sprite's info is inaccurate, Check " << PATH_XML::GAME_INFO << " File.";
		throw std::runtime_error(errCode.str());

	}

	return pAttribute;

}