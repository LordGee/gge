#include "Window.h"

namespace gge
{
	namespace graphics
	{
		void CallbackWindowResize(GLFWwindow *window, int width, int height);
		void CallbackKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
		void CallbackMouseButton(GLFWwindow* window, int button, int action, int mods);
		void CallbackMouseCursorPosition(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char* name, int width, int height)
			: m_Title(name), m_Width(width), m_Height(height) {
			if (!Init()) { // Initialise new window
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		// Initialise a new Window
		bool Window::Init() {
			if (!glfwInit()) { // Intialise GLFW
				std::cerr << "Error Initialising GLFW!" << std::endl;
				return false;
			}
			// Generate window based on parameters
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
			if (!m_Window) {
				std::cerr << "Failed to create GLFW Window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);

			// Init callbacks for resize and inputs related to the Window.
			glfwSetWindowSizeCallback(m_Window, CallbackWindowResize);
			glfwSetKeyCallback(m_Window, CallbackKeyPress);
			glfwSetMouseButtonCallback(m_Window, CallbackMouseButton);
			glfwSetCursorPosCallback(m_Window, CallbackMouseCursorPosition);

			glfwSwapInterval(0);
			if (glewInit() != GLEW_OK) { // Initialise GLEW
				std::cerr << "Failed to initialise GLEW!" << std::endl;
				return false;
			}
			std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
			return true; // Return Success
		}

		bool Window::IsClosed() {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::WindowClear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::WindowUpdate() {
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cerr << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void Window::WindowDestroy() {
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void CallbackWindowResize(GLFWwindow * window, int width, int height) {
			glViewport(0, 0, width, height);
		}

		void CallbackKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		void CallbackMouseButton(GLFWwindow * window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void CallbackMouseCursorPosition(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_X = xpos;
			win->m_Y = ypos;
		}

		bool Window::IsKeyPressed(unsigned int keycode) {
			if (keycode >= MAX_KEYS) {
				std::cerr << "Invalid Key Request (Out of range)" << std::endl;
				return false;
			}
			return m_Keys[keycode];
		}

		bool Window::IsMouseButtonPressed(unsigned button) {
			if (button >= MAX_BUTTONS) {
				std::cerr << "Invalid Button Request (Out of range)" << std::endl;
				return false;
			}
			return m_MouseButtons[button];
		}

		void Window::GetMousePos(double & xpos, double & ypos) {
			xpos = m_X;
			ypos = m_Y;
		}

	}
}