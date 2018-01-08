#include "KernelFactory.h"
#include <fstream>

Kernel KernelFactory::create(KernelConfig config, cl::Context context, cl::Device device)
{
	std::string sourceCode = readFile(config.getFilename());
	cl::Program program = build(sourceCode, context, device);

	auto clKernel = cl::Kernel(program, config.getFilename().c_str());
	Kernel managedKernel = Kernel(clKernel);

	auto arguments = config.getArguments();

	for (size_t i = 0; i < arguments.size(); i++) 
	{
		managedKernel.setArgument(i, arguments[i]);
	}

	return managedKernel;
}

std::string KernelFactory::readFile(std::string filename) 
{
	std::ifstream sourceFile(filename);
	std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

	return sourceCode;
}

cl::Program KernelFactory::build(std::string sourceCode, cl::Context context, cl::Device device)
{
	cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
	cl::Program program = cl::Program(context, source);
	program.build(std::vector<cl::Device>(1, device), "-I Assets");

	return program;
}