#pragma once

#include "graphics/windows/Window.h"
#include "maths/Maths.h"
#include "utilities/Timer.h"
#include "graphics/shaders/Shader.h"

#include "graphics/layers/TileLayer.h"
#include "graphics/renderables/Sprite.h"
#include "graphics/layers/Group.h"
#include "graphics/fonts/Text.h"
#include "graphics/fonts/FontManager.h"
// #include "audio/Audio.h"
// #include "audio/AudioManager.h"

#define GGE_SHADER_BASIC_VERT			"src/shaders/basic.vert"
#define GGE_SHADER_BASIC_FRAG			"src/shaders/basic.frag"
#define GGE_SHADER_BASIC_FRAG_LIGHT		"src/shaders/light.frag"
#define GGE_SHADER_LIGHT_POS			"light_pos"
#define GGE_SHADER_TEXTURES				"textures"
#define GGE_AUDIO_OVERRIDE				1
#define GGE_DEFAULT_STRING				"Default"

// using namespace gge;
// using namespace graphics;
// using namespace maths;
// using namespace audio;

static gge::maths::Vector2 MouseWorldPosition(double x, double y, float w, float h) {
	return gge::maths::Vector2(static_cast<float>(x * 32.0f / w - 16.0f), static_cast<float>(9.0f - y * 18.0f / h));
}

namespace gge
{
	class GGE {
	private:
		graphics::Window *	m_Window;
		Timer*				m_Timer;
		float				m_Time;
		unsigned int		m_FramesPerSecond, m_UpdatesPerSecond;
		float				m_Delta;

	protected:
		GGE() {
			m_FramesPerSecond = 0;
			m_UpdatesPerSecond = 0;
		}

		virtual ~GGE() { }

		graphics::Window* CreateWindow(const char* name, int width, int height) {
			m_Window = new graphics::Window(name, width, height);
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
		virtual void Render() = 0; // as fast a s possible

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
					updateTimer = m_Timer->Elapsed();
					Update();
					updates++;
				}

				Render();

				m_Window->WindowUpdate();

				frames++;

				if (m_Timer->Elapsed() - m_Time > 1.0f) {
					m_Time = m_Timer->Elapsed();
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = updates = 0;
					Tick();
				}
			}
		}
	};
}