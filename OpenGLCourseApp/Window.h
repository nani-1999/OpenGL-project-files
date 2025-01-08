#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {
public:
	Window(GLint Width, GLint Height, const GLchar* Title = "");
	~Window();

	/* Returns FramebufferSize of window */
	glm::vec<2, GLint> GetWindowFrameBufferSize() const;

	/* Returns Current Window */
	GLFWwindow* GetWindow() const { return window; }

private:
	GLFWwindow* window = nullptr;

	glm::vec<2, GLint> WindowSize;
	const GLchar* WindowTitle;
};

