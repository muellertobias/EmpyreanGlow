#include "KernelFactory.h"
#include <fstream>
namespace OpenCLExt
{
	namespace Kernel 
	{
		std::shared_ptr<Wrapper::Kernel> KernelFactory::create(KernelConfig config, OpenCLExt::Wrapper::Context context)
		{
			cl_int err = 0;

			std::string sourceCode = readFile(config.getFilename());
			cl::Program* program = build(sourceCode, *context.getNative(), context.getDevice());

			cl::Kernel* clKernel = new cl::Kernel(*program, config.getEntryPoint().c_str(), &err);
			if (err != CL_SUCCESS)
				throw new std::exception("error");

			std::shared_ptr<Wrapper::Kernel> managedKernel(new Wrapper::Kernel(clKernel));

			/*auto arguments = config.getArguments();

			for (size_t i = 0; i < arguments.size(); i++)
			{
				managedKernel.setArgument(i, arguments[i]);
			}*/

			return managedKernel;
		}

		std::string KernelFactory::readFile(std::string filename)
		{
			std::ifstream sourceFile(filename);
			std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

			return sourceCode;
		}

		cl::Program* KernelFactory::build(std::string sourceCode, cl::Context context, cl::Device device)
		{
			cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
			cl::Program* program = new cl::Program(context, source);
			program->build(std::vector<cl::Device>(1, device), "-I Assets"); // FIX Pfadangabe

			return program;
		}

	}
}