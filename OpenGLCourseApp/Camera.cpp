#include <iostream>

#include "Camera.h"
#include "Nani/NaniDebug.h"
// transformation on matrix are only used once, since it has += behaviour
// must have native location, rotation, scale
Camera::Camera() {
	//use normal glm::rotation on unit front vec
	std::cout << "Constructing Camera" << std::endl;

	Location = glm::vec<3, GLfloat>(0.f);
	Rotation = glm::vec<3, GLfloat>(0.f, 0.f, 0.f);
	//Direction = glm::vec<3, GLfloat>
	//CameraMatrix = glm::translate(CameraMatrix, glm::vec<3, GLfloat>(0.f, 0.f, -5.f));
	//CameraMatrix = glm::rotate(CameraMatrix, glm::radians(45.f), glm::vec<3, GLfloat>(1.f, 0.f, 0.f));
}
Camera::~Camera() {
	std::cout << "Destroying Camera" << std::endl;
}

void Camera::UpdateCameraLocation(bool WKey, bool SKey, bool DKey, bool AKey, bool EKey, bool QKey) {
	glm::vec<3, GLfloat> ForwardVector(0.f);
	ForwardVector.x = glm::cos(glm::radians<GLfloat>(Rotation.x)) * glm::sin(glm::radians<GLfloat>(Rotation.y));
	ForwardVector.y = -glm::sin(glm::radians<GLfloat>(Rotation.x));
	ForwardVector.z = glm::cos(glm::radians<GLfloat>(Rotation.x)) * glm::cos(glm::radians<GLfloat>(Rotation.y));

	glm::vec<3, GLfloat> RightVector = glm::cross(ForwardVector, WorldUpVector);
	glm::vec<3, GLfloat> UpVector = glm::cross(ForwardVector, RightVector);

	if (WKey || SKey) {
		Location.z += (WKey) ? 1.f : (SKey) ? -1.f : 0.f;
	}
	if (DKey || AKey) {
		Location.x += (DKey) ? 1.f : (AKey) ? -1.f : 0.f;
	}
	if (EKey || QKey) {
		Location.y += (EKey) ? 1.f : (QKey) ? -1.f : 0.f;
	}
}
void Camera::UpdateCameraRotation(glm::vec<2, GLfloat> DeltaCursorPos) {
}

glm::mat<4, 4, GLfloat> Camera::GetCameraMatrix() {
	return glm::mat4(1.f);
}
