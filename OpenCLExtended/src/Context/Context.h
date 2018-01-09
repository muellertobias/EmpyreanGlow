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
			Context(std::shared_ptr<cl::Context> context, cl::Device device);
			~Context();

			std::shared_ptr<cl::Context> getNative()
			{
				return _Context;
			}

			std::vector<cl_int> getProperties()
			{
				return _Properties;
			}

			cl::Device getDevice()
			{
				return _Device;
			}

		private:
			std::shared_ptr<cl::Context> _Context;
			std::vector<cl_int> _Properties;
			cl::Device _Device;
		};
	}
}