

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    정성화
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015년 1월 11일 일요일  오전 3:54:00. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @포함
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include "stdafx.h"
#include "TinyXML\tinyxml.h"


class CGameInfo_Loader : public DesignPattern::CSingleton<CGameInfo_Loader>
{
public:
    //================================================================================//
    //  @멤버함수
    //  @접근지정 : public
    //  @설명 : 현재 로컬 시간(윈도우 시계 기준)을 PATH_XML::GAME_INFO 경로의 XML파일에 엘레먼트로 저장.
    //			Debug 모드 시 디버깅 타임을 갱신.
    //			Release 모드 시 릴리즈 타임을 갱신.
    //================================================================================//
    void saveTimeToXMLFile(void);

    //================================================================================//
    //  @멤버함수
    //  @설명 : XML로 부터 윈도우 어플리케이션의 이름을 받아옴(게임 이름)   
    //================================================================================//
    void loadWindowAppName(wchar_t *wcsAppName);

    //================================================================================//
    //  @멤버함수
    //  @설명 : 윈도우 타입을 받아서 윈도우 사이즈를 XML로 부터 불러옴
    //  @타입
	//		1. FULL SCREEN : 풀스크린 모드
    //      2. window_4-to-3 : 800 x 600
    //================================================================================//
    void loadWindowSize(const std::string &windowType, Window::stWinInfo *winInfo);

    /*void test(void)
    {
    TiXmlDocument doc;
    doc.LoadFile(PATH_XML::GAME_INFO.c_str());

    TiXmlElement *ele = new TiXmlElement("Windows");
    doc.RootElement()->LinkEndChild(ele);

    TiXmlElement *subEle = new TiXmlElement("window_4-to-3");
    subEle->SetAttribute("screen_size_X", 800);
    subEle->SetAttribute("screen_size_Y", 600);

    ele->LinkEndChild(subEle);

    doc.SaveFile(PATH_XML::GAME_INFO.c_str());
    }*/
    
public:
    CGameInfo_Loader()  {}
    ~CGameInfo_Loader() {}

private:
    //================================================================================//
    //  @멤버함수
    //  @접근지정 : private
    //  @설명 : Doc을 열어서 포인터 객체로 저장 후 반환
    //	@예외
    //      1. XML File Open Fail : XML파일이 경로에 없을 시 발생.    
    //================================================================================//
    TiXmlDocument* _openDocument(void);
    
    //================================================================================//
    //  @멤버함수
    //  @접근지정 : private
    //  @설명 : Doc 객체 포인터를 파라미터로 받아 저장 후 성공 여부를 bool 타입으로 반환.      
    //================================================================================//
    bool _closeDocument(TiXmlDocument* cpTinyDoc);
    

    //================================================================================//
    //  @멤버함수
    //  @접근지정 : private
    //  @설명 : 파라미터로 전달 받은 SYSTEMTIME 값을 PATH_XML::GAME_INFO 경로의 XML파일에
    //			LatestDebugingTime 엘레먼트를 찾아 저장.
    //	@예외    
    //		1. XML File Get Damaged : XML파일내에 LatestDebugingTime라는 엘레먼트가 없을 시 발생.
    //================================================================================//
    void _saveLatestDebugingTime(const SYSTEMTIME &systemTime);


    //================================================================================//
    //  @멤버함수
    //  @접근지정 : private
    //  @설명 : 파라미터로 전달 받은 SYSTEMTIME 값을 PATH_XML::GAME_INFO 경로의 XML파일에
    //			LatestReleasingTime 엘레먼트를 찾아 저장.
    //	@예외   
    //		1. XML File Get Damaged : XML파일내에 LatestReleasingTime라는 엘레먼트가 없을 시 발생.
    //================================================================================//
    void _saveLatestReleasingTime(const SYSTEMTIME &systemTime);
};
