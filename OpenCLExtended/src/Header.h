#pragma once
#include "Kernel/KernelConfig.h"
#include "Kernel/KernelFactory.h"
#include "Wrapper/Kernel.h"

void test() 
{
	using namespace OpenCLExt::Kernel;

	int argument = 5;
	KernelConfig* c = new KernelConfig("test", "entry", 5);
	c->setArguments(0, sizeof(argument), &argument);

	KernelFactory* factory = new KernelFactory();
	//Kernel kernel = factory.create(c, )

	delete(factory);
	delete(c);
}