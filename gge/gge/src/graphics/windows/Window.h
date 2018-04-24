#pragma once

#include <glew.h>
#include <glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 52

namespace gge
{
	namespace graphics
	{
		class Window {
		private:
			GLFWwindow *	m_Window;
			const char*		m_Title;
			int				m_Width, m_Height;
			bool			m_Closed;

			bool			m_MouseButtons[MAX_BUTTONS];
			bool			m_MouseState[MAX_BUTTONS];
			bool			m_MouseHeld[MAX_BUTTONS];

			bool			m_Keys[MAX_KEYS];
			bool			m_KeyState[MAX_KEYS];
			bool			m_KeyHeld[MAX_KEYS];
			double			m_X, m_Y;

		public:
			Window(const char* name, int width, int height);
			~Window();
			bool IsClosed();
			void WindowClear();
			void WindowUpdate();
			void WindowDestroy();

		public:
			bool IsKeyPressed(unsigned int keycode);
			bool IsKeyHeld(unsigned int keycode);
			bool IsMouseButtonPressed(unsigned int button);
			bool IsMouseButtonDown(unsigned int button);
			void GetMousePos(double& xpos, double& ypos);

			inline int GetWidth() { return m_Width; }
			inline int GetHeight() { return m_Height; }

		private:
			bool Init();
			friend void CallbackWindowResize(GLFWwindow *window, int width, int height);
			friend void CallbackKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
			friend void CallbackMouseCursorPosition(GLFWwindow* window, double xpos, double ypos);
		};
	}
}