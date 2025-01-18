// OpenGL DataTypes
// GLint
// GLboolean { GL_TRUE, GL_FALSE }
//gl_Position = vec4(Scale * pos.x + (XMove * (Scale - 1.f)), Scale * pos.y, pos.z, 1.0); // vertex shader
//colour = vec4(1.0, 0.0, 0.0, 1.0); // fragment shader

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

#include <iomanip>

/* Window Dimensions */
const GLint WIDTH = 720, HEIGHT = 480;

/* Meshes */
std::vector<Mesh*> Meshes;

/* Shader */
std::vector<Shader*> Shaders;

/* Interpolation */
GLboolean Direction;
GLfloat MoveOffset = 0.f, InterpSpeed = 0.01f, RotateInterp = 0.f;

void CompileShaders() {
	/* Creating a Shader Program */
	Shader* shader = new Shader();

	/* Adding Shaders to Shader Program */
	/* Vertex Shader */
	shader->AddShader("Shaders/vshader.vert", GL_VERTEX_SHADER);
	/* Fragment Shader */
	shader->AddShader("Shaders/fshader.frag", GL_FRAGMENT_SHADER);

	/* Linking And Validating Shader Program */
	shader->LinkAndValidate();

	/* Adding our new shader to Shaders */
	Shaders.push_back(shader);
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

	Mesh* mesh1 = new Mesh();
	mesh1->CreateMesh(Vertices, sizeof(Vertices), Indices, sizeof(Indices));
	Meshes.push_back(mesh1);
	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(Vertices, sizeof(Vertices), Indices, sizeof(Indices));
	Meshes.push_back(mesh2);
}

int main()
{
	std::cout << std::fixed << std::setprecision(3);
	/* GLFW */
	if (!glfwInit()) { /* GLFW Initialization */
		std::cout << "GLFW initialization falied!" << std::endl;
		glfwTerminate(); /* terminitaing glfw if we fail to initialize */
		return 1; /* unsuccessful return */
	}

	/* Window */
	Window* mainWindow = new Window(WIDTH, HEIGHT, "Nani OpenGL");
	mainWindow->MakeCurrent();
	/* Buffer Size */
	glm::vec<2, GLint> BufferSize = mainWindow->GetWindowFrameBufferSize();
	
	/* GLEW */
	glewExperimental = GL_TRUE; /* allowing glew to use modern features */
	if (glewInit() != GLEW_OK) { /* GLEW Initialization */
		std::cout << "GLEW initialization failed!" << std::endl;
		glfwDestroyWindow(mainWindow->GetWindow());
		glfwTerminate();
		return 1;
	}

	/* Depth Buffer */
	glEnable(GL_DEPTH_TEST); /* to prevent random normal infacing */

	/* Viewport Size */
	glViewport(0, 0, BufferSize.x, BufferSize.y); /* setting viewport size of context current window */

	/* Printing out GL Version */
	std::cout << glGetString(GL_VERSION/*GL_SHADING_LANGUAGE_VERSION*/) << std::endl;

	/* Creating Triangle */
	CreateTriangle();

	/* Shader */
	CompileShaders();
	/* Getting Shader[0] Variable ID's */
	GLuint UniformProjection, UniformModel = 0;
	UniformProjection = Shaders.at(0)->GetShaderUniformLocation("Projection");
	UniformModel = Shaders.at(0)->GetShaderUniformLocation("Model");

	/* Shader Projection */
	glm::mat4 Projection = glm::perspective(45.f, (GLfloat)BufferSize.x / BufferSize.y, 0.1f, 100.f);


	GLboolean bCloseWindow = false;
	/* loop until glfw window close button is pressed */
	/* when we press the close buttion of a window, it sets glfwWindowShouldClose(thatwindow, GLFW_TRUE); */
	while (!bCloseWindow/*!glfwWindowShouldClose(mainWindow->GetWindow())*/) {
		/* getting use input events, can handle any input events on window */
		glfwPollEvents();

		/* Updating Interp Values */
		/* moving using shader variable, @TODO can add UE interp code */
		Direction = (MoveOffset >= 1.f || MoveOffset <= -1.f) ? !Direction : Direction;
		if (Direction) {
			MoveOffset += InterpSpeed * 0.01f;
		}
		else {
			MoveOffset -= InterpSpeed * 0.01f;
		}
		//glUniform1f(XMoveId, MoveXOffset); /* moving using shader */
		/* Rotating Triangle */
		RotateInterp = (RotateInterp >= 360.f) ? 0.f : RotateInterp + InterpSpeed;

		/* Clearing BUFFERS before drawing anything */
		/* clearing to draw a new frame, preventing drawing on top of another/previous frame */
		glClearColor(0.f, 0.f, 0.f, 0.f); /* color data of the pixels, background resulting maybe */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* clearing only color data of the pixel, since each pixel has a lot of data like stencel, depth, color, etc */

		/* Shader */
		Shaders.at(0)->UseShader();

		/* Projection Matrix */
		glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(Projection)); /* perspective starts at origin, so if there is any object in origin will look zoomed in */

		/* Shader Model 1 */
		glm::mat<4, 4, GLfloat> model(1.f);
		/* Translate */
		model = glm::translate(model, glm::vec<3, GLfloat>(0.6f, MoveOffset * 0.5f, -2.f));
		/* Scale */
		model = glm::scale(model, glm::vec<3, GLfloat>(0.3f, 0.3f, 0.3f));
		/* Rotate */
		model = glm::rotate(model, glm::radians<GLfloat>(RotateInterp), glm::vec<3, GLfloat>(0.2f, 1.f, 0.5f));
		/* Model Matrix */
		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		/* Rendering Mesh */
		Meshes.at(0)->RenderMesh();

		/* Shader Model 2 */
		model = glm::mat<4, 4, GLfloat>(1.f); /* We need to reset the model value and apply new values, since it has previous transformation values */
		model = glm::translate(model, glm::vec<3, GLfloat>(-0.6f, - MoveOffset * 0.5f , -2.f));
		model = glm::scale(model, glm::vec<3, GLfloat>(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians<GLfloat>(RotateInterp), glm::vec<3, GLfloat>(0.2f, 1.f, 0.5f)); /* One Radian = PI/180 */
		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Meshes.at(1)->RenderMesh();



		/* Shader */
		/* unuses Shader Progrom, since it is the only Shader that is beging used in the previous statements */
		glUseProgram(0); /* unuse shader for the next statement code, maybe we use different shader in the next statements */

		/* Instantly closes window */
		if (mainWindow->GetKeyEvents().at(GLFW_KEY_ESCAPE)) bCloseWindow = true;

		glfwSwapBuffers(mainWindow->GetWindow());
	}

	mainWindow->ClearWindow();
	glfwTerminate();
	return 0;
}