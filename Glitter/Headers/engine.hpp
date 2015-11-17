#pragma once

#include "glitter.hpp"
#include <GLFW/glfw3.h>

#include "shader.hpp"

namespace Gravel {

    class Engine {
        public:
            Engine();

            void mainLoop();

        private:
            void setupShaders();

            Shader* shader;
            GLFWwindow* mWindow;
            GLuint uniforms;
    };
}
