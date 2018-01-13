// EmpyreanGlow.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <memory>
#define CL_EXT_PREFIX__VERSION_2_0_DEPRECATED


#include "Kernel/KernelConfig.h"
#include "Kernel/KernelFactory.h"
#include "Wrapper/Kernel.h"

#include "Window/Window.h"
#include "Window/WindowFactory.h"

using namespace OpenCLExt::Kernel;
using namespace OpenGLExt::Window;

int main()
{
	int argument = 5;
	KernelConfig* c = new KernelConfig("test", "entry", 5);
	c->setArguments(0, sizeof(argument), &argument);

	KernelFactory* factory = new KernelFactory();
	//Kernel kernel = factory.create(c, )

	delete(factory);
	delete(c);
	

    return 0;
}

