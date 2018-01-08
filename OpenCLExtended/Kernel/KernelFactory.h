#pragma once
#include <CL\cl.hpp>
#include <string>
#include "KernelConfig.h"

class KernelFactory
{
public:
	KernelFactory() {}
	~KernelFactory() {}

	cl::Kernel create(KernelConfig config, cl::Context context, cl::Device device);

private:
	std::string readFile(std::string filename);
	cl::Program build(std::string sourceCode, cl::Context context, cl::Device device);
};

