#include "Window.h"

gge::graphics::Window::Window(const char* name, int width, int height) 
	: m_Title(name), m_Width(width), m_Height(height) {
	if (!Init()) { // Initialise new window
		glfwTerminate();
	}
}

gge::graphics::Window::~Window() {
	glfwTerminate();
}

// Initialise a new Window
bool gge::graphics::Window::Init() {
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
	/*
	glfwSetWindowSizeCallback(m_Window, WindowResize_Callback);
	glfwSetKeyCallback(m_Window, Key_Callback);
	glfwSetMouseButtonCallback(m_Window, MouseButton_Callback);
	glfwSetCursorPosCallback(m_Window, MouseCursorPosition_Callback);
	*/
	glfwSwapInterval(0.0);
	if (glewInit() != GLEW_OK) { // Initialise GLEW
		std::cerr << "Failed to initialise GLEW!" << std::endl;
		return false;
	}
	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
	return true; // Return Success
}

bool gge::graphics::Window::IsClosed() {
	return glfwWindowShouldClose(m_Window) == 1;
}
