#include <iostream>
#include "Window.h"

Window::Window(GLint Width, GLint Height, const GLchar* Title, GLFWwindow* SharedWindow) :
	WindowSize{ glm::vec<2, GLint>(Width, Height) },
	WindowTitle{ Title }
{
	/* @LOG */
	std::cout << "Constructing Window: " << Title << " " << Width << " x " << Height << std::endl;

	/* Setting up window properties */
	/* opengl version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	/* backwards compatibility  */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code should run or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	window = glfwCreateWindow(Width, Height, Title, nullptr, SharedWindow);
	if (!window) {
		std::cerr << "Failed to Create Window!" << std::endl;
		glfwTerminate();
		return;
	}

	/* Adding Window to Input */
	InitInput();
}
Window::~Window() {
	std::cout << "Destroying Window" << std::endl;

	ClearWindow();
}

void Window::MakeCurrent() {
	/* setting context for GLEW to use */
	/* setting up window for GLEW to use, incase if we have muliple GLFWwindow's */
	/* first we need to make sure a GLFWwindow is current context */
	glfwMakeContextCurrent(window);
}

glm::vec<2, GLint> Window::GetWindowFrameBufferSize() const {
	glm::vec<2, GLint> BufferSize{ 1 };
	glfwGetFramebufferSize(window, &BufferSize.x, &BufferSize.y);
	return BufferSize;
}

void Window::ClearWindow() {
	/* Clearing Input */
	ClearInput();
	/* Destroying Window */
	glfwDestroyWindow(window);
	//glfwTerminate();
	window = nullptr;
}

GLuint Window::GetWindowIndex(GLFWwindow* WindowToFind) {
	for (size_t i = 0; i < WindowIndices.size(); i++) {
		if (WindowIndices.at(i) == WindowToFind) {
			return i;
		}
	}
	std::cerr << "Unable to find GLFWwindow Index!" << std::endl;
	return -1;
}

void Window::InitInput() {
	/* Initializing Key Events */
	std::vector<bool> WindowKeyEvents;
	for (size_t i = 0; i < 1024; i++) {
		WindowKeyEvents.push_back(false);
	}
	/* Initializing Mouse Inputs */
	glm::vec<2, GLfloat> MouseAxis(0.f); /* this shit is not 0 by default at declaration stage, so initialize it to zero */
	/* Initializing Mouse Delta Inputs */
	glm::vec<2, GLfloat> MouseDelta(0.f);

	/* Pushing */
	WindowIndices.push_back(window);
	KeyEvents.push_back(WindowKeyEvents);
	MouseInput.push_back(MouseAxis);
	MouseDeltaInput.push_back(MouseDelta);

	/* @LOG */
	std::cout << "WindowIndices: " << WindowIndices.size() << " KeyEvents: " << KeyEvents.size() << " MouseInput: " << KeyEvents.size() << " MouseDeltaInput: " << MouseDeltaInput.size() << std::endl;

	// Binding Callbacks
	glfwSetKeyCallback(window, Window::InputEvent_Callback);
	glfwSetCursorPosCallback(window, Window::CursorPos_Callback);
}
void Window::ClearInput() { /* efficiently removes all elements with matching window index */
	/* Getting the Index of GLFWwindow */
	GLuint WindowIndex = GetWindowIndex(window);
	if (WindowIndex < 0) {
		std::cerr << "No Window to Clear its Input" << std::endl;
		return;
	}

	// Erasing GLFWwindow
	WindowIndices.erase(WindowIndices.begin() + WindowIndex);
	
	// Erasing KeyEvents
	std::vector<bool>& WindowKeyEvents = KeyEvents.at(WindowIndex);
	for (size_t i = 0; i < WindowKeyEvents.size(); i++) {
		WindowKeyEvents.at(i) = false;
	}
	WindowKeyEvents.clear();
	KeyEvents.erase(KeyEvents.begin() + WindowIndex);

	// Erasing MouseInput
	glm::vec<2, GLfloat>& WindowMouseInput = MouseInput.at(WindowIndex);
	WindowMouseInput = glm::vec<2, GLfloat>(0.f);
	MouseInput.erase(MouseInput.begin() + WindowIndex);
}

void Window::InputEvent_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key < 0 || key > 1024) return;

	KeyEvents.at(GetWindowIndex(window)).at(key) = action;
}
const std::vector<bool>& Window::GetKeyEvents() const { 
	return KeyEvents.at(GetWindowIndex(window)); 
}

void Window::CursorPos_Callback(GLFWwindow* window, double xpos, double ypos) {
	/* Previous Mouse Input */
	glm::vec<2, GLfloat>& WindowMouseInput = MouseInput.at(GetWindowIndex(window));

	/* Delta Mouse Input */
	glm::vec<2, GLfloat>& MouseDelta = MouseDeltaInput.at(GetWindowIndex(window));

	MouseDelta.x = WindowMouseInput.x ? WindowMouseInput.x - xpos : 0.f;
	MouseDelta.y = WindowMouseInput.y ? WindowMouseInput.y - ypos : 0.f;

	WindowMouseInput.x = (float)xpos;
	WindowMouseInput.y = (float)ypos;
}
const glm::vec<2, GLfloat>& Window::GetMouseInput() const {
	return MouseInput.at(GetWindowIndex(window));
}