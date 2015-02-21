

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    ����ȭ
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015�� 1�� 11�� �Ͽ���  ���� 3:54:00. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @����
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include "stdafx.h"
#include "TinyXML\tinyxml.h"


class CGameInfo_Loader : public DesignPattern::CSingleton<CGameInfo_Loader>
{
public:
    //================================================================================//
    //  @����Լ�
    //  @�������� : public
    //  @���� : ���� ���� �ð�(������ �ð� ����)�� PATH_XML::GAME_INFO ����� XML���Ͽ� ������Ʈ�� ����.
    //			Debug ��� �� ����� Ÿ���� ����.
    //			Release ��� �� ������ Ÿ���� ����.
    //================================================================================//
    void saveTimeToXMLFile(void);

    //================================================================================//
    //  @����Լ�
    //  @���� : XML�� ���� ������ ���ø����̼��� �̸��� �޾ƿ�(���� �̸�)   
    //================================================================================//
    void loadWindowAppName(wchar_t *wcsAppName);

    //================================================================================//
    //  @����Լ�
    //  @���� : ������ Ÿ���� �޾Ƽ� ������ ����� XML�� ���� �ҷ���
    //  @Ÿ��
	//		1. FULL SCREEN : Ǯ��ũ�� ���
    //      2. window_4-to-3 : 800 x 600
    //================================================================================//
	void loadWindowSize(const std::string &windowType, Window::shrdWININFO winInfo);

	//================================================================================//
	//  @����Լ�
	//  @���� : ��������Ʈ �������� XML�� ���� �ҷ���	
	//================================================================================//
	void loadSpriteInfo(const Window::shrdWININFO &winInfo, Resources::VecSpriteInfo &vecSpriteInfo);

	/*void test(void)
	{
		TiXmlDocument doc;
		doc.LoadFile(PATH_XML::GAME_INFO.c_str());

		TiXmlElement *ele = new TiXmlElement("Resources");
		doc.RootElement()->LinkEndChild(ele);

		TiXmlElement *subEle = new TiXmlElement("Sprites");
		ele->LinkEndChild(subEle);


		TiXmlElement *subEle2 = new TiXmlElement("testUI");
		subEle2->SetAttribute("spriteName", "test");
		subEle2->SetAttribute("fileName", "test.png");
		subEle2->SetAttribute("posX", 100);
		subEle2->SetAttribute("posY", 100);
		subEle2->SetAttribute("width", 100);
		subEle2->SetAttribute("height", 100);

		subEle->LinkEndChild(subEle2);
		

		doc.SaveFile(PATH_XML::GAME_INFO.c_str());
	}*/
    
public:
    CGameInfo_Loader()  {}
    ~CGameInfo_Loader() {}

private:
    //================================================================================//
    //  @����Լ�
    //  @�������� : private
    //  @���� : Doc�� ��� ������ ��ü�� ���� �� ��ȯ
    //	@����
    //      1. XML File Open Fail : XML������ ��ο� ���� �� �߻�.    
    //================================================================================//
    TiXmlDocument* _openDocument(void);
    
    //================================================================================//
    //  @����Լ�
    //  @�������� : private
    //  @���� : Doc ��ü �����͸� �Ķ���ͷ� �޾� ���� �� ���� ���θ� bool Ÿ������ ��ȯ.      
    //================================================================================//
    bool _closeDocument(TiXmlDocument* cpTinyDoc);
    

    //================================================================================//
    //  @����Լ�
    //  @�������� : private
    //  @���� : �Ķ���ͷ� ���� ���� SYSTEMTIME ���� PATH_XML::GAME_INFO ����� XML���Ͽ�
    //			LatestDebugingTime ������Ʈ�� ã�� ����.
    //	@����    
    //		1. XML File Get Damaged : XML���ϳ��� LatestDebugingTime��� ������Ʈ�� ���� �� �߻�.
    //================================================================================//
    void _saveLatestDebugingTime(const SYSTEMTIME &systemTime);


    //================================================================================//
    //  @����Լ�
    //  @�������� : private
    //  @���� : �Ķ���ͷ� ���� ���� SYSTEMTIME ���� PATH_XML::GAME_INFO ����� XML���Ͽ�
    //			LatestReleasingTime ������Ʈ�� ã�� ����.
    //	@����   
    //		1. XML File Get Damaged : XML���ϳ��� LatestReleasingTime��� ������Ʈ�� ���� �� �߻�.
    //================================================================================//
    void _saveLatestReleasingTime(const SYSTEMTIME &systemTime);


	//================================================================================//
	//  @����Լ�
	//  @�������� : private
	//  @���� : �Ķ���ͷ� ���޹��� attribute�� �����͸� ���� attribute�� ������ ������ �����ϰ� �̰��� ��ȯ.
	//	@����   
	//		1. Sprite's info is inaccurate, Check "File Name" File : XML ���� ���� attribute�� �̸��� ��Ȯ���� ���� �� �߻�.
	//================================================================================//
	TiXmlAttribute* _moveNextAttribute(TiXmlAttribute* pAttribute);

};
