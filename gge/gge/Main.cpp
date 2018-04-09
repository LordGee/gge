#include "src/gge.h"

int main() {

	using namespace gge;
	using namespace graphics;
	using namespace maths;

	const int width = 1280, height = 720;
	Window window("GG Engine", width, height);
	Shader* s = new Shader(GGE_SHADER_BASIC_VERT, GGE_SHADER_BASIC_FRAG_LIGHT);
	Shader& shader = *s;
	TileLayer layer(&shader);

	GLint texIDs[] = {
		0,1,2,3,4,5,6,7,8,9
	};

	shader.Enable();
	shader.SetUniform1iv(GGE_SHADER_TEXTURES, 10, texIDs);

	Texture* textures[] = {
		new Texture("img/test.png"),
		new Texture("img/test2.png"),
		new Texture("img/test3.png"),
		new Texture("img/test4.png")
	};

	int counter = 0;
	srand(0);
	for (float y = -9.0f; y < 9.0f; y += 0.5) {
		for (float x = -16.0f; x < 16.0f; x += 0.5) {
			if (rand() % 4 == 0) {
				layer.Add(new Sprite(x, y, 0.4f, 0.4f, 
					Vector4(rand() % 1000 / 1000.0f, 
						rand() % 1000 / 1000.0f, 
						rand() % 1000 / 1000.0f, 1)));
			} else {
				layer.Add(new Sprite(x, y, 0.4f, 0.4f, 
					textures[rand() % 4]));
			}
			counter++;
		}
	}

	std::cout << "Sprites drawn : " << counter << std::endl;

	double x = 0.0, y = 0.0;

	// todo: Create Timer
	while (!window.IsClosed())
	{
		window.WindowClear();
		shader.Enable();
		window.GetMousePos(x, y);
		shader.SetUniform2f(GGE_SHADER_LIGHT_POS, 
			MouseWorldPosition(x, y, (float)width, (float)height));
		layer.Render();
		window.WindowUpdate();
	}

	for (int i = 0; i < 4; i++) {
		delete textures[i];
	}

	window.WindowDestroy();



}
