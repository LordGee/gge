#include <glew.h>
#include <glfw3.h>

#include "src/graphics/Window.h"

int main() {

	using namespace gge;
	using namespace graphics;

	Window window("GoodGame Engine", 1920, 1080);

	/* Loop until the user closes the window */
	while (!window.IsClosed())
	{
		window.WindowClear();
		/* Render here */
		window.WindowUpdate();
	}

	return 0;
}
