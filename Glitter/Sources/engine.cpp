#include "engine.hpp"
#include "glitter.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cmath>

#include <string>

namespace Gravel
{
    //Vertex Data 
    const float triangle[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    void renderObject(GLuint vertexBuffer) {
        glDrawArrays(GL_TRIANGLES, 0, 2436);
    }

    void Engine::uploadMesh(std::string filename) {

        Mesh* mesh = new Mesh(filename);
        drawables.push_back(mesh);

        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        //Grab memory using opengl (vertex Buffer Object)
        GLuint vbo;
        glGenBuffers(1, &vbo);

        //Tie memory to active datatype 
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        const unsigned int verticesPerFace = 3;

        //Upload data
        glBufferData(GL_ARRAY_BUFFER, mesh->getSize()*sizeof(float)*verticesPerFace, mesh->getVertices(), GL_STATIC_DRAW);
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
        glEnable(GL_DEPTH_TEST);

        drawables = std::vector<Mesh*>();
        uploadMesh("/home/dan/workspace/glitter-game/models/box.obj");
        uploadMesh("/home/dan/workspace/glitter-game/models/robot_man.obj");
        
        setupShaders(); 
    }

    void Engine::mainLoop() {

        auto t_start = std::chrono::high_resolution_clock::now();

        view = glm::lookAt(
                glm::vec3(1.2f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
                );

        shader->bind("view", view);

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
        shader->bind("proj",proj);

        glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
 
        while (glfwWindowShouldClose(mWindow) == false) {
            getKeyPress();

            // Background Fill Color
            glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto t_now = std::chrono::high_resolution_clock::now();
            float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
            
            glm::mat4 model;
            model = glm::rotate(
                    model,
                    time * glm::radians(180.0f), 
                    glm::vec3(0.0f, 0.0f, 1.0f)
                    ) * glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));

            //glm::vec4 result = model * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
            //printf("%f, %f, %f,\n", result.x, result.y, result.z);
            
            shader->bind("model", model);
             
            glDrawArrays(GL_TRIANGLES, 0, 2436);

            // Flip Buffers and Draw
            glfwSwapBuffers(mWindow);
            glfwPollEvents();
        }   glfwTerminate();
    }

    void Engine::getKeyPress() {
        double xpos, ypos;

        glfwGetCursorPos(mWindow, &xpos, &ypos);

        //printf("Mouse pos: x: %f, y: %f\n", xpos, ypos);
        //printf("Mouse rot: x: %f, y: %f\n", sin(xpos),cos(ypos));

        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);
        if(glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS) {
            view = glm::translate( view, glm::vec3(0.1f,0.0f,0.0f));
        }
        if(glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS) {
            view = glm::translate( view, glm::vec3(0.0f,0.1f,0.0f));
        }
        if(glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS) {
            view = glm::translate( view, glm::vec3(-0.1f,0.0f,0.0f));
        }
        if(glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS) {
            view = glm::translate( view, glm::vec3(0.0f,-0.1f,0.0f));
        }

        glm::mat4 mouseView = glm::rotate(view, (float)xpos*.05f, glm::vec3(0.0f, 0.0f, 1.0f)); 
        
        shader->bind("view", mouseView);
    }


    void Engine::setupShaders() {

        std::string vertexSourceFile = "/home/dan/workspace/glitter-game/Glitter/Shaders/shader.vert";
        std::string fragmentSourceFile = "/home/dan/workspace/glitter-game/Glitter/Shaders/shader.frag";

        shader = new Shader(vertexSourceFile, fragmentSourceFile);
        shader->bindAttributeArray("position");
    }
    

}
