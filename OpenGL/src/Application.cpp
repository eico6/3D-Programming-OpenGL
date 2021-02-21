// The includes will paste in all the contents of the header files into the top of this .cpp file.
// The header files contain declerations and the implementation of their defenitions are found
// in their corresponding '.lib' files. These are linked together in the linking proccess.
// '.lib' (library files) files are just definitions pre-compiled into machine language.

#include <GL/glew.h>    // Includes modern OpenGL
#include <GLFW/glfw3.h> // Used to create a window and includes OpenGL 1.1 (Legacy OpenGL)

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

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
    window = glfwCreateWindow(640, 480, "Eivind Hobrad Naasen", NULL, NULL);
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

    // --- MY INITIALIZATIONS ---
    {
        float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
            -0.5f,  0.5f, // 3
        };

        // Index buffer
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // --- VERTEX BUFFER ---
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        // --- VERTEX ARRAY ---
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        // --- INDEX BUFFER ---
        IndexBuffer ib(indices, 6);

        // --- SHADERS ---
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
 
        // --- UNIFORMS ---
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

        // Unbind everything
        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r{0.0f};
        float increment{0.05f};
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            // Color cycle calculation
            if (r > 1.0f)
                increment = -0.01f;
            if (r < 0.0f)
                increment = 0.01f;
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    } // this scope is to delete all variables before 'glfwTerminate()'

    glfwTerminate();
    return 0;
}