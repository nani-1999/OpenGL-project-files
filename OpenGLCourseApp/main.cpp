// OpenGL DataTypes
// GLint
// GLboolean { GL_TRUE, GL_FALSE }
//gl_Position = vec4(Scale * pos.x + (XMove * (Scale - 1.f)), Scale * pos.y, pos.z, 1.0); // vertex shader
//colour = vec4(1.0, 0.0, 0.0, 1.0); // fragment shader

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h> /* must include glfw after glew, i think */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

#include "Nani/NaniMath.h"

/* @DEBUG */
#include <iomanip>
#include "Nani/NaniDebug.h"

/* Window */
const GLint WIDTH = 720, HEIGHT = 480; /* Dimensions */

/* Meshes */
std::vector<Mesh*> Meshes;

/* Shader */
std::vector<Shader*> Shaders;

/* Interpolation */
GLboolean Direction;
GLfloat MoveOffset = 0.f, InterpSpeed = 0.01f, RotateInterp = 0.f;

/* Delta Time */
GLfloat Time, DeltaTime = 0.f;

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

void CreateMesh() {

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
	/* @DEBUG */
	std::cout << std::fixed << std::setprecision(3);

	//Matest = glm::rotate(Matest, glm::radians(45.f), glm::vec<3, GLfloat>(1.f, 0.f, 0.f)); /* single time of axis always does global rotation, second time on same axis will result in gimbal lock problem */
	//glm::vec<3, GLfloat> ResultVec = Matest / glm::vec4(FwdVec, 1.f); /* multiply for column values, divide for row values */

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

	/* Creating Meshes */
	CreateMesh();

	/* Shader */
	CompileShaders();
	/* Getting Shader[0] Variable ID's */
	GLuint UniformProjection, UniformModel, UniformView = 0;
	UniformProjection = Shaders.at(0)->GetShaderUniformLocation("Projection");
	UniformModel = Shaders.at(0)->GetShaderUniformLocation("Model");
	UniformView = Shaders.at(0)->GetShaderUniformLocation("View");

	/* Projection Matrix */
	/* calculate prespective view of the buffer size */
	glm::mat<4, 4, GLfloat> Projection = glm::perspective(45.f, (GLfloat)BufferSize.x / BufferSize.y, 0.1f, 100.f);

	/* Camera Matrix */
	Camera* camera = new Camera();

	GLboolean bCloseWindow = false;
	/* loop until glfw window close button is pressed */
	/* when we press the close buttion of a window, it sets glfwWindowShouldClose(thatwindow, GLFW_TRUE); */
	while (!bCloseWindow/*!glfwWindowShouldClose(mainWindow->GetWindow())*/) {
		/* Time & DeltaTime */
		GLfloat CurrentTime = glfwGetTime();
		DeltaTime = CurrentTime - Time; /* before setting current time */
		Time = CurrentTime;

		/* Polling */
		/* getting user input events, can handle any input events on window */
		glfwPollEvents();

		/* Window Tick */
		mainWindow->Tick(DeltaTime); /* ticking for calculating delta cursor position */

		/* Updating Interp Values */
		/* moving using shader variable, @TODO can add UE interp code */
		//Direction = (MoveOffset >= 1.f || MoveOffset <= -1.f) ? !Direction : Direction;
		MoveOffset += InterpSpeed * 0.01f * ((MoveOffset >= 1.f || MoveOffset <= -1.f) ? 1.f :-1.f);
		//glUniform1f(XMoveId, MoveXOffset); /* moving using shader */
		/* Rotating Triangle */
		RotateInterp = (RotateInterp >= 360.f) ? 0.f : RotateInterp + InterpSpeed;

		/* Clearing BUFFERS before drawing anything */
		/* clearing to draw a new frame, preventing drawing on top of another/previous frame */
		glClearColor(0.f, 0.f, 0.f, 0.f); /* color data of the pixels, background resulting maybe */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* clearing only color data of the pixel, since each pixel has a lot of data like stencel, depth, color, etc */

		/* Shader */
		/* using Shaders[0] */
		Shaders.at(0)->UseShader();

		/* Math */
		GLfloat Sine = glm::sin(glm::radians<GLfloat>(Time * 100.f));
		GLfloat Frac = Nani::Frac(Time * 0.2f);
		GLfloat RAInterp = (Frac * 360.f - 180.f);

		/* Shader Model 1 */
		glm::mat<4, 4, GLfloat> model(1.f);
		/* Translate */
		model = glm::translate(model, glm::vec<3, GLfloat>(0.6f, Sine * 0.5f, 0.f));
		/* Scale */
		model = glm::scale(model, glm::vec<3, GLfloat>(0.3f, 0.3f, 0.3f));
		/* Rotate */
		model = glm::rotate(model, glm::radians<GLfloat>(RAInterp), glm::vec<3, GLfloat>(0.2f, 1.f, 0.5f));
		/* Model Matrix */
		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		/* Rendering Mesh */
		Meshes.at(0)->RenderMesh();

		/* Shader Model 2 */
		model = glm::mat<4, 4, GLfloat>(1.f); /* We need to reset the model value and apply new values, since it has previous model transformation values */
		model = glm::translate(model, glm::vec<3, GLfloat>(-0.6f, -Sine * 0.5f , 0.f));
		model = glm::scale(model, glm::vec<3, GLfloat>(-0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians<GLfloat>(RAInterp), glm::vec<3, GLfloat>(0.2f, 1.f, 0.5f)); /* rotation vec must be not zero vector, but angle can be zero. One Radian = PI/180 */
		glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Meshes.at(1)->RenderMesh();

		/* View Matrix */
		/* Doing before Projection */
		camera->UpdateCameraLocation(DeltaTime, mainWindow->GetKeyEvents()); /* updating camera location based on key events */
		camera->UpdateCameraRotation(mainWindow->GetDeltaCursorPos()); /* updating camera rotation based on mouse input */
		glm::mat<4, 4, GLfloat> CameraOrientation = camera->GetCameraMatrix(); /* getting camera orientation as matrix */
		glUniformMatrix4fv(UniformView, 1, GL_FALSE, glm::value_ptr(CameraOrientation)); /* using camera matrix as view matrix */
		
		/* Projection Matrix */
		/* Doing Projection on last */
		glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(Projection)); /* perspective starts at origin, so if there is any object in origin will look zoomed in */

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
/* refactoring to unreal on revision */