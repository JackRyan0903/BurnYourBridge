#pragma once

#include <tchar.h>
#include <max.h>
#include <stdmat.h>
#include <modstack.h>
#include <CS\BIPEXP.H>
#include <CS\Phyexp.h>
#include <iskin.h>
#include <vector>
#include <map>
#include <d3dx9.h>

#include "Utility.h"
#include "VertexPosition.h"
#include "VertexIndex.h"
#include "BoneIndex.h"
#include "FrameOffset.h"
#include "HeadInfo.h"
#include "GeometryType.h"


using namespace CSH::Util;

namespace CSH
{
	namespace Model3D
	{
		class Geometry
		{
		public:
			enum {NODE_NAME_LENGTH=32, NOT_EXIST=-1};
			enum {NODE_TYPE, PARENT_INDEX, N_INDEX, N_POSITION, N_BONE_DEPENDENT_VERTEX, N_ANIMATION};
			//enum {NODE_NAME, P_NODE, P_INDEX, P_POSITION, P_BONE_SOURCE, P_ANIMATION};

		public:
			TCHAR				m_nodeName[NODE_NAME_LENGTH];//맥스 노드 이름
			int					m_intInfo[6];//int 타입을 갖는 정보들 위 열거형 중 2번째(NODE_TYPE ~)

			INode*				m_pNode;
			VertexIndex*		m_indexList;
			VertexPosition*		m_positionList;
			BoneIndex*			m_boneSource;
			D3DXMATRIX*			m_animationMatrix;

		public:
			Geometry()
			{
				memset(m_nodeName, 0, sizeof(m_nodeName));
				memset(m_intInfo, 0, sizeof(m_intInfo));

				m_intInfo[PARENT_INDEX]=NOT_EXIST;

				m_pNode=nullptr;
				m_indexList=nullptr;
				m_positionList=nullptr;
				m_boneSource=nullptr;
				m_animationMatrix=nullptr;
			}

			~Geometry()
			{
				SafeDeleteArray(m_indexList);
				SafeDeleteArray(m_positionList);
				SafeDeleteArray(m_boneSource);
				SafeDeleteArray(m_animationMatrix);
			}

		public:
			int GetIntInfo(int index)
			{
				return m_intInfo[index];
			}

			int* GetIntInfoPointer(int index)
			{
				return &m_intInfo[index];
			}

			void SetIntInfo(int index, int value)
			{
				m_intInfo[index]=value;
			}

			//template <typename T>
			//T& GetPointer(int index)
			//{
			//	switch(index)
			//	{
			//	case NODE_NAME:
			//		return m_nodeName;

			//	case P_NODE:
			//		return m_pNode;

			//	case P_INDEX:
			//		return m_indexList;

			//	case P_POSITION:
			//		return m_positionList;

			//	case P_BONE_SOURCE:
			//		return m_boneSource;

			//	case P_ANIMATION:
			//		return m_animationMatrix;
			//	}
			//}

			//template <typename T>
			//void SetPointer(int index, T* ptr)
			//{
			//	switch(index)
			//	{
			//	case NODE_NAME:
			//		_stprintf(m_nodeName, ptr);
			//		//m_nodeName=ptr;

			//	case P_NODE:
			//		m_pNode=ptr;

			//	case P_INDEX:
			//		m_indexList=ptr;

			//	case P_POSITION:
			//		m_positionList=ptr;

			//	case P_BONE_SOURCE:
			//		m_boneSource=ptr;

			//	case P_ANIMATION:
			//		m_animationMatrix=ptr;
			//	}
			//}

		};

	}
}