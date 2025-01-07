#include <iostream>
#include <string>
#include <fstream>

#include "Shader.h"
#include "Nani/NaniUtility.h"

Shader::Shader() :
	ShaderProgram{ 0 }
{
	std::cout << "Constructing Shader" << std::endl;

	/* Creates a Program i.e., Shader Program on Construction */
	ShaderProgram = glCreateProgram();
	if (!ShaderProgram) {
		std::cerr << "Falied to create Shader Program" << std::endl;
		return;
	}
}
Shader::~Shader() {
	/* Clearing Shader on Destruction, just in case if ClearShader() is not called properly */
	ClearShader();
	std::cout << "Destroying Shader" << std::endl;
}

void Shader::AddShader(const std::string ShaderPath, GLenum ShaderType) {
	/* Creates a shader and returns its id */
	GLint CreatedShader = glCreateShader(ShaderType);

	/* Shader Code */
	std::string ShaderData; 
	ReadFile(ShaderPath, ShaderData);
	const char* ShaderCode = ShaderData.c_str(); /* converting to c string, since glshadersource requires turdy c type */
	const GLint ShaderCodeLength = strlen(ShaderCode);
	if (ShaderCodeLength == 0) {
		std::cerr << "Unable to Read Shader File" << std::endl;
		return;
	}

	/* Creating Shader source in Shader */
	glShaderSource(CreatedShader, 1, &ShaderCode, &ShaderCodeLength);

	/* Compiling Shader */
	glCompileShader(CreatedShader);

	/* Checking for Error */
	GLint result = 0;
	GLchar eLog[1024] = { "" };
	glGetShaderiv(CreatedShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(CreatedShader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Compiling Shader" << eLog << std::endl;
		return;
	}

	/* Attaching Shader */
	glAttachShader(ShaderProgram, CreatedShader);

	return;
}

void Shader::LinkAndValidate() {
	/* Checking for Errors */
	GLint result = 0;
	GLchar eLog[1024] = { "" };

	/* Linking Shader Program */
	glLinkProgram(ShaderProgram);
	/* checking link status */
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderProgram, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error Linking Program" << eLog << std::endl;
		return;
	}

	/* Validating Shader Program */
	glValidateProgram(ShaderProgram);
	/* checking valid status */
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(ShaderProgram, sizeof(eLog), nullptr, eLog);
		std::cerr << "Error Validating Program" << eLog << std::endl;
		return;
	}
}

void Shader::UseShader() {
	/* Uses the Shader Program in next statements */
	glUseProgram(ShaderProgram);
}
void Shader::ClearShader() {
	/* Deletes the Shader from Graphics memory */
	if (ShaderProgram != 0) {
		glDeleteProgram(ShaderProgram);
		ShaderProgram = 0;
	}
}

GLuint Shader::GetShaderUniformLocation(const GLchar* ShaderVariableName) {
	/* Getting Id of Shader Program variables */
	return glGetUniformLocation(ShaderProgram, ShaderVariableName);
}