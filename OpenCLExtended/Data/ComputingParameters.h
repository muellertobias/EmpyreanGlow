#pragma once
#include <CL\cl.hpp>

typedef struct {
	cl::Kernel kernel;
	cl::CommandQueue queue;
	cl::ImageGL texture;
	cl::size_t<3> dims;
} ComputingParameters;