#pragma once
#include <CL\cl.hpp>
#include <string>
#include "KernelConfig.h"
#include "../Wrapper/Kernel.h"
#include "../Wrapper/Context.h"

namespace OpenCLExt
{
	namespace Kernel 
	{
		class KernelFactory
		{
		public:
			KernelFactory() {}
			~KernelFactory() {}

			Wrapper::Kernel create(KernelConfig config, OpenCLExt::Wrapper::Context context);

		private:
			std::string readFile(std::string filename);
			cl::Program build(std::string sourceCode, cl::Context context, cl::Device device);
		};

	}
}