#include "Mesh.h"

Mesh::Mesh() :
	VAO{ 0 },
	EBO{ 0 },
	VBO{ 0 },
	IndicesCount{ 0 }
{ 
	std::cout << "Constructing Mesh" << std::endl;
}
Mesh::~Mesh() { std::cout << "Destroying Mesh" << std::endl; }

void Mesh::CreateMesh(GLfloat* Vertices, GLuint SizeOfVertices, GLint* Indices, GLuint SizeOfIndices) {
	IndicesCount = SizeOfIndices / sizeof(GLuint);
}
void Mesh::RenderMesh() {

}
void Mesh::ClearMesh() {

}