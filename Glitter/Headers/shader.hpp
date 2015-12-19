#pragma once 
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glitter.hpp"


class Shader {
    public:
        
        Shader() {mProgram = glCreateProgram();}
        Shader(std::string vertexShader, std::string fragmentShader); 
        ~Shader() {glDeleteProgram(mProgram);}

        void get(std::string filename);
        void attach(std::string shader, GLenum type);
        void bind(unsigned int location, glm::mat4 const & matrix);
        template<typename T> Shader & bind(std::string const & name, T&& value)
        {
            int location = glGetUniformLocation(mProgram, name.c_str());
            if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
            else bind(location, std::forward<T>(value));
            return *this;
        }
        
        void setupBinds();
        void setupUniforms();
        GLuint mProgram;
    private:
        GLuint mVertexShader;
        GLuint mFragmentShader;
};
