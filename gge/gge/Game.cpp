#include "src/GGEngine.h"
#include "src/graphics/layers/TileLayer.h"

#define GAME_NAME "My First Game"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class Game : public GGEngine {
	
private:
	Window * window;
	Layer* layer;
	// TileLayer* layerT;
	Text* fps;
	Sprite* box;
	Shader* shader;
	// Texture* myPicture;

	const float speed = 0.5f;

public:
	Game() { }

	~Game() {

	}

	/* Start() executes only at the start of the application*/
	void Start() override {
		window = CreateWindow(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
		FontManager::GetFont()->SetScale(window->GetWidth() / 32, window->GetHeight() / 18);
		shader = new Shader(GGE_SHADER_BASIC_VERT, GGE_SHADER_BASIC_FRAG);
		layer = new Layer(new BatchRenderer2D(), shader, Matrix::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		// layer = new TileLayer(shader);
		// myPicture = new Texture("img/test3.png");

		Texture* textures[] = {
			new Texture("img/test.png"),
			new Texture("img/test2.png"),
			new Texture("img/test3.png"),
			new Texture("img/test4.png")
		};

		srand(0);
		for (float y = -9.0f; y < 9.0f; y += 0.5f) {
			for (float x = -16.0f; x < 16.0f; x += 0.5f) {
				layer->Add(new Sprite(x, y, 0.4f, 0.4f, textures[rand() % 4]));
			}
		}



		box = new Sprite(-2.0f, -2.0f, 2.0f, 2.0f, GGE_COL_BLUE);
		layer->Add(box);
		fps = new Text("FPS Counter", -15.5, 7.8f, GGE_COL_WHITE);
		layer->Add(fps);
	}

	/* Tick() executes once per second */
	void Tick() override {
		fps->text = std::to_string(GetFramesPerSecond());
		std::cout << GetUpdatesPerSecond() << " UPS, " << GetFramesPerSecond() << " FPS." << std::endl;
	}

	/* Update() executes 60 times a second */
	void Update() override {
		if (window->IsKeyPressed(GLFW_KEY_LEFT)) {
			box->position.x -= speed;
		}
		else if (window->IsKeyPressed(GLFW_KEY_RIGHT)) {
			box->position.x += speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_UP)) {
			box->position.y += speed;
		}
		else if (window->IsKeyPressed(GLFW_KEY_DOWN)) {
			box->position.y -= speed;
		}
		/*
		double x, y;
		window->GetMousePos(x, y);
		shader->SetUniform2f(GGE_SHADER_LIGHT_POS, MouseWorldPosition(x, y, static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())));
		*/
	}

	/* Render() executes as fast as possible (this will exceeed the update) */
	void Render() override {
		layer->Render();
	}
};

#if 1
int main() {
	Game game;
	game.Initialise();
	return 0;
}
#endif
