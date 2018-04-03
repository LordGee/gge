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
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		// glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
