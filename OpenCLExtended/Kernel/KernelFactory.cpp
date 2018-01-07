#include "KernelFactory.h"
#include <fstream>


cl::Kernel KernelFactory::create(std::string kernelEntryFunctionName, std::string kernelFilename, cl::Context context, cl::Device device)
{
	std::string sourceCode = readFile(kernelFilename);
	cl::Program program = build(sourceCode, context, device);

	return cl::Kernel(program, kernelEntryFunctionName.c_str());
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