#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "Initializing GLFW Failed!" << std::endl;
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        std::cout << "Failed to Create GLFWwindow" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* First Make sure a GLFWwindow is context current before Initializing GLEW */
    if (glewInit() != GLEW_OK) {
        std::cout << "Initializing GLEW Failed!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }


    /* Printing out GL Version*/
    std::cout << glGetString(GL_VERSION) << std::endl; // 4.6, major version: 4, minor version: 6

    
    /* Triangle Positions */
    float Positions[6] = {
        -0.5f, -0.5f,
         0.f ,  0.5f,
         0.5f, -0.5f
    };
    /* Generating a Buffer */
    /* Vertex Buffer */
    GLuint BufferID;
    glGenBuffers(1, &BufferID); // technically only making a buffer id not the buffer itself i think
    glBindBuffer(GL_ARRAY_BUFFER, BufferID); // making a buffer of type and binding to the id, buffer type or type that can be stored in this buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), Positions, GL_STATIC_DRAW); // adding data to the buffer, must require size information, data is optional NULL if dont want to provide data, also data is static means stored once and used manytime
    /* Setting up Buffer layout */
    glEnableVertexAttribArray(0); // enabling the attribute pointer
    glVertexAttribPointer(0/*first attribute index*/, 2/*attribute size*/, GL_FLOAT/*buffer data type*/, GL_FALSE, 2 * sizeof(float)/*size of the attribute in bytes*/, 0);
    /* Clearing Buffer Binding */
    glBindBuffer(GL_ARRAY_BUFFER, 0); // clearing buffer bind so we can make and bind another buffer in the next statements

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Legacy OpenGL
        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f(0.f, 0.5f);
        //glVertex2f(0.5f, -0.5f);
        //glEnd();

        //
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/*
* Store in Buffer, layout that Buffer and Access with Shader, all done in graphics card
* Vertex Attribute = memory layout
* orderwise auto connections, weird statement wide standards
*/