#include "Context.h"
namespace OpenCLExt
{
	namespace Context
	{
		Context::Context(std::shared_ptr<cl::Context> context)
		{
			_Context = context;
			_Properties = _Context->getInfo<CL_CONTEXT_PROPERTIES>();
			_Devices = _Context->getInfo<CL_CONTEXT_DEVICES>();
		}

		Context::~Context()
		{
		}
	}
}