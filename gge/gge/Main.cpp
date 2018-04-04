#include "src/graphics/Window.h"
#include "src/maths/Maths.h"

int main() {

	using namespace gge;
	using namespace graphics;
	using namespace maths;

	Window window("GoodGame Engine", 1920, 1080);

	Matrix orthographic = Matrix::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);


	/* Loop until the user closes the window */
	while (!window.IsClosed())
	{
		window.WindowClear();
		/* Render here */
		

		window.WindowUpdate();
	}

	window.WindowDestroy();
	return 0;
}
