#pragma once

#include <string>

#include <GL/glew.h>

class Shader {
public:
	Shader();
	~Shader();

	void UseShader();
	void ClearShader();

	/* Creates a Shader, compiles it and adds to the Shader Program */
	void AddShader(const std::string ShaderPath, GLenum ShaderType);
	/* Links and Validates the Shader Program */
	void LinkAndValidate();

	/* Getting Shader Variable IDs */
	GLuint GetShaderUniformLocation(const GLchar* ShaderVariableName);

private:
	/* Shader Program */
	GLuint ShaderProgram;
};

