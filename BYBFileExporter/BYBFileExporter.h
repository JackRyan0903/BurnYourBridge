#pragma once

//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
//SIMPLE TYPE

#include <impexp.h>

//--------------------------------------------------------------------------------
/* 헤더 파일 추가 부분*/
//#include <max.h>
//#include <stdmat.h>
//#include <modstack.h>
//#include <CS\BIPEXP.H>
//#include <CS\Phyexp.h>
//#include <iskin.h>
//
//#include <vector>
//#include <map>
//#include <d3dx9.h>

#include "Geometry.h"

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
/* Physique 및 Skin 관련 필요 정의 부분 */

//3DS MAX Physique 관련 
#define PHYSQ_CLASSID Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B)

//3DS MAX Skin 관련, iskin.h에 이미 정의되어 있다.
//9815843,87654는 iskin.h에 정의된 Class_ID 값
#ifndef SKIN_CLASSID
#define SKIN_CLASSID Class_ID(9815843,87654)
#endif
//--------------------------------------------------------------------------------


extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;
