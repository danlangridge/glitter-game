#include "Engine.hpp"
#include "glitter.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <string>

namespace Gravel
{

    const GLchar* vertexSource = "#version 130\nin vec2 position;void main(){gl_Position = vec4(position, 0.0, 1.0);}";
    const GLchar* fragmentSource = "#version 130\nuniform vec3 triangleColor;out vec4 outColor;void main(){outColor = vec4(triangleColor, 1.0);}";

int uploadTestMesh() {
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    //Vertex Data 
    float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    //Grab memory using opengl (vertex Buffer Object)
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Tie memory to active datatype 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Upload data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    return 0;
}

    Engine::Engine() {
        // Load GLFW and Create a Window
        glfwInit();

        mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

        // Check for Valid Context
        if (mWindow == nullptr) {
            fprintf(stderr, "Failed to Create OpenGL Context");
            return;
        }

        // Create Context and Load OpenGL Functions
        glfwMakeContextCurrent(mWindow);
        gladLoadGL();
        fprintf(stderr, "OpenGL %s\nGLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

        uploadTestMesh();    
        setupShaders(); 
    }

    void Engine::mainLoop() {
        while (glfwWindowShouldClose(mWindow) == false) {
            if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(mWindow, true);

            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Flip Buffers and Draw
            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }   glfwTerminate();
    }


    void Engine::setupShaders() {

        std::string vertexSourceFile = "/home/dan/workspace/glitter-game/Glitter/Shaders/shader.vert";
        std::string fragmentSourceFile = "/home/dan/workspace/glitter-game/Glitter/Shaders/shader.frag";

        shader = new Shader(vertexSourceFile, fragmentSourceFile);
    }

}
