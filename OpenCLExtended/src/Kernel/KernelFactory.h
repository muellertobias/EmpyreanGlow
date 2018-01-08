#pragma once
#include <CL\cl.hpp>
#include <string>
#include "KernelConfig.h"
#include "Kernel.h"
namespace OpenCLExt
{
	namespace Kernel {

		class KernelFactory
		{
		public:
			KernelFactory() {}
			~KernelFactory() {}

			Kernel create(KernelConfig config, cl::Context context, cl::Device device);

		private:
			std::string readFile(std::string filename);
			cl::Program build(std::string sourceCode, cl::Context context, cl::Device device);
		};

	}
}