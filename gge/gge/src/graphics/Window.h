#pragma once

#include <glew.h>
#include <glfw3.h>
#include <iostream>

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

		public:
			Window(const char* name, int width, int height);
			~Window();
			bool IsClosed();

		private:
			bool Init();
		};
	}
}