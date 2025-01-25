#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

static const glm::vec<3, GLfloat> WorldUpVector(0.f, 1.f, 0.f);

class Camera {
public:
	Camera();
	~Camera();

	void UpdateCameraOrientation(bool WKey, bool SKey, bool DKey, bool AKey, bool EKey, bool QKey);

	glm::mat<4, 4, GLfloat> GetCameraMatrix();
private:
	///* Unit Vectors */
	//glm::vec<3, GLfloat> Forward;
	//glm::vec<3, GLfloat> Right;
	//glm::vec<3, GLfloat> Up;
	//glm::vec<3, GLfloat> Direction;
	///* Position */
	//glm::vec<3, GLfloat> Location;
	///* Rotation */
	//glm::vec<3, GLfloat> Rotation; /* Pitch = Y, Yaw = Z, Roll = X */

	/* Camera Transform */
	glm::vec<3, GLfloat> Location, Rotation;
};

