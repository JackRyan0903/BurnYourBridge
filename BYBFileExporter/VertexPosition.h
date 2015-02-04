#pragma once


namespace CSH
{
	namespace Model3D
	{
		class VertexPosition
		{
		public:
			enum {X, Y, Z};

		private:
			float m_position[3];

		public:
			VertexPosition()
			{
				m_position[X]=0.0f;
				m_position[Y]=1.0f;
				m_position[Z]=2.0f;
			}

			VertexPosition(float x, float y, float z)
			{
				m_position[X]=x;
				m_position[Y]=y;
				m_position[Z]=z;
			}

		public:
			float GetPosition(int position)
			{
				return m_position[position];
			}

			void SetPosition(int position, float value)
			{
				m_position[position]=value;
			}
		};
	}
}