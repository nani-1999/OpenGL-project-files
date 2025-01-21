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

void Window::Tick(GLfloat DeltaTime) {
	/* Delta Cursor Pos */
	GLuint WindowIndex = GetWindowIndex((window));

	glm::vec<2, GLfloat>& PreviousPos = PreviousCursorPos.at(WindowIndex);
	glm::vec<2, GLfloat>& CurrentPos = CurrentCursorPos.at(WindowIndex);

	glm::vec<2, GLfloat>& DeltaPos = DeltaCursorPos.at(WindowIndex);
	DeltaPos.x = CurrentPos.x - PreviousPos.x;
	DeltaPos.y = CurrentPos.y - PreviousPos.y;

	PreviousPos.x = CurrentPos.x;
	PreviousPos.y = CurrentPos.y;
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
// rename to cursor pos
void Window::InitInput() {
	/* Creating Keys */
	std::vector<bool> WindowKeyEvents;
	for (size_t i = 0; i < 1024; i++) {
		WindowKeyEvents.push_back(false);
	}
	/* Creating Previous CursorPos */
	glm::vec<2, GLfloat> PreviousPos(0.f);
	/* Creating Current CursorPos */
	glm::vec<2, GLfloat> CurrentPos(0.f); /* this shit is not 0 by default at declaration stage, so initialize it to zero */
	/* Creating Delta CursorPos */
	glm::vec<2, GLfloat> DeltaPos(0.f);

	/* Pushing */
	WindowIndices.push_back(window);
	KeyEvents.push_back(WindowKeyEvents);
	PreviousCursorPos.push_back(PreviousPos);
	CurrentCursorPos.push_back(CurrentPos);
	DeltaCursorPos.push_back(DeltaPos);

	/* Binding Callbacks */
	glfwSetKeyCallback(window, Window::InputEvent_Callback);
	glfwSetCursorPosCallback(window, Window::CursorPos_Callback);
}
void Window::ClearInput() { /* efficiently removes all elements with matching window index */
	/* Getting the Index of GLFWwindow */
	GLuint WindowIndex = GetWindowIndex(window);

	/*  Erasing GLFWwindow*/
	WindowIndices.at(WindowIndex) = nullptr; /* nulling before erasing */
	WindowIndices.erase(WindowIndices.begin() + WindowIndex);
	
	/* Erasing KeyEvents */
	std::vector<bool>& WindowKeyEvents = KeyEvents.at(WindowIndex);
	for (size_t i = 0; i < WindowKeyEvents.size(); i++) { /* falsing out before erasing */
		WindowKeyEvents.at(i) = false;
	}
	WindowKeyEvents.clear(); 
	KeyEvents.erase(KeyEvents.begin() + WindowIndex);

	/* Erasing Previous Cursor Pos */
	glm::vec<2, GLfloat>& PreviousPos = PreviousCursorPos.at(WindowIndex);
	PreviousPos = glm::vec<2, GLfloat>(0.f); /* zeroing out before erasing */
	PreviousCursorPos.erase(PreviousCursorPos.begin() + WindowIndex);
	/* Erasing Current Cursor Pos */
	glm::vec<2, GLfloat>& CurrentPos = CurrentCursorPos.at(WindowIndex);
	CurrentPos = glm::vec<2, GLfloat>(0.f); /* zeroing out before erasing */
	CurrentCursorPos.erase(CurrentCursorPos.begin() + WindowIndex);
}

void Window::InputEvent_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key < 0 || key > 1024) return;

	KeyEvents.at(GetWindowIndex(window)).at(key) = action;
}
const std::vector<bool>& Window::GetKeyEvents() const { 
	return KeyEvents.at(GetWindowIndex(window)); 
}

void Window::CursorPos_Callback(GLFWwindow* window, double xpos, double ypos) {
	glm::vec<2, GLfloat>& CurrentPos = CurrentCursorPos.at(GetWindowIndex(window));
	CurrentPos.x = (float)xpos;
	CurrentPos.y = (float)ypos;
}
const glm::vec<2, GLfloat>& Window::GetCursorPos() const {
	return CurrentCursorPos.at(GetWindowIndex(window));
}
const glm::vec<2, GLfloat>& Window::GetDeltaCursorPos() const {
	return DeltaCursorPos.at(GetWindowIndex(window));
}