#include "BYBExporter.h"

using namespace CSH::Util;
using namespace CSH::Model3D;
using CSH::Model3D::BYBExporter;


//--------------------------------------------------------------------------------
/* ������ */

BYBExporter::BYBExporter()
{
	m_doExport=false;

	m_expInterface=nullptr;
	m_interface=nullptr;
	m_suppressPrompt=0;
	m_options=0;
	m_geometry=nullptr;
}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* 3ds max ���� ���� ���� */

void  NodeGather(INode* pNode)
{

}



void  SetParentIndex(Geometry* pGeom)
{

}


void  SetGeometry(Geometry* pGeom)
{

}


void  SetAnimation(Geometry* pGeom)
{

}


int   BoneIDFind(INode* pNode)
{
	return false;
}


void  SetBoneWeight(Geometry* pGeom)
{

}


void  SetPhysiqueWeight(Geometry* pGeom, Modifier* pMod)
{

}


void  SetSkinWeight(Geometry* pGeom, Modifier* pMod)
{

}


void* ModifierFind(INode* pNode, Class_ID classID)
{
	return nullptr;
}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* 3ds max -> directx ��ȯ ���� */

void  MaxMatrixToD3D(D3DXMATRIX* pDest, Matrix3* pSrc, bool identity)
{

}

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
/* ���� ��� ���� */

void  BinaryFileWrite()
{

}


void  TextFileWrite()
{

}


void  FileRename(TCHAR* pOut, TCHAR* pIn, TCHAR* fileName, TCHAR* ext)
{

}


//--------------------------------------------------------------------------------