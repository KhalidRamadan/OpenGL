

#if 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


// my headers 
#include "core/Window.h"

int main()
{
	using namespace core;
	using namespace math;
	std::string name = "Hello OpenGL";
	int width = 800;
	int height = 600;
	{
		Window mywindow(name.c_str(), width, height);

		vec4 color(0.2f, 0.3f, 0.3f, 1.0f);

		mywindow.setClearColor(color);


		while (mywindow.closed() == 0)
		{
			mywindow.clear();

			if (mywindow.isKeyPressed(GLFW_KEY_ESCAPE) == 1)
				mywindow.close();

			mywindow.update();
		}
	}


	system("PAUSE");
	return 0;
}

#endif 