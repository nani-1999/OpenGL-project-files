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
	InitWindowInput(window);
}
Window::~Window() {
	std::cout << "Destroying Window" << std::endl;

	ClearWindow();
}

void Window::InitWindowInput(GLFWwindow* NewWindow) {
	NPair<GLFWwindow*, std::vector<bool>> WindowKeyEvents;
	WindowKeyEvents.Key = NewWindow;
	for (int i = 0; i < 1024; i++) {
		WindowKeyEvents.Value.push_back(false);
	}
	AllWindowsKeyEvents.push_back(WindowKeyEvents);
}
void Window::RemoveWindowInput(GLFWwindow* RemoveWindow) { /* efficiently removes all elements with matching value */
	for (int i = 0; i < AllWindowsKeyEvents.size() ; i++) {
		NPair<GLFWwindow*, std::vector<bool>>& WindowKeyEvents = AllWindowsKeyEvents.at(i);
		if (WindowKeyEvents.Key == RemoveWindow) {
			/* Clearing KeyEvents */
			for (int i = 0 ; i < WindowKeyEvents.Value.size() ; i++) {
				WindowKeyEvents.Value.at(i) = false;
			}
			WindowKeyEvents.Value.clear();
			/* nulling Window reference */
			WindowKeyEvents.Key = nullptr;
			/* Removing WindowKeyEvents pair in AllWindowsKeyEvents */
			AllWindowsKeyEvents.erase(AllWindowsKeyEvents.begin() + i); /* removes the element at i index */
		}
	}
}

void Window::MakeCurrent() {
	/* setting context for GLEW to use */
	/* setting up window for GLEW to use, incase if we have muliple GLFWwindow's */
	/* first we need to make sure a GLFWwindow is current context */
	glfwMakeContextCurrent(window);
}

void Window::ClearWindow() {
	/* Clearing Input */
	RemoveWindowInput(window);
	/* Destroying Window */
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

const std::vector<bool>& Window::GetKeyEvents() const {
	for (int i = 0; i < AllWindowsKeyEvents.size(); i++) {
		NPair<GLFWwindow*, std::vector<bool>>& WindowKeyEvents = AllWindowsKeyEvents.at(i);
		if (window == WindowKeyEvents.Key) {
			return WindowKeyEvents.Value;
		}
	}
}

void Window::InputEvent_Callback(GLFWwindow* window, int Key, int Code, int Action, int Mode) {
	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

}

glm::vec<2, GLint> Window::GetWindowFrameBufferSize() const {
	glm::vec<2, GLint> BufferSize{ 1 };
	glfwGetFramebufferSize(window, &BufferSize.x, &BufferSize.y);
	return BufferSize;
}