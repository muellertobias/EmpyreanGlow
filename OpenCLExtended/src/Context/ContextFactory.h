#pragma once
#include <CL\cl.hpp>
#include "../Wrapper/Context.h"

namespace OpenCLExt
{
	namespace Context
	{
		class ContextFactory
		{
		public:
			ContextFactory(size_t platformID);
			~ContextFactory();

			std::shared_ptr<Wrapper::Context> create(size_t deviceID, intptr_t glContext, intptr_t windowContext);

		private:
			cl::Platform _Platform;
		};
	}
}
