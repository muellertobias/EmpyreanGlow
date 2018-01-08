#include "Kernel.h"
namespace OpenCLExt
{
	namespace Kernel
	{
		Kernel::Kernel(cl::Kernel kernel)
		{
			this->_Kernel = kernel;
		}

		Kernel::~Kernel()
		{
		}

		void Kernel::setArgument(size_t index, Argument argument)
		{
			_Kernel.setArg(index, argument.size, argument.pointer);
		}
		void Kernel::setArgument(size_t index, size_t argSize, void* argValue)
		{
			_Kernel.setArg(index, argSize, argValue);
		}

		template<typename TType>
		void Kernel::setArgument(size_t index, TType argument)
		{
			_Kernel.setArg(index, argument);
		}
	}
}