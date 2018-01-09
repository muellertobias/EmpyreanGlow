#include "Context.h"
namespace OpenCLExt
{
	namespace Context
	{
		Context::Context(std::shared_ptr<cl::Context> context, cl::Device device)
		{
			_Context = context;
			_Properties = _Context->getInfo<CL_CONTEXT_PROPERTIES>();
			_Device = device;
		}

		Context::~Context()
		{
		}
	}
}