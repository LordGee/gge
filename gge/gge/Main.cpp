#include "src/graphics/Window.h"
#include "src/maths/Maths.h"
#include "src/graphics/Shader.h"

#include "src/graphics/layers/TileLayer.h"
#include "src/graphics/renderers/Sprite.h"

int main() {

	using namespace gge;
	using namespace graphics;
	using namespace maths;

	Window window("GoodGame Engine", 1920, 1080);

	Matrix orthographic = Matrix::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.Enable();
	shader.SetUniform2f("light_position", Vector2(4.0f, 1.5f));

	TileLayer layer(&shader);

	unsigned int count = 0;
	for (float y = -9.0f; y < 9.0f; y += 0.1f) {
		for (float x = -16.0f; x < 16.0f; x += 0.1f) {
			layer.Add(new Sprite
			(x, y, 0.09f, 0.09f, Vector4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
			count++;
		}
	}

	std::cout << "Sprites on screen: " << count << std::endl;

	// todo: Create Timer

	/* Loop until the user closes the window */
	while (!window.IsClosed())
	{
		window.WindowClear();

		double x, y;
		window.GetMousePos(x, y);

		shader.Enable();
		shader.SetUniform2f("light_pos", 
			Vector2(static_cast<float>(x * 32.0f / 1920.0f - 16.0f), 
				static_cast<float>(9.0f - y * 18.0f / 1080.0f)));

		layer.Render();

		window.WindowUpdate();
	}

	window.WindowDestroy();
	return 0;
}
