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
		// Fenster erstellen
		OpenGLExt::Windows::WindowConfig windowConfig;
		windowConfig.Monitor = OpenGLExt::Windows::Primary;
		windowConfig.Title = "Empyrean Glow Window";
		windowConfig.IsFullscreen = false;

		OpenGLExt::Windows::WindowFactory windowFactory = OpenGLExt::Windows::WindowFactory();
		OpenGLExt::Windows::Window window = windowFactory.create(windowConfig);
		// Open CL init stuff
		OpenCLExt::Context::ContextFactory contextFactory = OpenCLExt::Context::ContextFactory(0);
		std::shared_ptr<OpenCLExt::Wrapper::Context> context = contextFactory.create(0, window.getGLContext(), window.getWindowContext());
		// Kernel für Mandelbrot
		KernelConfig c("Assets\\fractal.cl", "fractal", 0);

		KernelFactory factory = KernelFactory();
		std::shared_ptr<OpenCLExt::Wrapper::Kernel> kernel = factory.create(c, *context);

		OpenCLExt::Queue::CommandQueue queue(context);

		OpenGLExt::Shaders::Shaders shaders("Assets\\fractal.vert", "Assets\\fractal.frag");

		OpenGLExt::Texture::Texture2D texture(shaders, windowConfig.Width, windowConfig.Height); // FIX in WindowConfig steht erst nach der Erstellung des Fensters ein Wert für Höhe/Breite

		cl_int err;
		cl::ImageGL t = cl::ImageGL(*context->getNative(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, texture.getNative(), &err);

		volatile double positionX = 0.0;
		volatile double positionY = 540.0;
		volatile short scrollDirection = 0;

		window.SetClickCallback(std::function<void(double, double)>([&positionX, &positionY](double posX, double posY)
		{
			positionX = posX;
			positionY = posY;
		}));

		window.SetScrollCallback(std::function<void(short, double, double)>([&scrollDirection, &positionX, &positionY](short scrollDir, double posX, double posY)
		{
			scrollDirection = scrollDir; // 0 oder 1 oder -1
			/*positionX = posX;
			positionY = posY;*/
		}));

		int height = windowConfig.Height;
		int width = windowConfig.Width;

		window.SetWindowSizeChangedCallback(std::function<void(int, int)>([&width, &height](int w, int h) 
		{
			height = h;
			width = w;
		}));

		kernel->setArgument(0, t);
		kernel->setArgument(1, windowConfig.Width);
		kernel->setArgument(2, windowConfig.Height);
		kernel->setArgument(3, 1.0f);
		kernel->setArgument(4, 1.0f);
		kernel->setArgument(5, 0.4f);
		kernel->setArgument(6, -0.2f);

		float zoom = 1.0f;
		float moveX = 0.0f; // windowConfig.Width / 2
		float moveY = 0.0f; // windowConfig.Height / 2
		float yPosOld = positionY;
		float xPosOld = positionX;
		float cal = 1; //0.9645; // hard durch Tests
		int directionX;
		int directionY;

		std::vector<cl::Memory> objs;
		objs.clear();
		objs.push_back(t);
		while (!window.isClosed())
		{
			zoom = zoom + 0.1 * scrollDirection;
			scrollDirection = 0;

			// Move X,Y Berechnung
			
			if (positionY != yPosOld || positionX != xPosOld) {
				float oldMX = moveX;
				float oldMY = moveY;
				float faY = ((positionY - (float)(height / 2)) * (cal / (float)(height / 2))); 
				float faX = ((positionX - (float)(width / 2)) * (cal / (float)(width / 2))); 
				moveY += faY * (float)exp(-zoom + 1);
				moveX += faX * (float)exp(-zoom + 1);
				yPosOld = positionY;
				xPosOld = positionX;

				// Berechnung des Fades
				// TODO: exponentielles Faden 
				float a = 1;
				float fadeFrames = a / 100;
				int counter = 100 / a;
				float stepX = 0;
				float stepY = 0;

				if ((oldMX > 0 && moveX > 0) || (oldMX < 0 && moveX < 0)) {
					stepX = abs(abs(moveX) - abs(oldMX)) * fadeFrames;
				}
				else {
					stepX = (abs(moveX) + abs(oldMX)) * fadeFrames;
				}

				if ((oldMY > 0 && moveY > 0) || (oldMY < 0 && moveY < 0)) {
					stepY = abs(abs(moveY) - abs(oldMY)) * fadeFrames;
				}
				else {
					stepY = (abs(moveY) + abs(oldMY)) * fadeFrames;
				}

				while (counter > 0 && !window.isClosed())
				{
				
					if (moveX > oldMX) {
						oldMX += (stepX);
					}
					else if (moveX <= oldMX) {
						oldMX -= (stepX);
					}
					if (moveY > oldMY) {
						oldMY += (stepY);
					}
					else if(moveY <= oldMY) {
						oldMY -= (stepY);
					}
					counter--;
					glFinish();

					zoom = zoom + 0.1 * scrollDirection;
					scrollDirection = 0;

					kernel->setArgument(3, (float)exp(-zoom + 1)); // zoom X
					kernel->setArgument(4, (float)exp(-zoom + 1)); // zoom Y
					kernel->setArgument(5, oldMX); // move X
					kernel->setArgument(6, oldMY); // move Y
					 
					queue.execute(objs, kernel, windowConfig.Width, windowConfig.Height);
					texture.render();
					window.refresh();
				}
			}
			else {
				glFinish();
				kernel->setArgument(3, (float)exp(-zoom + 1)); // zoom X
				kernel->setArgument(4, (float)exp(-zoom + 1)); // zoom Y
				kernel->setArgument(5, moveX);//exp(moveX)); // move X
				kernel->setArgument(6, moveY);//exp(moveY)); // move Y

				queue.execute(objs, kernel, windowConfig.Width, windowConfig.Height);
				texture.render();
				window.refresh();
			}

			//moveX += 0.001;
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

