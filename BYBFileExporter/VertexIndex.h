#pragma once

#include <Windows.h>

namespace CSH
{
	namespace Model3D
	{
		class VertexIndex
		{
		public:
			enum {FIRST, SECOND, THIRD};

		private:
			WORD m_index[3];

		public:
			VertexIndex()
			{
				m_index[FIRST]=FIRST;
				m_index[SECOND]=SECOND;
				m_index[THIRD]=THIRD;
			}


			VertexIndex(WORD first, WORD second, WORD third)
			{
				m_index[FIRST]=first;
				m_index[SECOND]=second;
				m_index[THIRD]=third;
			}

		public:
			WORD GetIndex(int index)
			{
				return m_index[index];
			}

			void SetIndex(int index, WORD value)
			{
				m_index[index]=value;
			}
		};
	}
}