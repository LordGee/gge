#include "Window.h"
#include "../fonts/FontManager.h"
#include "../../audio/AudioManager.h"

namespace gge
{
	namespace graphics
	{
		void Callback_WindowResize(GLFWwindow *window, int width, int height);
		void Callback_KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
		void Callback_MouseButton(GLFWwindow* window, int button, int action, int mods);
		void Callback_MouseCursorPosition(GLFWwindow* window, double xpos, double ypos);

		/* Create a new context Window constructor asign member variables */
		Window::Window(const char* name, int width, int height, bool fullScreen)
			: m_Title(name), m_Width(width), m_Height(height), m_FullScreen(fullScreen) {
			if (!Init()) { // Initialise new window
				glfwTerminate(); // if not terminate
			}
			/* Prepare arrays for keyboard inputs */
			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyHeld[i] = false;
			}
			/* Prepare arrays for mouse inputs */
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseHeld[i] = false;
			}
			/* Initialise font manager */
			FontManager::FontManagerInit();
			/* Initialise audio manager */
			audio::AudioManager::AudioInit();
		}

		/* deconstructor */
		Window::~Window() {
			/* terminate the glfw connection */
			glfwTerminate();
			/* Destroy all loaded fonts inc custom */
			FontManager::TeminateAllFonts();
			/* Remove all audio clips from the audio manager */
			audio::AudioManager::TerminateAudioClips();
		}

		/* Initialise a new Window called from the Window Constructor */
		bool Window::Init() {
			if (!glfwInit()) { // Intialise GLFW
				std::cerr << "Error Initialising GLFW!" << std::endl;
				return false;
			}
			
			if (m_FullScreen) {
				/* Gets the primary monitor used by the user only used if full screen option is selected */
				GLFWmonitor* m_Monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);
				/* resets the width and height to the size of the monitor */
				m_Width = mode->width;
				m_Height = mode->height;
				/* Generate window based on parameters */
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, m_Monitor, nullptr);
			} else {
				/* Generate window based on parameters */
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
			}
			if (!m_Window) { // check if window has been created successfully
				/* else log message and end initialisation attempt */
				std::cerr << "Failed to create GLFW Window!" << std::endl;
				return false;
			}
			/* Makes the context of the specified window current for the calling thread. */
			glfwMakeContextCurrent(m_Window);
			/* Makes the pointer available in the context window, this is useful to ensure pointer access in full screen mode */
			glfwSetWindowUserPointer(m_Window, this);
			// Init callbacks for resize and inputs related to the Window.
			glfwSetFramebufferSizeCallback(m_Window, Callback_WindowResize);
			glfwSetKeyCallback(m_Window, Callback_KeyPress);
			glfwSetMouseButtonCallback(m_Window, Callback_MouseButton);
			glfwSetCursorPosCallback(m_Window, Callback_MouseCursorPosition);
			/* Not 100% sure about this something to do with OPenGL and OPenGL ES and also VSync */
			glfwSwapInterval(0);
			if (glewInit() != GLEW_OK) { // Initialise GLEW
				/* else log message and end initialisation attempt */
				std::cerr << "Failed to initialise GLEW!" << std::endl;
				return false;
			}
			/* These two methods needed to be set to enable freetype to render fonts correctly  */
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
			return true; // Return Success
		}

		/* Check if the window has been closed or not */
		bool Window::IsClosed() {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::WindowClear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::WindowUpdate() {		
			/* Checks the current state of any key presses */
			// TODO: Need to improve this, the update loop does not pick up single key presses due to 60 fps restriction
			for (int i = 0; i < MAX_KEYS; i++) {
				m_KeyHeld[i] = m_Keys[i] && !m_KeyState[i];
			}
			memcpy(m_KeyState, m_Keys, MAX_KEYS * sizeof(bool));

			/* Checks the current state of any mouse button presses */
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseHeld[i] = m_MouseButtons[i] && !m_MouseState[i];
			}
			memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS * sizeof(bool));
			/* Updates any audio sounds that are currently playing */
			audio::AudioManager::UpdateAudio();
			/* Logger for any OpenGL errors */
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cerr << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		/* Called after the main loop has concluded to end GLFW */
		void Window::WindowDestroy() {
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		/* If the window is altered the new width and height are reflected in the member variables */
		void Callback_WindowResize(GLFWwindow * window, int width, int height) {
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		/* If a key is pressed the variable array state is updated */
		void Callback_KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}

		/* If the mouse button is pressed the variable array state is updated */
		void Callback_MouseButton(GLFWwindow * window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		/* If the mouse cursor position changes the member variables are updated */
		void Callback_MouseCursorPosition(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_X = xpos;
			win->m_Y = ypos;
		}

		/* Check if a key is held down and keeps checking until release */
		bool Window::IsKeyHeldDown(unsigned int keycode) {
			if (keycode >= MAX_KEYS) {
				std::cerr << "Invalid Key Request (Out of range)" << std::endl;
				return false;
			}
			return m_Keys[keycode];
		}

		/* Same as previous but is only actioned once until release */
		bool Window::IsKeyDown(unsigned int keycode) {
			if (keycode >= MAX_KEYS) {
				std::cerr << "Invalid Key Request (Out of range)" << std::endl;
				return false;
			}
			return m_KeyHeld[keycode];
		}

		/* Check if a mouse button is held down and keeps checking until release */
		bool Window::IsMouseButtonHeldDown(unsigned int button) {
			if (button >= MAX_BUTTONS) {
				std::cerr << "Invalid Button Request (Out of range)" << std::endl;
				return false;
			}
			return m_MouseButtons[button];
		}

		/* Same as previous but is only actioned once until release */
		bool Window::IsMouseButtonDown(unsigned int button) {
			if (button >= MAX_BUTTONS) {
				std::cerr << "Invalid Button Request (Out of range)" << std::endl;
				return false;
			}
			return m_MouseHeld[button];
		}

		/* Returns current mouse position via referenced variables */
		void Window::GetMousePos(double & xpos, double & ypos) {
			xpos = m_X;
			ypos = m_Y;
		}

	}
}
