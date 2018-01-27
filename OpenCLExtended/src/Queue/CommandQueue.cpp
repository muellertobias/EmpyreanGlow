#include "CommandQueue.h"

namespace OpenCLExt
{
	namespace Queue
	{
		CommandQueue::CommandQueue(std::shared_ptr<Context> context)
		{
			cl::Context nativeContext = *context->getNative().get();
			_Queue = std::shared_ptr<cl::CommandQueue>(new cl::CommandQueue(nativeContext, context->getDevice()));
		}

		CommandQueue::~CommandQueue()
		{
		}

		void CommandQueue::execute(std::vector<cl::Memory> externData, std::shared_ptr<OpenCLExt::Wrapper::Kernel> kernel, size_t width, size_t heigth)
		{
			cl::Event event;

			cl_int res = _Queue->enqueueAcquireGLObjects(&externData, NULL, &event);
			event.wait();
			if (res != CL_SUCCESS) 
			{
				throw new std::exception("Failed to acquire extern objects");
			}

			cl::NDRange local(16, 16);
			cl::NDRange global(local[0] * divideUp(width, local[0]), local[1] * divideUp(heigth, local[1]));

			_Queue->enqueueNDRangeKernel(*kernel->getNative(), cl::NullRange, global, local);

			// release opengl object
			res = _Queue->enqueueReleaseGLObjects(&externData);
			event.wait();
			if (res != CL_SUCCESS) 
			{
				throw new std::exception("Failed to release extern objects");
			}

			_Queue->finish();
		}

		size_t CommandQueue::divideUp(size_t a, size_t b)
		{
			return (a + b - 1) / b;
		}
	}
}
