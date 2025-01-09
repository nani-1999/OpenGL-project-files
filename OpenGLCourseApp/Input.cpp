#include "Input.h"
#include <iostream>

Input::Input() {
	std::cout << "Constructing Input" << std::endl;
}
Input::~Input() {
	std::cout << "Destroying Input" << std::endl;
}

//void Input::BindKeyInputs(GLFWwindow* window) {
//	 
//	//glfwSetKeyCallback(window, InputEvent_Callback);
//}
//
//
//void Input::InputEvent_Callback(GLFWwindow* window, int Key, int Code, int Action, int Mode) {
//	if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//
//	if (Key >= 0 && Key <= 1024) {
//		if (Action == GLFW_PRESS) {
//			//bKeyStates[Key] = GLFW_TRUE;
//		}
//	}
//}