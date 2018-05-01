#pragma once

#include <GGEngine.h>

/* Set Define to 0 to execute the example project, else set to 0 */
#include "CarGame.h"
#define EXECUTE_EXAMPLE_PROJECT 1


#define GAME_NAME "My Game"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class Game : public GGEngine {
private:
	Window *			m_Window;

public:
	Game() {
		m_Window = CreateWindow(
			GAME_NAME, 
			WINDOW_WIDTH, 
			WINDOW_HEIGHT
		);
	}
	~Game() { }
	void Start() override;
	void Tick() override;
	void Update() override;
	void FastUpdate() override;
	void Render() override;
};

#if 1
int main() {
#if EXECUTE_EXAMPLE_PROJECT
	CarGame game;
#else
	Game game;
#endif
	game.Initialise();
	return 0;
}
#endif