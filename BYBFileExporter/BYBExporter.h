#pragma once

#include "Geometry.h"

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

namespace CSH
{
	namespace Model3D
	{
		class BYBExporter
		{
		public:


		private:
			bool					m_doExport;
			ExpInterface*			m_expInterface;
			Interface*				m_interface;
			bool					m_suppressPrompt;
			DWORD					m_options;
			TCHAR					m_binaryFileName[MAX_PATH];
			TCHAR					m_textFileName[MAX_PATH];
			std::vector<INode*>		m_maxNode;
			HeadInfo				m_head;
			Geometry*				m_geometry;

		public:
			BYBExporter();

		public://3ds max 정보 추출 관련
			void  NodeGather(INode* pNode);
			void  SetBone(Geometry* pGeom);
			void  SetParentIndex(Geometry* pGeom);
			void  SetGeometry(Geometry* pGeom);
			void  SetAnimation(Geometry* pGeom);
			int   BoneIDFind(INode* pNode);
			void  SetBoneWeight(Geometry* pGeom);
			void  SetPhysiqueWeight(Geometry* pGeom, Modifier* pMod);
			void  SetSkinWeight(Geometry* pGeom, Modifier* pMod);
			void* ModifierFind(INode* pNode, Class_ID classID);

		public://3ds max -> directx 변환 관련
			void  MaxMatrixToD3D(D3DXMATRIX* pDest, Matrix3* pSrc, bool identity=true);

		public://파일 출력 관련
			void  BinaryFileWrite();
			void  TextFileWrite();
			void  FileRename(TCHAR* pOut, TCHAR* pIn, TCHAR* fileName, TCHAR* ext);

		};
	}
}