#include <iostream>

#include "Mesh.h"

Mesh::Mesh() :
	VAO{ 0 },
	IBO{ 0 },
	VBO{ 0 },
	IndicesCount{ 0 }
{ 
	std::cout << "Constructing Mesh" << std::endl;
}
Mesh::~Mesh() {
	ClearMesh(); /* even though we call clearmesh separately, we have to recall it in destructor just in case */
	std::cout << "Destroying Mesh" << std::endl;
}

void Mesh::CreateMesh(GLfloat* Vertices, GLuint SizeOfVertices, GLuint* Indices, GLuint SizeOfIndices) {
	IndicesCount = SizeOfIndices / sizeof(GLuint);

	/* Attribute */
	glGenVertexArrays(1, &VAO); /* creating one vertex array id */
	glBindVertexArray(VAO); /* activating the vertex array object, so statement linking magic works */

	/* Index Buffer */
	/* once we activate VAO and then IBO and then VBO, then IBO and VBO are linked to VAO, statement linking magic */
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); /* activating */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeOfIndices/* total size in bytes */, Indices, GL_STATIC_DRAW);

	/* Vertex Buffer */
	glGenBuffers(1, &VBO); /* creating one buffer id */
	glBindBuffer(GL_ARRAY_BUFFER, VBO); /* activating */
	glBufferData(GL_ARRAY_BUFFER, SizeOfVertices, Vertices, GL_STATIC_DRAW);
	/* Layout of Vertex Buffer */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0/* don't need stride i think */, nullptr); /* layout of our vertex attribute, don't need pointer since statement linking magic */
	glEnableVertexAttribArray(0);

	/* After setting up all VAO, IBO and VBO, we don't need Vertices and Indices anymore, means changing Vertices or Indices in later code won't effect existing objects */

	/* deactivating, so statement linking magic won't work */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::RenderMesh() {
	glBindVertexArray(VAO); /* activating vertex array to draw it */
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); /* no need i think, since drawing fine */

	/* Draws whatever that is currently activated in vertex array */
	glDrawElements(GL_TRIANGLES/* takes the indices as first 3 to draw */, IndicesCount/* total number of indices to draw */, GL_UNSIGNED_INT, nullptr); /* we don't need pointer, since VAO is activated in previous statement which VAO has link to IBO */

	/* Deactivating so we don't have problem in next statements */
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::ClearMesh() {
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	IndicesCount = 0;
}