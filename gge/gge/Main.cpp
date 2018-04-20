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
				int r = rand() % 256;
				int colour = 0xff00 << 8 | r;
				layer.Add(new Sprite(x, y, 0.4f, 0.4f, colour));
			} else {
				layer.Add(new Sprite(x, y, 0.4f, 0.4f, 
					textures[rand() % 4]));
			}
			counter++;
		}
	}

	std::cout << "Sprites drawn : " << counter << std::endl;

	double x = 0.0, y = 0.0;

	Timer timer;
	float timeCount = 0.0f;
	int frameCount = 0;

	while (!window.IsClosed())
	{
		window.WindowClear();
		shader.Enable();

		timeCount += timer.Elapsed();
		timer.Reset();
		frameCount++;
		if (timeCount >= 1.0f) {
			std::cout << "FPS: " << frameCount << std::endl;
			frameCount = 0;
			timeCount = 0.0f;


			int r = rand() % 256;
			int colour = 0xff00 << 8 | r;

			const std::vector<Renderable2D*>& rs = layer.GetRenderables();
			for (int i = 0; i < rs.size(); i++) {
				rs[i]->SetColour(colour);
			}


		}
		
		
		if (window.IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			std::cout << "Clicked" << std::endl;
		}

		window.GetMousePos(x, y);
		shader.SetUniform2f(GGE_SHADER_LIGHT_POS, 
			MouseWorldPosition(x, y, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight())));
		layer.Render();
		window.WindowUpdate();
		
	}

	for (int i = 0; i < 4; i++) {
		delete textures[i];
	}

	window.WindowDestroy();



}
