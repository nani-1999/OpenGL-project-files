#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

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
	const std::vector<bool>& GetKeyEvents() const;
	/* Returns MouseInputs of GLFWwindow */
	const glm::vec<2, GLfloat>& GetCursorPos() const;
	/* Returns DeltaMouseInputs of GLFWindow */
	const glm::vec<2, GLfloat>& GetDeltaCursorPos() const;

	/* Window Tick */
	void Tick(GLfloat DeltaTime);

private:
	/* Window */
	GLFWwindow* window = nullptr;
	glm::vec<2, GLint> WindowSize;
	const GLchar* WindowTitle;

	/* Input */
	std::vector<bool> KeyEvents;
	glm::vec<2, GLfloat> CurrentCursorPos;
	glm::vec<2, GLfloat> PreviousCursorPos;
	glm::vec<2, GLfloat> DeltaCursorPos;

	/* Input */
	void InitInput(); /* Initializing Window Input */
	void ClearInput(); /* to remove window input */
	/* Callbacks */
	static void InputEvent_Callback(GLFWwindow* window, int key, int scancode, int action, int mods); /* must be static */
	static void CursorPos_Callback(GLFWwindow* window, double xpos, double ypos);

	/* Delta */
	void CalculateDeltaCursorPos();
};