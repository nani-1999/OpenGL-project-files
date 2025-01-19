#include <iostream>

#include "Camera.h"
#include "Nani/NaniUtility.h"

Camera::Camera() {
	//use normal glm::rotation on unit front vec
	std::cout << "Constructing Camera" << std::endl;

	CameraOrientation = glm::mat<4, 4, GLfloat>(1.f);
}
Camera::~Camera() {
	std::cout << "Destroying Camera" << std::endl;
}

void Camera::UpdateCameraOrientation(GLfloat DeltaTime, GLfloat DeltaX, GLfloat DeltaY) {
	glm::vec<3, GLfloat> MouseInput = glm::vec<3, GLfloat>(DeltaX, DeltaY, 1.f);
	CameraOrientation = glm::rotate(CameraOrientation, glm::radians<GLfloat>(1), MouseInput);
}