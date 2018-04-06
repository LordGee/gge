#include "src/graphics/Window.h"
#include "src/maths/Maths.h"
#include "src/graphics/Shader.h"

#include "src/graphics/layers/TileLayer.h"
#include "src/graphics/renderers/Sprite.h"
#include "src/graphics/layers/Group.h"

int main() {

	using namespace gge;
	using namespace graphics;
	using namespace maths;

	Window window("GoodGame Engine", 1920, 1080);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.Enable();
	shader.SetUniform2f("light_position", Vector2(4.0f, 1.5f));

	GLint texIDs[] = {
		0,1,2,3,4,5,6,7,8,9
	};
	shader.SetUniform1iv("textures", 10, texIDs);


	TileLayer layer(&shader);
	unsigned int count = 0;

	Texture* textures[] = {
		new Texture("img/test.png"),
		new Texture("img/test2.png"),
		new Texture("img/test3.png"),
		new Texture("img/test4.png")
	};

	for (float y = -9.0f; y < 9.0f; y++) {
		for (float x = -16.0f; x < 16.0f; x++) {
			if (rand() % 4 == 0) {
				layer.Add(new Sprite(x, y, 0.9f, 0.9f, Vector4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
			}
			else {
				layer.Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 4]));
			}

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

	for (int i = 0; i < 4; i++)
	{
		delete textures[i];
	}

	window.WindowDestroy();
	return 0;
}
