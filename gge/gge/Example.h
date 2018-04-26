#pragma once

#include <GGEngine.h>

#define EX_GAME_NAME "My Example Project"
#define EX_WINDOW_WIDTH 1920
#define EX_WINDOW_HEIGHT 1080
/* Setting the full screen option to 1 will void width and height */
#define EX_FULL_SCREEN 1

class Example : public GGEngine {

private:
	Window *					window;
	Shader*						shader;
	std::vector<Texture*>		images;
	Container*					container;
	Sprite*						square;
	Sprite*						fpsBackground;
	Text*						fpsHeading;
	Text*						fpsCounter;
	Audio*						sfxAudio;
	Audio*						mainAudio;

	const float speed = 0.5f;

public:
	Example() {
		window = CreateWindow(EX_GAME_NAME, EX_WINDOW_WIDTH, EX_WINDOW_HEIGHT, EX_FULL_SCREEN);
		FontManager::GetFont()->SetScale(window->GetWindowWidth() / 32, window->GetWindowHeight() / 18);
	}
	~Example() {
		for (int i = 0; i < images.size(); i++) {
			delete images[i];
		}
	}

	void Start() override;
	void Tick() override;
	void Update() override;
	void FastUpdate() override;
	void Render() override;

};