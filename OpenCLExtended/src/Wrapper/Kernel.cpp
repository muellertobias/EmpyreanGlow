#include "Kernel.h"

namespace OpenCLExt
{
	namespace Wrapper
	{
		Kernel::Kernel(cl::Kernel* kernel)
		{
			this->_Kernel = kernel;
		}

		Kernel::~Kernel()
		{
			delete(_Kernel);
		}

		void Kernel::setArgument(size_t index, Argument argument)
		{
			_Kernel->setArg(index, argument.size, argument.pointer);
		}

		void Kernel::setArgument(size_t index, size_t argSize, void* argValue)
		{
			_Kernel->setArg(index, argSize, argValue);
		}
	}
}