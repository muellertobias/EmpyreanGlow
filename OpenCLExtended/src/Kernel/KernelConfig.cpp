#include "KernelConfig.h"
namespace OpenCLExt
{
	namespace Kernel {

		KernelConfig::KernelConfig(std::string filename, std::string entryPoint, unsigned int nArguments)
		{
			_Filename = filename;
			_EntryPoint = entryPoint;
			_Arguments = std::vector<Argument>(nArguments);
		}


		KernelConfig::~KernelConfig()
		{
		}

		void KernelConfig::setArguments(int index, size_t valueSize, void* valuePtr)
		{
			_Arguments.at(index).pointer = valuePtr;
			_Arguments.at(index).size = valueSize;
		}

	}
}