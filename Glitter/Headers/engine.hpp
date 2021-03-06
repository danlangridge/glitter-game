#pragma once

#include "glitter.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "mesh.hpp"
#include <vector>

namespace Gravel {

    class Engine {
        public:
            Engine();

            void mainLoop();

        private:
            void setupShaders();
            void getKeyPress();
            void uploadMesh(std::string filename);

            void renderObject(GLuint vbo);
            void renderAxis();
            void uploadAxis();
            void uploadAxis(const float axisLine[]);
            void renderLine(GLuint vbo);

            Shader* shader;
            GLFWwindow* mWindow;
            GLuint uniforms;
            glm::mat4 view;
            std::vector<Mesh*> drawables;

            std::vector<GLuint> buffers;            
            GLint positionAttribute;

            std::vector<GLuint> axis; 

    };
}
