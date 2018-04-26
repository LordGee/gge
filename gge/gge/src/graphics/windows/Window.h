#pragma once

#include <glew.h>
#include <glfw3.h>
#include <iostream>

#define MAX_KEYS 512
#define MAX_BUTTONS 52

namespace gge
{
	namespace graphics
	{
		class Window {
		private:
			GLFWmonitor *	m_Monitor;
			GLFWwindow *	m_Window;
			const char*		m_Title;
			int				m_Width, m_Height;
			bool			m_Closed;
			bool			m_FullScreen;

			bool			m_MouseButtons[MAX_BUTTONS];
			bool			m_MouseState[MAX_BUTTONS];
			bool			m_MouseHeld[MAX_BUTTONS];

			bool			m_Keys[MAX_KEYS];
			bool			m_KeyState[MAX_KEYS];
			bool			m_KeyHeld[MAX_KEYS];
			double			m_X, m_Y;

		public:
			Window(const char* name, int width, int height, bool fullScreen);
			~Window();
			bool IsClosed();
			void WindowClear();
			void WindowUpdate();
			void WindowDestroy();

		public:
			bool IsKeyHeldDown(unsigned int keycode);
			bool IsKeyDown(unsigned int keycode);
			bool IsMouseButtonHeldDown(unsigned int button);
			bool IsMouseButtonDown(unsigned int button);
			void GetMousePos(double& xpos, double& ypos);

			inline int GetWindowWidth() { return m_Width; }
			inline int GetWindowHeight() { return m_Height; }

		private:
			bool Init();
			friend void Callback_WindowResize(GLFWwindow *window, int width, int height);
			friend void Callback_KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void Callback_MouseButton(GLFWwindow* window, int button, int action, int mods);
			friend void Callback_MouseCursorPosition(GLFWwindow* window, double xpos, double ypos);
		};
	}
}