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
			ContextFactory(size_t platformID);
			~ContextFactory();

			Context create(size_t deviceID, intptr_t glContext, intptr_t windowContext);

		private:
			cl::Platform _Platform;
		};
	}
}
