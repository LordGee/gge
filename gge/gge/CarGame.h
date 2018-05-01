#pragma once

#include <GGEngine.h>

#define GAME_NAME "My Car Game"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class CarGame : public GGEngine {
private:
	Window * m_Window;

public:
	Shader * shader;
	Container*				background;
	Container*				info;
	Container*				action;
	Sprite*					track;
	std::vector<Sprite*>	barrier;
	Sprite*					player;
	Texture*				carRight;
	const int				carSize = 2;
	const float				speed = 0.2f;
	bool					checkPoints[4];
	float					currentTimer = 0.0f;
	float 					updateTimer = 0.0;
	int						lap = 0;
	float					bestLap = 99.99f;
	Text*					lapText;
	Text*					timeText;
	Text*					bestText;


public:
	CarGame() {
		m_Window = CreateWindow(
			GAME_NAME,
			WINDOW_WIDTH,
			WINDOW_HEIGHT
		);

	}
	~CarGame() { }
	void Start() override;
	void Tick() override;
	void Update() override;
	void FastUpdate() override;
	void Render() override;
};
