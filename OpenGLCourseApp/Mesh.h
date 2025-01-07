#pragma once

#include <GL/glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();

	/* Creates a Mesh */
	/* Size of Vertices in Bytes */
	void CreateMesh(GLfloat* Vertices, GLuint NumberOfVertices, GLuint* Indices, GLuint NumberOfIndices);
	/* Draws a Mesh to the screen */
	void RenderMesh();
	/* deletes the mesh from graphics card */
	void ClearMesh();

private:
	/* IDs */
	GLuint VAO, IBO, VBO;

	/* Number of Indices */
	GLuint IndicesCount;
};

