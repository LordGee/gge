#include "CarGame.h"

/* Start() executes only at the start of the game */
void ::CarGame::Start() {
	shader = new Shader();
	background = new Container(shader);
	action = new Container(shader);
	info = new Container(shader);
	track = new Sprite(-16, -9, 32, 18, 0xffffffff);
	barrier.push_back(new Sprite(-16, -9, 32, 2, 0xff242b45));
	barrier.push_back(new Sprite(-16, -9, 2, 18, 0xff242b45));
	barrier.push_back(new Sprite(-14, 7, 32, 2, 0xff242b45));
	barrier.push_back(new Sprite(14, -7, 2, 18, 0xff242b45));
	barrier.push_back(new Sprite(-10, -3, 20, 6, 0xff000000));
	barrier.push_back(new Sprite(9.5, -7, 0.5, 4, 0xff12ff00));
	background->AddToContainer(track);
	for (int i = 0; i < barrier.size(); i++) {
		background->AddToContainer(barrier[i]);
	}
	carRight = new Texture("img/car_right2.png");
	player = new Sprite(7.0f, -5.5f, carSize, carSize, carRight);
	action->AddToContainer(player);
	FontManager::AddFont(new Font("mytext", "font/Muli-Bold.ttf", 32));
	FontManager::GetFont("mytext")->SetScale(m_Window->GetWindowWidth() / 32, m_Window->GetWindowHeight() / 18);
	timeText = new Text("Time: 0.0000", -15.5, 8, "mytext", GGE_COL_WHITE);
	lapText = new Text("Lap: 0", 13, 8, "mytext", GGE_COL_WHITE);
	bestText = new Text("Best Lap: 99.999", -2, 0, "mytext", GGE_COL_WHITE);
	info->AddToContainer(timeText);
	info->AddToContainer(lapText);
	info->AddToContainer(bestText);
}

/* Tick() executes once per second */
void ::CarGame::Tick() {
	lapText->text = "Lap: " + std::to_string(lap);
}

/* Update() executes 60 times a second */
void ::CarGame::Update() {
	if (m_Window->IsKeyHeldDown(GLFW_KEY_LEFT)) {
		player->position.x -= speed;
		if (player->position.x > -10 - carSize && player->position.x < 10 && player->position.y > -3 - carSize && player->position.y < 3
			|| player->position.x > 16 - carSize || player->position.x < -16 || player->position.y > 9 - carSize || player->position.y < -9) {
			player->position.x += speed;
		}
	}
	else if (m_Window->IsKeyHeldDown(GLFW_KEY_RIGHT)) {
		player->position.x += speed;
		if (player->position.x > -10 - carSize && player->position.x < 10 && player->position.y > -3 - carSize && player->position.y < 3
			|| player->position.x > 16 - carSize || player->position.x < -16 || player->position.y > 9 - carSize || player->position.y < -9) {
			player->position.x -= speed;
		}
	}
	if (m_Window->IsKeyHeldDown(GLFW_KEY_UP)) {
		player->position.y += speed;
		if (player->position.x > -10 - carSize && player->position.x < 10 && player->position.y > -3 - carSize && player->position.y < 3
			|| player->position.x > 16 - carSize || player->position.x < -16 || player->position.y > 9 - carSize || player->position.y < -9) {
			player->position.y -= speed;
		}
	}
	else if (m_Window->IsKeyHeldDown(GLFW_KEY_DOWN)) {
		player->position.y -= speed;
		if (player->position.x > -10 - carSize && player->position.x < 10 && player->position.y > -3 - carSize && player->position.y < 3
			|| player->position.x > 16 - carSize || player->position.x < -16 || player->position.y > 9 - carSize || player->position.y < -9) {
			player->position.y += speed;
		}
	}
	bool finishLap = false;
	if (player->position.x > 10 - carSize / 2 && player->position.y < -3 - carSize / 2) {
		checkPoints[0] = true;
		if (checkPoints[3]) {
			finishLap = true;
		}
	}
	else if (player->position.x > 10 - carSize / 2 && player->position.y > 3 - carSize / 2) {
		if (checkPoints[0]) {
			checkPoints[1] = true;
		}
	}
	else if (player->position.x < -10 - carSize / 2 && player->position.y > 3 - carSize / 2) {
		if (checkPoints[1]) {
			checkPoints[2] = true;
		}
	}
	else if (player->position.x < -10 - carSize / 2 && player->position.y < -3 - carSize / 2) {
		if (checkPoints[2]) {
			checkPoints[3] = true;
		}
	}
	if (finishLap) {
		for (int i = 0; i < 4; i++) {
			checkPoints[i] = false;
		}
		lap++;
		if (currentTimer < bestLap) {
			bestLap = currentTimer;
			bestText->text = "Best Lap: " + std::to_string(bestLap);
		}
		currentTimer = 0.0f;
	}
	currentTimer += GetTimer() - updateTimer;
	updateTimer = GetTimer();
	timeText->text = "Time: " + std::to_string(currentTimer);
}

/* FastUpdate() executes as fast as the Render method */
void CarGame::FastUpdate() { }

/* Render() executes as fast as possible */
void ::CarGame::Render() {
	background->RenderThisContainer();
	info->RenderThisContainer();
	action->RenderThisContainer();

}
