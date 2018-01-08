#pragma once
#include <cl/cl.hpp>
#include "KernelConfig.h"

class Kernel
{
public:
	Kernel(cl::Kernel kernel);
	~Kernel();

	void setArgument(size_t index, Argument argument);
	void setArgument(size_t index, size_t argSize, void* argValue);
	template<typename TType> void setArgument(size_t index, TType argument);

private:
	cl::Kernel _Kernel;
};

