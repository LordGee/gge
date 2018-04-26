#pragma once

#include "../graphics/windows/Window.h"
#include "../graphics/renderers/Renderer2D.h"
#include "../graphics/renderers/BatchRenderer2D.h"
#include "../graphics/shaders/Shader.h"

#include "../graphics/layers/Container.h"
#include "../graphics/renderables/Sprite.h"

#include "../graphics/fonts/Text.h"
#include "../graphics/fonts/FontManager.h"

#include "../maths/Maths.h"
#include "../utilities/Timer.h"

#include "../audio/AudioManager.h"

// Shaders
#define GGE_SHADER_BASIC_VERT			"src/shaders/basic.vert"
#define GGE_SHADER_BASIC_FRAG			"src/shaders/basic.frag"
#define GGE_SHADER_BASIC_FRAG_LIGHT		"src/shaders/light.frag"
#define GGE_SHADER_LIGHT_POS			"light_pos"

// Audio
#define GGE_AUDIO_OVERRIDE				1

// Strings
#define GGE_DEFAULT_STRING				"Default"

// Colours
#define GGE_COL_WHITE					0xffffffff
#define GGE_COL_BLACK					0xff000000
#define GGE_COL_RED						0xff0000ff
#define GGE_COL_GREEN					0xff00ff00
#define GGE_COL_BLUE					0xffff0000

using namespace gge;
using namespace graphics;
using namespace maths;
using namespace audio;



namespace gge
{
	class GGEngine {
	private:
		Window*				m_Window;
		Timer*				m_Timer;
		float				m_Time;
		unsigned int		m_FramesPerSecond, m_UpdatesPerSecond;

	protected:
		GGEngine() {
			m_FramesPerSecond = 0;
			m_UpdatesPerSecond = 0;
		}

		virtual ~GGEngine() {
			delete m_Timer;
		}

		Window* CreateWindow(const char* name, int width, int height, bool fullScreen = false) {
			m_Window = new Window(name, width, height, fullScreen);
			return m_Window;
		}

	public:
		void Initialise() {
			Start();
			Run();
		}

	protected:
		virtual void Start() = 0; // run once at start
		virtual void Tick() {} // once per second
		virtual void Update() {} // 60 frames per second
		virtual void FastUpdate() {} // as fast as render 
		virtual void Render() = 0; // as fast as possible

		const unsigned int GetFramesPerSecond() { return m_FramesPerSecond; }
		const unsigned int GetUpdatesPerSecond() { return m_UpdatesPerSecond; }

	private:
		void Run() {
			m_Timer = new Timer();
			m_Time = 0.0f;
			float updateTimer = 0.0f;
			const float updateTick = 1.0f / 60.0f;
			
			unsigned int frames = 0, updates = 0;

			while (!m_Window->IsClosed()) {
				
				m_Window->WindowClear();

				if (m_Timer->Elapsed() - updateTimer > updateTick) {
					Update();
					updateTimer = m_Timer->Elapsed();
					updates++;
				}

				FastUpdate();
				Render();
				frames++;
				m_Window->WindowUpdate();

				if (m_Timer->Elapsed() - m_Time > 1.0f) {
					m_Time = m_Timer->Elapsed();
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = updates = 0;
					Tick();
				}
			}

			m_Window->WindowDestroy();
		}
	};

	static Vector2 MouseWorldPosition(double x, double y, float w, float h) {
		return Vector2(static_cast<float>(x * 32.0f / w - 16.0f), static_cast<float>(9.0f - y * 18.0f / h));
	}
}