// The includes will paste in all the contents of the header files into the top of this .cpp file.
// The header files contain declerations and the implementation of their defenitions are found
// in their corresponding '.lib' files. These are linked together in the linking proccess.
// '.lib' (library files) files are just definitions pre-compiled into machine language.

#include <GL/glew.h>    // Includes modern OpenGL
#include <GLFW/glfw3.h> // Used to create a window and includes OpenGL 1.1 (Legacy OpenGL)
#include <iostream>
#include "Application.h"

int main(void)
{
    GLFWwindow* window;
    Application* myApplication = new Application();

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Set OpenGL version to be 3.3 (MAJOR.MINOR), and profile mode to either:
    // Compatible profile = comes with a default VAO as object 0
    // Core profile       = does not come with a default VAO
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Eivind Naasen Hobrad", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Sets the fps to match either the VSync or the monitor's hz
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    myApplication->init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        myApplication->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(myApplication->getShader());

    glfwTerminate();
    return 0;
}
