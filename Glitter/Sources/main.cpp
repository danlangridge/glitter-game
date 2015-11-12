// Local Headers
#include "glitter.hpp"
#include "Engine.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <string>

int main(int argc, char * argv[]) {

    Gravel::Engine gameEngine = Gravel::Engine();
    gameEngine.mainLoop();

    return 0;
}
