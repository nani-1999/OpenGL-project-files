#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

static const glm::vec<3, GLfloat> WorldUpVector(0.f, 1.f, 0.f);

class Camera {
public:
	Camera();
	~Camera();

	void UpdateCameraLocation(GLfloat DeltaTime, const std::vector<bool>& KeyEvents);
	void UpdateCameraRotation(glm::vec<2, GLfloat> DeltaCursorPos);

	glm::mat<4, 4, GLfloat> GetCameraMatrix();

private:
	/* Camera Transform */
	glm::vec<3, GLfloat> Location, Rotation;

	/* Camera Sensitivity */
	glm::vec<2, GLfloat> Sensitivity;

	/* Movement Keys */
	GLenum ForwardKey, BackwardKey, RightKey, LeftKey, UpKey, DownKey;
};

