#include <iostream>
#include "Window.h"

Window::Window(GLint Width, GLint Height, const GLchar* Title, GLFWwindow* SharedWindow) {
	/* @LOG */
	std::cout << "Constructing Window: " << Title << " " << Width << " x " << Height << std::endl;

	/* Setting up window properties */
	/* opengl version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	/* backwards compatibility  */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code should run or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	WindowSize = glm::vec<2, GLint>(Width, Height);
	WindowTitle = Title;

	window = glfwCreateWindow(Width, Height, Title, nullptr, SharedWindow);
	if (!window) {
		std::cerr << "Failed to Create Window!" << std::endl;
		glfwTerminate();
		return;
	}

	/* setting this Window as GLFWwindow user pointer, so we can access it later */
	glfwSetWindowUserPointer(window, this);

	/* Input */
	InitInput();
}
Window::~Window() {
	std::cout << "Destroying Window" << std::endl;

	ClearWindow();
}
void Window::InitInput() {
	/* making space of keys */
	for (size_t i = 0; i < 1024; i++) {
		KeyEvents.push_back(false);
	}
	/* emptying Cursor Positions */
	CurrentCursorPos, PreviousCursorPos, DeltaCursorPos = glm::vec<2, GLfloat>(0.f);

	/*  */
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Binding Callbacks */
	glfwSetKeyCallback(window, Window::InputEvent_Callback);
	glfwSetCursorPosCallback(window, Window::CursorPos_Callback);
}

void Window::Tick(GLfloat DeltaTime) {
	CalculateDeltaCursorPos();
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

void Window::ClearInput() {
	/* Erasing KeyEvents */
	for (size_t i = 0; i < KeyEvents.size(); i++) {
		KeyEvents.at(i) = false;
	}
	KeyEvents.clear();
	CurrentCursorPos, PreviousCursorPos, DeltaCursorPos = glm::vec<2, GLfloat>(0.f);
}

void Window::InputEvent_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key < 0 || key > 1024) return;

	Window* Obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
	Obj->KeyEvents.at(key) = action;
}
void Window::CursorPos_Callback(GLFWwindow* window, double xpos, double ypos) {

	Window* Obj = static_cast<Window*>(glfwGetWindowUserPointer(window));
	Obj->CurrentCursorPos.x = (float)xpos;
	Obj->CurrentCursorPos.y = (float)ypos;
}

void Window::CalculateDeltaCursorPos() {
	/* Delta Cursor Pos */
	DeltaCursorPos.x = CurrentCursorPos.x - PreviousCursorPos.x;
	DeltaCursorPos.y = CurrentCursorPos.y - PreviousCursorPos.y;

	PreviousCursorPos.x = CurrentCursorPos.x;
	PreviousCursorPos.y = CurrentCursorPos.y;
}

const std::vector<bool>& Window::GetKeyEvents() const { 
	return KeyEvents; 
}
const glm::vec<2, GLfloat>& Window::GetCursorPos() const {
	return CurrentCursorPos;
}
const glm::vec<2, GLfloat>& Window::GetDeltaCursorPos() const {
	return DeltaCursorPos;
}