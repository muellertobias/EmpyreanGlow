#pragma once
#include <CL\cl.hpp>
#include <memory>
namespace OpenCLExt
{
	namespace Context
	{
		class Context
		{
		public:
			Context(std::shared_ptr<cl::Context> context);
			~Context();

		private:
			std::shared_ptr<cl::Context> _Context;
			std::vector<cl_int> _Properties;
			std::vector<cl::Device> _Devices;
		};
	}
}