#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/glm.hpp"

#include <vector>

#include "Nani/NaniTypes.h"

std::vector<GLFWwindow*> WindowIndices;
std::vector<std::vector<bool>> KeyEvents;
std::vector<glm::vec<2, GLfloat>> MouseInput;

static std::vector<NPair<GLFWwindow*, std::vector<bool>>> AllWindowsKeyEvents; /* has reference to all GLFWwindow's and its key events, made for Input to use */

class Window {
public:
	Window(GLint Width, GLint Height, const GLchar* Title = "", GLFWwindow* SharedWindow = nullptr);
	~Window();

	/* Returns FramebufferSize of window */
	glm::vec<2, GLint> GetWindowFrameBufferSize() const;

	/* Returns Current Window */
	GLFWwindow* GetWindow() const { return window; }

	/* Context Current */
	void MakeCurrent();

	/* Clear Window */
	void ClearWindow();

	/* Input */
	/* Returns KeyEvents of GLFWwindow */
	std::vector<bool> GetKeyEvents() const;

private:
	/* Window */
	GLFWwindow* window = nullptr;
	glm::vec<2, GLint> WindowSize;
	const GLchar* WindowTitle;

	/* Input */
	void InitInput(); /* Initializing Window Input */
	void ClearInput(); /* to remove window input */
	/* Callback that is automatically called by GLFW */
	static void InputEvent_Callback(GLFWwindow* window, int Key, int Code, int Action, int Mode); /* must be static */
};