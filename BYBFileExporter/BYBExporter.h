#pragma once

#include "Geometry.h"

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