#pragma once

#include <iostream>

namespace CSH
{
	namespace Model3D
	{
		class HeadInfo
		{
		public:
			enum {START_FRAME, END_FRAME, FRAME_RATE, TICK_FRAME};

		private:
			int m_frameInfo[4];
			int m_numberOfGeometry;

		public:
			HeadInfo()
			{
				memset(m_frameInfo, 0, sizeof(m_frameInfo));
				m_numberOfGeometry=0;
			}

		public:
			int GetFrameInfo(int informationIndex)
			{
				return m_frameInfo[informationIndex];
			}

			void SetFrameInfo(int informationIndex, int value)
			{
				m_frameInfo[informationIndex]=value;
			}

			int GetNumberOfGeometry(void)
			{
				return m_numberOfGeometry;
			}

			void SetNumberOfGeometry(int value)
			{
				m_numberOfGeometry=value;
			}
		};
	}
}