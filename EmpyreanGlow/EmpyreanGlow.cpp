// EmpyreanGlow.cpp : Defines the entry point for the console application.
//
#include "GL/glew.h" // MUST HAVE ... GL is a bitch!
#include <iostream>
#include <memory>
#include <thread>
#include <functional>
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
		volatile double positionX = 0.0;
		volatile double positionY = 0.0;
		volatile short scrollDirection = 0;

		int height = 0;
		int width = 0;

		float zoom = 1.0f;
		float newMoveX = 0.0f; 
		float newMoveY = 0.0f; 

		float currentMoveX = 0.0f;
		float currentMoveY = 0.0f;

		float oldPositionY = positionY;
		float oldPositionX = positionX;

		float stepX = 0;
		float stepY = 0;
		int stepCounter = 0;

		// Fenster erstellen
		OpenGLExt::Windows::WindowConfig windowConfig;
		windowConfig.Monitor = OpenGLExt::Windows::Primary;
		windowConfig.Title = "Empyrean Glow Window";
		windowConfig.IsFullscreen = false;

		OpenGLExt::Windows::WindowFactory windowFactory = OpenGLExt::Windows::WindowFactory();
		OpenGLExt::Windows::Window window = windowFactory.create(windowConfig);
		height = windowConfig.Height;
		width = windowConfig.Width;

		window.SetClickCallback(std::function<void(double, double)>([&positionX, &positionY](double posX, double posY)
		{
			positionX = posX;
			positionY = posY;
		}));

		window.SetScrollCallback(std::function<void(short, double, double)>([&scrollDirection, &positionX, &positionY](short scrollDir, double posX, double posY)
		{
			scrollDirection = scrollDir; // 0 oder 1 oder -1
		}));

		window.SetWindowSizeChangedCallback(std::function<void(int, int)>([&width, &height](int _width, int _heigth)
		{
			height = _heigth;
			width = _width;
		}));

		// Open CL init stuff
		OpenCLExt::Context::ContextFactory contextFactory = OpenCLExt::Context::ContextFactory(0);
		std::shared_ptr<OpenCLExt::Wrapper::Context> context = contextFactory.create(0, window.getGLContext(), window.getWindowContext());
		
		// Kernel für Mandelbrot
		KernelConfig kernelConfig("Assets\\fractal.cl", "fractal", 0);
		KernelFactory factory = KernelFactory();
		std::shared_ptr<OpenCLExt::Wrapper::Kernel> kernel = factory.create(kernelConfig, *context);

		OpenCLExt::Queue::CommandQueue queue(context);

		OpenGLExt::Shaders::Shaders shaders("Assets\\fractal.vert", "Assets\\fractal.frag");
		OpenGLExt::Texture::Texture2D texture(shaders, windowConfig.Width, windowConfig.Height); // FIX in WindowConfig steht erst nach der Erstellung des Fensters ein Wert für Höhe/Breite

		cl_int err;
		cl::ImageGL image = cl::ImageGL(*context->getNative(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, texture.getNative(), &err);
		if (err != CL_SUCCESS)
			throw new std::exception("texture failure");

		std::vector<cl::Memory> memory = { image };
		kernel->setArgument(0, image);
		kernel->setArgument(1, windowConfig.Width);
		kernel->setArgument(2, windowConfig.Height);

		while (!window.isClosed())
		{
			glFinish();

			zoom = zoom + 0.1 * scrollDirection;
			scrollDirection = 0; // reset
			float scale = (float)exp(1 - zoom);

			// Move X,Y Berechnung
			if (positionY != oldPositionY || positionX != oldPositionX) 
			{
				float factorY = ((positionY - (float)(height / 2.0)) * (1.0 / (float)(height / 2.0)));
				float factorX = ((positionX - (float)(width / 2.0)) * (1.0 / (float)(width / 2.0)));
				newMoveY += factorY * scale;
				newMoveX += factorX * scale;
				oldPositionY = positionY;
				oldPositionX = positionX;

				// Berechnung des Fades
				// TODO: exponentielles Faden 
				float a = 1;
				float fadeFrames = a / 100;
				stepCounter = 100 / a;
				stepX = 0;
				stepY = 0;

				if ((currentMoveX > 0 && newMoveX > 0) || (currentMoveX < 0 && newMoveX < 0))
				{
					stepX = abs(abs(newMoveX) - abs(currentMoveX)) * fadeFrames;
				}
				else
				{
					stepX = (abs(newMoveX) + abs(currentMoveX)) * fadeFrames;
				}

				if ((currentMoveY > 0 && newMoveY > 0) || (currentMoveY < 0 && newMoveY < 0))
				{
					stepY = abs(abs(newMoveY) - abs(currentMoveY)) * fadeFrames;
				}
				else
				{
					stepY = (abs(newMoveY) + abs(currentMoveY)) * fadeFrames;
				}
			}

			if (stepCounter > 0) 
			{
				if (newMoveX > currentMoveX)
				{
					currentMoveX += (stepX);
				}
				else if (newMoveX <= currentMoveX)
				{
					currentMoveX -= (stepX);
				}
				if (newMoveY > currentMoveY)
				{
					currentMoveY += (stepY);
				}
				else if (newMoveY <= currentMoveY)
				{
					currentMoveY -= (stepY);
				}
				stepCounter--;
			}

			kernel->setArgument(3, scale); 
			kernel->setArgument(4, scale); 
			kernel->setArgument(5, currentMoveX); 
			kernel->setArgument(6, currentMoveY);
					 
			queue.execute(memory, kernel, windowConfig.Width, windowConfig.Height);
			texture.render();
			window.refresh();
		}
		
		window.close();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

    return 0;
}

