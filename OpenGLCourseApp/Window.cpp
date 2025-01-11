#include <iostream>
#include "Window.h"

Window::Window(GLint Width, GLint Height, const GLchar* Title, GLFWwindow* SharedWindow) :
	WindowSize{ glm::vec<2, GLint>(Width, Height) },
	WindowTitle{ Title }
{
	std::cout << "Constructing Window: " << Title << " " << Width << " x " << Height << std::endl;

	/* Setting up window properties */
	/* opengl version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	/* backwards compatibility  */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code should run or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	window = glfwCreateWindow(Width, Height, Title, nullptr, SharedWindow);
	if (window == nullptr) {
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

void Window::InitInput() {
	NPair<GLFWwindow*, std::vector<bool>> WindowKeyEvents;
	WindowKeyEvents.Key = window;
	for (size_t i = 0; i < 1024; i++) {
		WindowKeyEvents.Value.push_back(false);
	}
	AllWindowsKeyEvents.push_back(WindowKeyEvents);

	/* Binding Callback */
	glfwSetKeyCallback(window, Window::InputEvent_Callback);
}
void Window::ClearInput() { /* efficiently removes all elements with matching window value */
	for (size_t i = 0; i < AllWindowsKeyEvents.size(); i++) {
		NPair<GLFWwindow*, std::vector<bool>>& WindowKeyEvents = AllWindowsKeyEvents.at(i);
		if (WindowKeyEvents.Key == window) {
			/* Clearing KeyEvents */
			for (size_t i = 0 ; i < WindowKeyEvents.Value.size() ; i++) {
				WindowKeyEvents.Value.at(i) = false;
			}
			WindowKeyEvents.Value.clear();
			/* nulling Window reference */
			WindowKeyEvents.Key = nullptr;
			/* Removing WindowKeyEvents pair in AllWindowsKeyEvents */
			AllWindowsKeyEvents.erase(AllWindowsKeyEvents.begin() + i); /* removes the element pair at i index */
		}
	}
}

void Window::InputEvent_Callback(GLFWwindow* window, int Key, int Code, int Action, int Mode) {
	/* Immediately closing that window if escape key is pressed */
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	for (size_t i = 0; i < AllWindowsKeyEvents.size(); i++) {
		NPair<GLFWwindow*, std::vector<bool>>& WindowKeyEvents = AllWindowsKeyEvents.at(0);
		if (WindowKeyEvents.Key == window) {
			if (Action == GLFW_PRESS) {
				WindowKeyEvents.Value.at(Key) = true;
			}
			else if (Action == GLFW_RELEASE) {
				WindowKeyEvents.Value.at(Key) = false;
			}
		}
	}
}

std::vector<bool> Window::GetKeyEvents() const {
	for (size_t i = 0; i < AllWindowsKeyEvents.size(); i++) {
		NPair<GLFWwindow*, std::vector<bool>>& WindowKeyEvents = AllWindowsKeyEvents.at(i);
		if (window == WindowKeyEvents.Key) {
			return WindowKeyEvents.Value;
		}
	}
	std::vector<bool> EmptyKeys;
	std::cerr << "Unable to Find KeyEvents of the Window!" << std::endl;
	return EmptyKeys;
}