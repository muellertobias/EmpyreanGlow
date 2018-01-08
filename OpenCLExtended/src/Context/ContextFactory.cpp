#include "ContextFactory.h"

namespace OpenCLExt
{
	namespace Context
	{
		ContextFactory::ContextFactory()
		{
			cl_int err = cl::Platform::get(&_Platforms);
			if (err == CL_SUCCESS)
				throw new std::exception("plattforms could not found");
		}


		ContextFactory::~ContextFactory()
		{
		}

		Context ContextFactory::create(std::vector<cl_context_properties> clContextProperties)
		{
			return 0;
		}
	}
}
