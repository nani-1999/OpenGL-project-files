// OpenGL DataTypes
// GLint
// GLboolean { GL_TRUE, GL_FALSE }
//gl_Position = vec4(Scale * pos.x + (XMove * (Scale - 1.f)), Scale * pos.y, pos.z, 1.0); // vertex shader
//colour = vec4(1.0, 0.0, 0.0, 1.0); // fragment shader

#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Window Dimensions */
const GLint WIDTH = 720, HEIGHT = 480;

GLuint VAO, VBO, Shader, /*XMoveId,*/ UniformModel, IBO, UniformProjection;

GLboolean Direction;
GLfloat MoveXOffset = 0.f, InterpSpeed = 0.01f, Radian = glm::radians<GLfloat>(45)/* One Radian = PI/180 */, RotateInterp = 0.f;

/* Vertex Shader */
/* here pos is absolute value, we only updating it with model, so the color representation is connstantly same even when transforming */
/* vCol will be passed out to the other shader, other shader with same variable name receives it */
static const char* vShader = "                                                                \n\
#version 330                                                                                  \n\
                                                                                              \n\
layout (location = 0) in vec3 pos;											                  \n\
out vec4 vCol;			                                                                      \n\
			                                                                                  \n\
//uniform float XMove;			                                                              \n\
//uniform float Scale = 0.3f;                                                                 \n\
uniform mat4 Model;                                                                           \n\
uniform mat4 Projection;                                                                                              \n\
                                                                                              \n\
void main()                                                                                   \n\
{                                                                                             \n\
    gl_Position = Projection * Model * vec4(pos, 1.0f);                                                    \n\
	vCol = vec4(clamp(pos, 0.f, 1.f), 1.f);                                                   \n\
}";

/* Fragment Shader */
static const char* fShader = "           \n\
#version 330                             \n\
                                         \n\
out vec4 colour;                         \n\
in vec4 vCol;                            \n\
                                         \n\
void main()                              \n\
{                                        \n\
    colour = vCol;                       \n\
}";

void AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType) {
	/* Creates a shader and returns its id */
	GLint CreatedShader = glCreateShader(ShaderType);

	/* Shader Code */
	const GLint CodeLength = strlen(ShaderCode);
	glShaderSource(CreatedShader, 1, &ShaderCode, &CodeLength);

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

void CompileShaders() {
	Shader = glCreateProgram(); /* creates a program i.e., shader program and returns its id */

	if (!Shader) {
		std::cout << "Failed to Create Shader Program" << std::endl;
		glfwTerminate();
		return;
	}

	/* Vertex Shader */
	AddShader(Shader, vShader, GL_VERTEX_SHADER);

	/* Fragment Shader */
	AddShader(Shader, fShader, GL_FRAGMENT_SHADER);

	/* Checking for Errors */
	GLint result = 0;
	GLchar eLog[1024] = { "" };

	/* Linking Shader Program */
	glLinkProgram(Shader);
	/* checking link status */
	glGetProgramiv(Shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(Shader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Linking Program" << eLog << std::endl;
		return;
	}

	/* Validating Shader Program */
	glValidateProgram(Shader);
	/* checking valid status */
	glGetProgramiv(Shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(Shader, sizeof(eLog), nullptr, eLog);
		std::cout << "Error Validating Program" << eLog << std::endl;
		return;
	}

	/* Getting Id of Shader Program variables */
	//XMoveId = glGetUniformLocation(Shader, "XMove");
	UniformModel = glGetUniformLocation(Shader, "Model");
	UniformProjection = glGetUniformLocation(Shader, "Projection");
}

void CreateTriangle() {

	GLuint Indices[] = {
		1, 2, 0,
		3, 6, 2,
		7, 4, 6,
		5, 0, 4,
		6, 0, 2,
		3, 5, 7,
		1, 3, 2,
		3, 7, 6,
		7, 5, 4,
		5, 1, 0,
		6, 4, 0,
		3, 1, 5
	};

	GLfloat Vertices[] = {
		- 1.f, - 1.f, 1.f,
		- 1.f, 1.f, 1.f,
		- 1.f, - 1.f, - 1.f,
		- 1.f, 1.f, - 1.f,
		1.f, - 1.f, 1.f,
		1.f, 1.f, 1.f,
		1.f, - 1.f, - 1.f,
		1.f, 1.f, - 1.f,
	};


	/* Attribute */
	glGenVertexArrays(1, &VAO); /* creating one vertex array id */
	glBindVertexArray(VAO); /* activating the vertex array object, so statement linking magic works */

	/* Index Buffer */
	/* once we activate VAO and then IBO and then VBO, then IBO and VBO are linked to VAO, statement linking magic */
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); /* activating */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices)/* total size in bytes */, Indices, GL_STATIC_DRAW);

	/* Vertex Buffer */
	glGenBuffers(1, &VBO); /* creating one buffer id */
	glBindBuffer(GL_ARRAY_BUFFER, VBO); /* activating */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	/* Layout of Vertex Buffer */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0/* don't need stride i think */, nullptr); /* layout of our vertex attribute, don't need pointer since statement linking magic */
	glEnableVertexAttribArray(0);

	/* After setting up all VAO, IBO and VBO, we don't need Vertices and Indices anymore, means changing Vertices or Indices in later code won't effect existing objects */

	/* deactivating, so statement linking magic won't work */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int mainOLD()
{
	/* initializing GLFW */
	if (!glfwInit()) {
		std::cout << "GLFW initialization falied!" << std::endl;
		glfwTerminate(); /* terminitaing glfw if we fail to initialize */
		return 1; /* unsuccessful return */
	}

	/* after this is glfw ready to be used */

	/* Setting up window properties */
	/* opengl version */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* what to alter and value */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); /* so its 3.3 version */
	/* backwards compatibility  */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); /* core profile = no backwards compatibility, means no depricated code should run or else throw error */
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* forward compact, means upto date code */

	/* Creating our glfw window */
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
	if (mainWindow == nullptr) {
		//std::cout << "Create Window Failed!" << std::endl;
		glfwTerminate();
		return 1;
	}

	/* after this is window created successfully */

	/* Getting available frame size to draw size information */
	int bufferWidth, bufferHeight = 1;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	/* setting context for GLEW to use */
	/* setting up window for GLEW to use, incase if we have muliple GLFWwindow's */
	/* first we need to make sure a GLFWwindow is current context */
	glfwMakeContextCurrent(mainWindow);

	/* allowing glew to use modern features */
	glewExperimental = GL_TRUE;

	/* Initializing GLEW */
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialization failed!" << std::endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	/* Depth Buffer */
	glEnable(GL_DEPTH_TEST);

	/* Setting up desired viewport size */
	glViewport(0, 0, bufferWidth, bufferHeight);

	/* Shader Projection */
	glm::mat4 Projection = glm::perspective(45.f, (GLfloat)bufferWidth / bufferHeight, 0.1f, 100.f);

	/* Printing out GL Version */
	std::cout << glGetString(GL_VERSION/*GL_SHADING_LANGUAGE_VERSION*/) << std::endl; // 4.6, major version: 4, minor version: 6

	/* Creating Triangle */
	CreateTriangle();
	/* Compiling Shaders */
	CompileShaders();

	/* loop until glfw window close button is pressed */
	/* window doesn't close by default by pressing close button, so we have to check if closebutton is true or not */
	while (!glfwWindowShouldClose(mainWindow)) {
		/* getting use input events, can handle any input events on window */
		glfwPollEvents();

		/* Updating Interp Values */
		/* moving using shader variable, @TODO can add UE interp code */
		Direction = (MoveXOffset >= 1.f || MoveXOffset <= -1.f) ? !Direction : Direction;
		if (Direction) {
			MoveXOffset += InterpSpeed;
		}
		else {
			MoveXOffset -= InterpSpeed;
		}
		//glUniform1f(XMoveId, MoveXOffset); /* moving using shader */
		/* Rotating Triangle */
		RotateInterp = (RotateInterp >= 360.f) ? 0.f : RotateInterp + InterpSpeed;

		/* Clearing BUFFERS before drawing anything */
		/* clearing to draw a new frame, preventing drawing on top of another/previous frame */
		glClearColor(0.f, 0.f, 0.f, 1.f); /* color data of the pixels, background resulting maybe */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* clearing only color data of the pixel, since each pixel has a lot of data like stencel, depth, color, etc */

		/* Shader */
		glUseProgram(Shader);

		/* Shader Model */
		glm::mat4 model(1.f);
		/* Translate */
		/* if we do rotation first and translate after, it will behave like relative space translate. world space translate is the otherway around */
		/* if we do scale first object origin will not hit desired max translate destination */
		model = glm::translate(model, glm::vec3(0.f, 0.f, -2.f)); /* translate matrix */
		/* Scale */
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		/* Rotate */
		/* maybe do scale first and rotate, to prevent stretching i think */
		model = glm::rotate(model, glm::radians<GLfloat>(RotateInterp), glm::vec3(0.2f, 1.f, 0.5f)); /* One Radian = PI/180 */

		/* Sending Model to Shader */
		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		/* Sending Projection to Shader */
		glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(Projection)); /* perspective starts at origin, so if there is any object in origin will look zoomed in */

		/* Drawing Triangle */
		glBindVertexArray(VAO); /* activating vertex array, so can draw */
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); /* no need i think, since drawing fine */
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Draws whatever that is currently activated in vertex array */
		glDrawElements(GL_TRIANGLES/* takes the indices as first 3 to draw */, 36/* total number of indices to draw */, GL_UNSIGNED_INT, nullptr); /* we don't need pointer, since VAO is activated in previous statement which VAO has link to IBO */
		/* Deactivating so we don't have problem in next statements */
		glBindVertexArray(0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		/* Shader */
		glUseProgram(0); /* unuse shader for the next statement code, maybe we use different shader in the next statements */

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();
	return 0;
}