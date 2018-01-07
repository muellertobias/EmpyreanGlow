#pragma once
#include <CL\cl.hpp>
#include <string>

class KernelFactory
{
public:
	KernelFactory() {}
	~KernelFactory() {}

	cl::Kernel create(std::string kernelEntryFunctionName, std::string kernelFilename, cl::Context context, cl::Device device);

private:
	std::string readFile(std::string filename);
	cl::Program build(std::string sourceCode, cl::Context context, cl::Device device);
};

