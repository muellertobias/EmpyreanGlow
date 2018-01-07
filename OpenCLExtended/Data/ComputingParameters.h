#pragma once
#include <CL\cl.hpp>
#include <memory>

typedef struct {
	std::unique_ptr<cl::Kernel> Kernel;
	std::unique_ptr<cl::CommandQueue> Queue;
	std::unique_ptr<cl::Memory> Texture; //cl::ImageGL texture;
	cl::size_t<3> Dimensions;
} ComputingParameters;