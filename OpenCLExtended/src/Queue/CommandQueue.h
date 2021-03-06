#pragma once
#include <memory>
#include <CL/cl.hpp>
#include "../Wrapper/Context.h"
#include "../Wrapper/Kernel.h"

namespace OpenCLExt
{
	namespace Queue
	{
		using namespace Wrapper;

		typedef struct {
			size_t sizeX;
			size_t sizeY;
			size_t sizeZ;
		} Dimensions;

		class CommandQueue
		{
		public:
			CommandQueue(std::shared_ptr<OpenCLExt::Wrapper::Context> context);
			~CommandQueue();

			void execute(std::vector<cl::Memory> externData, std::shared_ptr<OpenCLExt::Wrapper::Kernel> kernel, size_t width, size_t heigth);

			void setLocalSize(size_t sizeX, size_t sizeY)
			{
				localSize.sizeX = sizeX;
				localSize.sizeY = sizeY;
				localSize.sizeZ = 0;
			}

			void setGlobalSize(size_t sizeX, size_t sizeY, size_t sizeZ)
			{
				localSize.sizeX = sizeX;
				localSize.sizeY = sizeY;
				localSize.sizeZ = sizeZ;
			}


		private:
			std::shared_ptr<cl::CommandQueue> _Queue;
			Dimensions localSize;
			Dimensions globalSize;

			size_t divideUp(size_t a, size_t b);
		};
	}
}