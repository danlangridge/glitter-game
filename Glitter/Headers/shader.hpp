#pragma once 
#include <string>

#include "glitter.hpp"


class Shader {
    public:
        
        Shader() {mProgram = glCreateProgram();}
        Shader(std::string vertexShader, std::string fragmentShader); 
        ~Shader() {glDeleteProgram(mProgram);}

        void get(std::string filename);
        void attach(std::string shader, GLenum type);
        void setupBinds();
        void setupAttributes();
        GLuint retrieve(std::string filename);

    private:
        GLuint mProgram;
        GLuint mVertexShader;
        GLuint mFragmentShader;
};
