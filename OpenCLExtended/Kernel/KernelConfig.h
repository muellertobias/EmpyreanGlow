#pragma once
#include <string>
#include <vector>

typedef struct {
	void* pointer;
	size_t size;
} Argument;

class KernelConfig
{
public:
	KernelConfig(std::string filename, std::string entryPoint, unsigned int nArguments);
	~KernelConfig();

	void setArguments(int index, size_t valueSize, void* valuePtr);

	const std::string& getFilename()
	{
		return _Filename;
	}

	const std::string& getEntryPoint()
	{
		return _EntryPoint;
	}

	const std::vector<Argument>& getArguments() 
	{
		return _Arguments;
	}

private:
	std::string _Filename;
	std::string _EntryPoint;
	std::vector<Argument> _Arguments;
};

