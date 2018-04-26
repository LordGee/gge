#include "Example.h"

void Example::Start() {
	// Create Default shader
	shader = new Shader();
	// Create a container to hold all assets
	container = new Container(shader);
	// Add a couple of images to our texture array
	images = {
		new Texture("img/test.png"),
		new Texture("img/test4.png")
	};
	// Cover the background with these images at random
	srand(0);
	for (float y = -9.0f; y < 9.0f; y += 0.5f) {
		for (float x = -16.0f; x < 16.0f; x += 0.5f) {
			container->AddToContainer(new Sprite(x, y, 0.4f, 0.4f, images[rand() % 2]));
		}
	}
	// Create a blue square sprite
	square = new Sprite(-2.0f, -2.0f, 2.0f, 2.0f, GGE_COL_BLUE);
	// Add the blue square sprite to the container
	container->AddToContainer(square);
	// Add a new font to the font manager
	FontManager::AddFont(new Font("MyFont", "font/Muli-Bold.ttf", 32));
	FontManager::GetFont("MyFont")->SetScale(window->GetWindowWidth() / 32, window->GetWindowHeight() / 18);
	// Add an fps counter
	// Create a slightly transparent background
	fpsBackground = new Sprite(-15.0f, 6.0f, 4, 2, 0xc8ffffff);
	// Create two new text objects one with default font and one with new
	fpsHeading = new Text("FPS Counter", -14.5, 7.2, GGE_COL_BLACK);
	fpsCounter = new Text("", -13.5f, 6.5f, "MyFont", GGE_COL_BLACK);
	// Add all fps objects to the container
	container->AddToContainer(fpsBackground);
	container->AddToContainer(fpsHeading);
	container->AddToContainer(fpsCounter);
	// Add a new sound effect to the audio manager
	AudioManager::AddAudioClip(new Audio("SFX", "audio/BeBop.wav"));
	// Get the new sound to use locally
	sfxAudio = AudioManager::GetAudioClip("SFX");
	// Play the default music file on a loop
	mainAudio = AudioManager::GetAudioClip(GGE_DEFAULT_STRING);
	mainAudio->SetAudioLoop(true);
	mainAudio->Play();

}

void Example::Tick() {
	// Update the fps counter every 1 second
	fpsCounter->text = std::to_string(GetFramesPerSecond());
	// Log out to console information
	std::cout << GetUpdatesPerSecond() << " UPS, " << GetFramesPerSecond() << " FPS." << std::endl;
}

void Example::Update() {
	// Add a player controller to move the square object around the screen
	if (window->IsKeyHeldDown(GLFW_KEY_LEFT)) {
		square->position.x -= speed;
		sfxAudio->Play();
	}
	else if (window->IsKeyHeldDown(GLFW_KEY_RIGHT)) {
		square->position.x += speed;
		sfxAudio->Play();
	}
	if (window->IsKeyHeldDown(GLFW_KEY_UP)) {
		square->position.y += speed;
		sfxAudio->Play();
	}
	else if (window->IsKeyHeldDown(GLFW_KEY_DOWN)) {
		square->position.y -= speed;
		sfxAudio->Play();
	}
}

void Example::FastUpdate() {
	// Pause and resume the main audio playback,
	if (window->IsKeyDown(GLFW_KEY_SPACE)) {
		if (mainAudio->IsAudioPlaying()) {
			mainAudio->Pause();
		} else {
			mainAudio->Resume();
		}
	}
}

void Example::Render() {
	// Render all objects held in the container
	container->RenderThisContainer();

	
}
