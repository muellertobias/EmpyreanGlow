// EmpyreanGlow.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#include "../OpenCLExtended/Kernel/KernelConfig.h"

int main()
{
	int argument = 5;
	KernelConfig c = KernelConfig("test", "entry", 5);
	c.setArguments(0, sizeof(argument), &argument);
    return 0;
}

