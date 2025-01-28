#include <iostream>

#include "Camera.h"
#include "Nani/NaniMath.h"

// transformation on matrix are only used once, since it has += behaviour
// must have native location, rotation, scale
Camera::Camera() {
	//use normal glm::rotation on unit front vec
	std::cout << "Constructing Camera" << std::endl;

	Location = Rotation = glm::vec<3, GLfloat>(0.f);

	Sensitivity = glm::vec<2, GLfloat>(0.05f);

	ForwardKey = GLFW_KEY_W;
	BackwardKey = GLFW_KEY_S;
	RightKey = GLFW_KEY_D;
	LeftKey = GLFW_KEY_A;
	UpKey = GLFW_KEY_E;
	DownKey = GLFW_KEY_Q;
}
Camera::~Camera() {
	std::cout << "Destroying Camera" << std::endl;
}

void Camera::UpdateCameraLocation(GLfloat DeltaTime, const std::vector<bool>& KeyEvents) {
	glm::vec<3, GLfloat> ForwardVector(0.f);
	ForwardVector.x = glm::cos(glm::radians<GLfloat>(Rotation.x)) * glm::sin(glm::radians<GLfloat>(Rotation.y));
	ForwardVector.y = -glm::sin(glm::radians<GLfloat>(Rotation.x));
	ForwardVector.z = -glm::cos(glm::radians<GLfloat>(Rotation.x)) * glm::cos(glm::radians<GLfloat>(Rotation.y));

	glm::vec<3, GLfloat> RightVector(0.f); // = glm::cross(ForwardVector, WorldUpVector); /* cross product working but increment is low when totally looking down */
	RightVector.x = glm::cos(glm::radians<GLfloat>(Rotation.y));
	RightVector.y = 0.f;
	RightVector.z = glm::sin(glm::radians<GLfloat>(Rotation.y));
	//glm::vec<3, GLfloat> UpVector = glm::cross(ForwardVector, RightVector); /* using world up vector instead */

	glm::vec<3, GLfloat> EmptyVector = glm::vec<3, GLfloat>(0.f);

	/* negating, since camera is stationary and the world should orient opposite */
	Location -= ((KeyEvents.at(ForwardKey)) ? ForwardVector : (KeyEvents.at(BackwardKey)) ? -ForwardVector : EmptyVector) * DeltaTime;
	Location -= ((KeyEvents.at(RightKey))   ? RightVector   : (KeyEvents.at(LeftKey))     ? -RightVector   : EmptyVector) * DeltaTime;
	Location -= ((KeyEvents.at(UpKey))      ? WorldUpVector : (KeyEvents.at(DownKey))     ? -WorldUpVector : EmptyVector) * DeltaTime; 
}
void Camera::UpdateCameraRotation(glm::vec<2, GLfloat> DeltaCursorPos) {
	Rotation.x = glm::clamp<GLfloat>(Nani::NormalizeAngle(Rotation.x + DeltaCursorPos.y * Sensitivity.x), -89.f, 89.f);
	Rotation.y = Nani::NormalizeAngle(Rotation.y + DeltaCursorPos.x * Sensitivity.y);
}

glm::mat<4, 4, GLfloat> Camera::GetCameraMatrix() {
	glm::mat<4, 4, GLfloat> CameraMatrix(1.f);
	/* Rotation */
	CameraMatrix = glm::rotate(CameraMatrix, glm::radians<GLfloat>(Rotation.x), glm::vec<3, GLfloat>(1.f, 0.f, 0.f));
	CameraMatrix = glm::rotate(CameraMatrix, glm::radians<GLfloat>(Rotation.y), glm::vec<3, GLfloat>(0.f, 1.f, 0.f));
	/* Translation */
	CameraMatrix = glm::translate(CameraMatrix, Location);

	return CameraMatrix;
}
