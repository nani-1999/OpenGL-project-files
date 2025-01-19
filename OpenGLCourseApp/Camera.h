#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	~Camera();

	void UpdateCameraOrientation(GLfloat DeltaTime, GLfloat DeltaX, GLfloat DeltaY);
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

	/* Unit Vector */
	glm::mat<4, 4, GLfloat> CameraOrientation;

};

