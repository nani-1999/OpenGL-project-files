#include <iostream>
#include "Window.h"

Window::Window(GLint Width, GLint Height, const GLchar* Title) :
	WindowSize{ glm::vec<2, GLint>(Width, Height) },
	WindowTitle{ Title }
{
	std::cout << "Constructing Window: " << Width << " x " << Height << " " << Title << std::endl;

	/* Setting up window properties */
	/* opengl version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	/* backwards compatibility  */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code should run or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to Create Window!" << std::endl;
		glfwTerminate();
		return;
	}

	/* setting context for GLEW to use */
	/* setting up window for GLEW to use, incase if we have muliple GLFWwindow's */
	/* first we need to make sure a GLFWwindow is current context */
	glfwMakeContextCurrent(window);
}
Window::~Window() {
	std::cout << "Destroying Window" << std::endl;

	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

glm::vec<2, GLint> Window::GetWindowFrameBufferSize() const {
	glm::vec<2, GLint> BufferSize{ 1 };
	glfwGetFramebufferSize(window, &BufferSize.x, &BufferSize.y);
	return BufferSize;
}