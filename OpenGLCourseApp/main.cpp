// OpenGL DataTypes
// GLint
// GLboolean { GL_TRUE, GL_FALSE }

#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Window Dimensions
const GLint WIDTH = 720, HEIGHT = 480;

GLuint VAO, VBO, Shader;

// Vertex Shader
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                              \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                        \n\
}";

void AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType) {
	/* creates a shader, compiles it and adds to a program*/

	// creates a shader and returns its id
	GLint CreatedShader = glCreateShader(ShaderType);

	// shader code
	const GLint CodeLength = strlen(ShaderCode);
	glShaderSource(CreatedShader, 1, &ShaderCode, &CodeLength);

	// shader compile
	glCompileShader(CreatedShader);

	// Checking for Error
	GLint result = 0;
	GLchar eLog[1024] = { "" };
	glGetShaderiv(CreatedShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(CreatedShader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Compiling Shader" << eLog << std::endl;
		return;
	}

	// attaching shader
	glAttachShader(ShaderProgram, CreatedShader);

	return;
}

void CompileShaders() {
	Shader = glCreateProgram(); // creates a program i.e., shader program and returns its id

	if (!Shader) {
		std::cout << "Failed to Create Shader Program" << std::endl;
		glfwTerminate();
		return;
	}

	// Vertex Shader
	AddShader(Shader, vShader, GL_VERTEX_SHADER);
	// Fragment Shader
	AddShader(Shader, fShader, GL_FRAGMENT_SHADER);

	// Checking for Error
	GLint result = 0;
	GLchar eLog[1024] = { "" };

	// Linking Shader Program
	glLinkProgram(Shader);
	// checking link status
	glGetProgramiv(Shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(Shader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Linking Program" << eLog << std::endl;
		return;
	}

	// Validating Shader Program
	glValidateProgram(Shader);
	// checking valid status
	glGetProgramiv(Shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(Shader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Validating Program" << eLog << std::endl;
		return;
	}
}

void CreateTriangle() {

	GLfloat vertices[] = {
		-1.f, -1.f, 0.f,
		 1.f, -1.f, 0.f,
		 0.f,  1.f, 0.f
	};

	// Attribute
	glGenVertexArrays(1, &VAO); /* creating one vertex array id */
	glBindVertexArray(VAO); /* creating vertext array and binding it to a vertex array id */

	// Buffer
	glGenBuffers(1, &VBO); /* creating one buffer id */
	glBindBuffer(GL_ARRAY_BUFFER, VBO); /* creating structure buffer and binding it to a buffer id */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Layout of Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); /* layout of our vertex attribute */
	glEnableVertexAttribArray(0);

	// clearing binds, so it won't effect "next statement connections"
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{
	// initializing GLFW
	if (!glfwInit()) {
		std::cout << "GLFW initialization falied!" << std::endl;
		glfwTerminate(); /* terminitaing glfw if we fail to initialize */
		return 1; /* unsuccessful return */
	}

	/* after this is glfw ready to be used */

	// setting up window properties
	// opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	// creating our glfw window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
	if (mainWindow == nullptr) {
		//std::cout << "Create Window Failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	// after this is window created successfully

	// getting available frame size to draw size information
	int bufferWidth, bufferHeight = 1;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// setting context for GLEW to use
	// setting up window for GLEW to use, incase if we have muliple GLFWwindow's
	// first we need to make sure a GLFWwindow is current context
	glfwMakeContextCurrent(mainWindow);

	// allowing glew to use modern features
	glewExperimental = GL_TRUE;

	// initializing GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// setting up desired viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	/* Printing out GL Version */
	std::cout << glGetString(GL_VERSION/*GL_SHADING_LANGUAGE_VERSION*/) << std::endl; // 4.6, major version: 4, minor version: 6

	// Creating Triangle
	CreateTriangle();
	// Compiling Shaders
	CompileShaders();

	// loop until glfw window close button is pressed
	// window doesn't close by default by pressing close button, so we have to check if closebutton is true or not
	while (!glfwWindowShouldClose(mainWindow)) {
		// getting use input events, can handle any input events on window
		glfwPollEvents();

		// clearing window
		// clearing to draw a new frame, preventing drawing on top of another/previous frame
		glClearColor(0.f, 0.f, 0.f, 1.f); //color data of the pixels, background resulting maybe
		glClear(GL_COLOR_BUFFER_BIT); // clearing only color data of the pixel, since each pixel has a lot of data like stencel, depth, color, etc

		// Shader
		glUseProgram(Shader);

		// Triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Shader
		glUseProgram(0); // unuse shader for the next statement code, maybe we use different shader in the next statements


		glfwSwapBuffers(mainWindow);
	}

	return 0;
}