#include "src/gge.h"

int main() {

	using namespace gge;
	using namespace graphics;
	using namespace maths;

	const int width = 1920, height = 1080;
	Window window("GG Engine", width, height);
	Shader* s1 = new Shader(GGE_SHADER_BASIC_VERT, GGE_SHADER_BASIC_FRAG_LIGHT);
	Shader* s2 = new Shader(GGE_SHADER_BASIC_VERT, GGE_SHADER_BASIC_FRAG);
	Shader& pointShader = *s1;
	Shader& litShader = *s2;
	TileLayer background(&pointShader);
	TileLayer foreground(&litShader);

	GLint texIDs[] = {
		0,1,2,3,4,5,6,7,8,9
	};

	pointShader.Enable();
	pointShader.SetUniform1iv(GGE_SHADER_TEXTURES, 10, texIDs);

	litShader.Enable();
	litShader.SetUniform1iv(GGE_SHADER_TEXTURES, 10, texIDs);

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

			int r = rand() % 256;
			int colour = 0xffff00 << 8 | r;

			if (rand() % 2 == 0) {
				background.Add(new Sprite(x, y, 0.4f, 0.4f, colour));
			} else {
				background.Add(new Sprite(x, y, 0.4f, 0.4f,
					textures[rand() % 4]));
			}
			counter++;
		}
	}

	FontManager::AddFont(new Font("MULI", "font/Muli-Bold.ttf", 48));

	Text* fps = new Text("FPS Counter", -15, 8, FontManager::GetFont("MULI"), 0xffff424d);
	foreground.Add(fps);

	std::cout << "Sprites drawn : " << counter << std::endl;

	double x = 0.0, y = 0.0;

	Timer timer;
	float timeCount = 0.0f;
	float colourTick = 0.0f;
	int frameCount = 0;

	while (!window.IsClosed())
	{
		window.WindowClear();

		timeCount += timer.Elapsed();
		timer.Reset();
		frameCount++;
		if (timeCount >= 1.0f) {
			fps->text = std::to_string(frameCount) + " FPS";
			std::cout << "FPS: " << frameCount << std::endl;
			frameCount = 0;
			timeCount = 0.0f;
		}


		colourTick += 0.001f;
		const std::vector<Renderable2D*>& rs = background.GetRenderables();
		for (int i = 0; i < rs.size(); i++) {
			float g = sin(colourTick) / 2 + 0.5f;
			rs[i]->SetColour(Vector4(0, g, 0.8, 1));
		}

		if (window.IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			std::cout << "Clicked" << std::endl;
		}

		window.GetMousePos(x, y);
		pointShader.Enable();
		pointShader.SetUniform2f(GGE_SHADER_LIGHT_POS, 
			MouseWorldPosition(x, y, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight())));

		background.Render();
		litShader.Enable();
		foreground.Render();
		window.WindowUpdate();
		
	}

	for (int i = 0; i < 4; i++) {
		delete textures[i];
	}

	window.WindowDestroy();



}
