#pragma once

#include "glitter.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "mesh.hpp"

namespace Gravel {

    class Engine {
        public:
            Engine();

            void mainLoop();

        private:
            void setupShaders();
            void getKeyPress();

            Shader* shader;
            GLFWwindow* mWindow;
            GLuint uniforms;
            glm::mat4 view;
    };
}
