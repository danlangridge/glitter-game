#pragma once

#include "glitter.hpp"
#include <GLFW/glfw3.h>


namespace Gravel {

    class Engine {
        public:
            Engine();

            void mainLoop();

        private:
            void generateProgram();

            GLuint shaderProgram;
            GLFWwindow* mWindow;
            GLuint uniforms;
    };


}
