#include "ContextFactory.h"

namespace OpenCLExt
{
	namespace Context
	{
		ContextFactory::ContextFactory(size_t platformID)
		{
			std::vector<cl::Platform> platforms;
			cl_int err = cl::Platform::get(&platforms);
			if (err == CL_SUCCESS)
				throw new std::exception("platforms could not found");

			_Platform = platforms[platformID];
		}


		ContextFactory::~ContextFactory()
		{
		}

		std::shared_ptr<Wrapper::Context> ContextFactory::create(size_t deviceID, intptr_t glContext, intptr_t windowContext)
		{
			cl_context_properties clContextProperties[] =
			{
				CL_GL_CONTEXT_KHR, (cl_context_properties)glContext,
				CL_WGL_HDC_KHR, (cl_context_properties)windowContext,
				CL_CONTEXT_PLATFORM, (cl_context_properties)_Platform(),
				0
			};

			std::vector<cl::Device> devices;
			_Platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
			cl::Device unmanagedDevice = devices[deviceID];

			std::shared_ptr<cl::Context> context = std::shared_ptr<cl::Context>(new cl::Context(unmanagedDevice, clContextProperties));

			return std::shared_ptr<Wrapper::Context>(new Wrapper::Context(context, unmanagedDevice));
		}
	}
}
