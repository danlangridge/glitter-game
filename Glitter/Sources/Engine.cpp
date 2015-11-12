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

        /*
           glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
           glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
           glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
           glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
           glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
           */ 

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
        generateProgram(); 
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


    void Engine::generateProgram() {

        const GLchar* vertexSourceFile = "/home/dan/workspace/glitter/Glitter/Glitter/Sources/shader.vert";
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader); 

        const GLchar* fragmentSourceFile = "/home/workspace/glitter/Glitter/Glitter/Sources/fragment.vert";
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        //TODO: get errors in case of failed compilation
        std::printf("shaders uploaded\n");

        GLint status;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
        if (status) {
            std::printf("Vertex Shader compiled successfully\n"); 
        } else {
            char buffer[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, buffer); 
            std::printf("Vertex Shader failed compilation: %s", buffer);
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
        if (status) {
            std::printf("Fragment Shader compiled successfully\n"); 
        } else {
            char buffer[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, buffer); 
            std::printf("Fragment Shader failed compilation: %s", buffer);
        }

        GLuint shaderProgram = glCreateProgram();
        glAttachShader( shaderProgram, vertexShader);
        glAttachShader( shaderProgram, fragmentShader);

        glBindFragDataLocation(shaderProgram, 0, "outColor");

        //Link shaders to eachother
        glLinkProgram(shaderProgram);

        //Activate program
        glUseProgram(shaderProgram);

        //attach to gl_Position
        GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

}
