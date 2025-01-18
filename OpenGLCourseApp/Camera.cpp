#include "Camera.h"
#include <iostream>

Camera::Camera() {
	//use normal glm::rotation on unit front vec
	std::cout << "Constructing Camera" << std::endl;

	CameraOrientation = glm::mat<4, 4, GLfloat>(1.f);
}
Camera::~Camera() {
	std::cout << "Destroying Camera" << std::endl;
}

void Camera::UpdateCameraOrientation(GLfloat DeltaTime, GLfloat xpos, GLfloat ypos) {
	glm::vec<3, GLfloat> MouseInput = glm::vec<3, GLfloat>(xpos, ypos, 1.f);
	CameraOrientation = glm::rotate(CameraOrientation, glm::radians<GLfloat>(DeltaTime), MouseInput);

	std::cout << CameraOrientation[0][0] << std::endl;
}