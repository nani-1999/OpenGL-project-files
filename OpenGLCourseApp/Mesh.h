#pragma once

#include <iostream>
#include <GL/glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();

	/* Creates a Mesh */
	/* Size of Vertices in Bytes */
	void CreateMesh(GLfloat* Vertices, GLuint SizeOfVertices, GLint* Indices, GLuint SizeOfIndices);
	/* Draws a Mesh to the screen */
	void RenderMesh();
	/* deletes the mesh from graphics card */
	void ClearMesh();

private:
	/* IDs */
	/* Vertex Array Object */
	GLuint VAO, EBO, VBO;
	GLuint IndicesCount;
};

