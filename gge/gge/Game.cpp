#include "src/gge.h"

using namespace gge;
using namespace graphics;
using namespace maths;

class Game : public GGE {
	
private:
	Window * window;
	Layer* layer;
	Text* fps;
	Sprite* whiteBox;
	Shader* shader;

	const float speed = 0.5f;

public:
	Game() { }

	~Game() {
		delete layer;
	}

	void Start() override {
		window = CreateWindow("My First Game", 1280, 720);
		FontManager::GetFont()->SetScale(window->GetWidth() / 32, window->GetHeight() / 18);
		shader = new Shader(GGE_SHADER_BASIC_VERT, GGE_SHADER_BASIC_FRAG);
		layer = new Layer(new BatchRenderer2D(), shader, Matrix::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		whiteBox = new Sprite(0.0f, 0.0f, 4.0f, 4.0f, new Texture("img/test2.png"));
		layer->Add(whiteBox);
		fps = new Text("FPS Counter", -15.5, 7.8f, 0xffffffff);
		layer->Add(fps);
	}

	void Tick() override {
		fps->text = std::to_string(GetFramesPerSecond());
		std::cout << GetUpdatesPerSecond() << " UPS, " << GetFramesPerSecond() << " FPS." << std::endl;
	}

	void Update() override {
		if (window->IsKeyPressed(GLFW_KEY_LEFT)) {
			whiteBox->position.x -= speed;
		}
		else if (window->IsKeyPressed(GLFW_KEY_RIGHT)) {
			whiteBox->position.x += speed;
		}
		if (window->IsKeyPressed(GLFW_KEY_UP)) {
			whiteBox->position.y += speed;
		}
		else if (window->IsKeyPressed(GLFW_KEY_DOWN)) {
			whiteBox->position.y -= speed;
		}

		double x, y;
		window->GetMousePos(x, y);
		shader->SetUniform2f(GGE_SHADER_LIGHT_POS, MouseWorldPosition(x, y, static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())));
	}

	void Render() override {
		layer->Render();
	}
};

int main() {
	Game game;
	game.Initialise();
	return 0;
}