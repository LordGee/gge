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
			bool			m_Keys[MAX_KEYS];
			bool			m_MouseButtons[MAX_BUTTONS];
			double			m_X, m_Y;

		public:
			Window(const char* name, int width, int height);
			~Window();
			bool IsClosed();
			void WindowClear();
			void WindowUpdate();

		public:
			bool IsKeyPressed(unsigned int keycode);
			bool IsMouseButtonPressed(unsigned int button);
			void GetMousePos(double& xpos, double& ypos);

		private:
			bool Init();
			friend static void CallbackKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
			friend static void CallbackMouseCursorPosition(GLFWwindow* window, double xpos, double ypos);
		};
	}
}