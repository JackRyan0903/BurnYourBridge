

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/* @author    ����ȭ
/* @e-mail    JackRyan0903@gmail.com
/* @Copyright 2015�� 1�� 9�� �ݿ���  ���� 9:59:00. Jack Ryan all rights reserved.
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/


#pragma once
#pragma warning(disable:4996)

/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
/*  @����
/*=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=*/
#include <string>   // std::string
#include <vector>

//================================================================================//
//  @���ӽ����̽�
//  @���� : XML ��θ� �����ϰ� �ִ� ���ӽ����̽�
//  @���
//      1. GAME_INFO(Resources/XML/GameInfo.xml)
//================================================================================//
namespace PATH_XML{

	const static std::string GAME_INFO = "Resources/XML/GameInfo.xml";

};


//================================================================================//
//  @���ӽ����̽�
//  @���� : ������ ���� �������� �����ϴ� ����ü���� ����
//================================================================================//
namespace Window{

    typedef struct _stWinInfo{

        wchar_t wcsAppName[64];
        bool bIsFullScreen;
        int iScreenSize_X;
        int iScreenSize_Y;

    }stWinInfo;

	typedef std::shared_ptr<Window::stWinInfo> shrdWININFO;

};




namespace Resources{	

	class CSpriteInfo{

	public:
		CSpriteInfo(const std::string &strType, const std::string &strSpriteName, const std::string &strFileName, const float &fPosX, const float &fPosY, const int &iWidth, const int &iHeight)
			: m_strType(strType), m_strSpriteName(strSpriteName), m_strFileName(strFileName), m_fPosX(fPosX), m_fPosY(fPosY), m_iWidth(iWidth), m_iHeight(iHeight)
		{

		}

		~CSpriteInfo(){}

		std::string getType() const{ return m_strType; }

		std::string getSpriteName() const{	return m_strSpriteName;	}

		std::string getFileName() const{	return m_strFileName;	}

		float getPosX() const{	return m_fPosX;	}

		float getPosY() const{	return m_fPosY;	}

		int getWidth() const{	return m_iWidth;	}

		int getHeigth() const{	return m_iHeight;	}

	private:
		std::string m_strType;
		std::string m_strSpriteName;
		std::string m_strFileName;
		float m_fPosX;
		float m_fPosY;
		int m_iWidth;
		int m_iHeight;

	};

	typedef std::vector<CSpriteInfo*> VecSpriteInfo;

};

//================================================================================//
//  @���ӽ����̽�
//  @���� : ��ü�� �ǻ����� �޽��� ����ü���� ����
//================================================================================//
namespace Message{



};
