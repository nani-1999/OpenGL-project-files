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

	void UpdateCameraLocation(bool WKey, bool SKey, bool DKey, bool AKey, bool EKey, bool QKey);
	void UpdateCameraRotation(glm::vec<2, GLfloat> DeltaCursorPos);

	glm::mat<4, 4, GLfloat> GetCameraMatrix();
private:

	/* Camera Transform */
	glm::vec<3, GLfloat> Location, Rotation;
};

