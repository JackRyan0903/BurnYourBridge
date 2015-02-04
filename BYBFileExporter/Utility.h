#pragma once

namespace CSH
{
	namespace Util
	{
		template <typename T>
		void SafeDelete(T& param)
		{
			if(param)
			{
				delete param;
				param=nullptr;
			}
		}


		template <typename T>
		void SafeDeleteArray(T& param)
		{
			if(param)
			{
				delete []param;
				param=nullptr;
			}
		}
	}
}