#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Nani/NaniTypes.h"



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
	/* Returns KeyEvents of this Window */
	const std::vector<bool>& GetKeyEvents() const;

private:
	/* Window */
	GLFWwindow* window = nullptr;
	glm::vec<2, GLint> WindowSize;
	const GLchar* WindowTitle;

	/* Input */
	static std::vector<NPair<GLFWwindow*, std::vector<bool>>> AllWindowsKeyEvents; /* has window and its key events, made for Input to use */
	static void InitWindowInput(GLFWwindow* NewWindow); /* Initializing Window Input */
	static void RemoveWindowInput(GLFWwindow* RemoveWindow); /* to remove window input */
	/* Callback that is automatically called by GLFW */
	static void InputEvent_Callback(GLFWwindow* window, int Key, int Code, int Action, int Mode); /* must be static */
};

