// EmpyreanGlow.cpp : Defines the entry point for the console application.
//
#include "GL/glew.h" // MUST HAVE ... GL is a bitch!
#include <iostream>
#include <memory>

#include "Window/Window.h"
#include "Window/WindowFactory.h"

#include "Context/ContextFactory.h"
#include "Wrapper/Context.h"

#include "Kernel/KernelConfig.h"
#include "Kernel/KernelFactory.h"
#include "Wrapper/Kernel.h"

#include "Queue/CommandQueue.h"

#include "Shaders\Shaders.h"
#include "Texture\Texture2D.h"

using namespace OpenCLExt::Kernel;
using namespace OpenGLExt::Windows;

int main()
{
	try 
	{
		OpenGLExt::Windows::WindowConfig windowConfig;
		windowConfig.Monitor = OpenGLExt::Windows::Primary;
		windowConfig.Title = "Empyrean Glow Window";
		windowConfig.IsFullscreen = true;

		OpenGLExt::Windows::WindowFactory windowFactory = OpenGLExt::Windows::WindowFactory();
		OpenGLExt::Windows::Window window = windowFactory.create(windowConfig);

		OpenCLExt::Context::ContextFactory contextFactory = OpenCLExt::Context::ContextFactory(0);
		std::shared_ptr<OpenCLExt::Wrapper::Context> context = contextFactory.create(0, window.getGLContext(), window.getWindowContext());

		KernelConfig c("Assets\\fractal.cl", "fractal", 0);

		KernelFactory factory = KernelFactory();
		std::shared_ptr<OpenCLExt::Wrapper::Kernel> kernel = factory.create(c, *context);

		OpenCLExt::Queue::CommandQueue queue(context);

		OpenGLExt::Shaders::Shaders shaders("Assets\\fractal.vert", "Assets\\fractal.frag");

		OpenGLExt::Texture::Texture2D texture(shaders, windowConfig.Width, windowConfig.Height); // FIX in WindowConfig steht erst nach der Erstellung des Fensters ein Wert für Höhe/Breite

		cl_int err;
		cl::ImageGL t = cl::ImageGL(*context->getNative(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, texture.getNative(), &err);

		// TODO impl
		//auto a = [t, windowConfig, kernel, queue, texture, window](double posX, double posY)
		//{
		//	
		//};
		//window.setCallback(a);

		while (!window.isClosed())
		{

			glFinish(); // TODO schauen, ob man dies ans Ende stellen kann

			kernel->setArgument(0, t);
			kernel->setArgument(1, windowConfig.Width);
			kernel->setArgument(2, windowConfig.Height);
			kernel->setArgument(3, 1.0f);
			kernel->setArgument(4, 1.0f);
			kernel->setArgument(5, 0.4f);
			kernel->setArgument(6, -0.2f);
			kernel->setArgument(7, -0.7f);
			kernel->setArgument(8, 0.27f);

			std::vector<cl::Memory> objs;
			objs.clear();
			objs.push_back(t);

			queue.execute(objs, kernel, windowConfig.Width, windowConfig.Height);
			texture.render();
			window.refresh();
		}

		window.close();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

    return 0;
}

