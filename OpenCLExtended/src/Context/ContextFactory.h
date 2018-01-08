#pragma once
#include <CL\cl.hpp>
#include "Context.h"

namespace OpenCLExt
{
	namespace Context
	{
		class ContextFactory
		{
		public:
			ContextFactory();
			~ContextFactory();

			Context create(std::vector<cl_context_properties> clContextProperties);

		private:
			std::vector<cl::Platform> _Platforms;
		};
	}
}
