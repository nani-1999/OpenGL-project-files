#include <iostream>

#include "Camera.h"
#include "Nani/NaniDebug.h"
// transformation on matrix are only used once, since it has += behaviour
// must have native location, rotation, scale
Camera::Camera() {
	//use normal glm::rotation on unit front vec
	std::cout << "Constructing Camera" << std::endl;

	CameraMatrix = glm::mat<4, 4, GLfloat>(1.f);
	Location = glm::vec<3, GLfloat>(0.f);
	Rotation = glm::vec<3, GLfloat>(0.f, 0.f, 0.f);
	//Direction = glm::vec<3, GLfloat>
	//CameraMatrix = glm::translate(CameraMatrix, glm::vec<3, GLfloat>(0.f, 0.f, -5.f));
	//CameraMatrix = glm::rotate(CameraMatrix, glm::radians(45.f), glm::vec<3, GLfloat>(1.f, 0.f, 0.f));
}
Camera::~Camera() {
	std::cout << "Destroying Camera" << std::endl;
}

void Camera::UpdateCameraOrientation(bool WKey, bool SKey, bool DKey, bool AKey, bool EKey, bool QKey) {
	//if (Wkey) {
	//	CameraOrientation = glm::translate(CameraOrientation, glm::vec<3, GLfloat>(0.f, 0.f, 0.001f));
	//}
	//if (SKey) {
	//	CameraOrientation = glm::translate(CameraOrientation, glm::vec<3, GLfloat>(0.f, 0.f, -0.001f));
	//}
	GLfloat Sine = glm::sin(glfwGetTime());

	/* GetForwardVector()
	* const Vec(0,0,1); since z is the forward in this dimensions
	* fwvec;
	* fwvec.x =;
	* fwvec.y =;
	* fwvec.z =;
	* return fwvec;
	*/

	CameraMatrix = glm::mat<4, 4, GLfloat>(1.f);

	

	//if (WKey) {
	//	Location -= Forward * 0.001f;
	//}
	//if (SKey) {
	//	Location += Forward * 0.001f;
	//}
	//CameraMatrix = glm::translate(CameraMatrix, Location);

	//glm::vec<3, GLfloat> Translate(0.f);
	//Translate.z = 0.001f * (WKey ? 1.f : SKey ? -1.f : 0.f);                   // see look at code of unreal engine
	//Translate.x = 0.001f * (DKey ? -1.f : AKey ? 1.f : 0.f);
	//Translate.y = 0.001f * (EKey ? -1.f : QKey ? 1.f : 0.f);
	//CameraMatrix = glm::translate(CameraMatrix, Translate);

	// Matrix4 * Vec4
	// Mat4 Model
	// Vec3 Location
	// Vec3 Rotation/Direction
	// Vec3 Scale
	// Model * Location/Rotation/Scale

	//CameraMatrix = glm::translate(CameraMatrix, glm::vec<3, GLfloat>(0.f, 0.f, -5.f * Sine));
	//CameraMatrix = glm::rotate(CameraMatrix, glm::radians(45.f), glm::vec<3, GLfloat>(1.f, 0.f, 0.f));
}