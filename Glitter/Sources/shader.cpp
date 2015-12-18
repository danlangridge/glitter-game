#include "shader.hpp"
#include <fstream>
#include <streambuf>
#include <cstdio>

Shader::Shader(std::string vertexShader, std::string fragmentShader) {
    mProgram = glCreateProgram();
    get(fragmentShader);
    get(vertexShader);
    setupBinds(); 
    glLinkProgram(mProgram);
    glUseProgram(mProgram);
}

void Shader::get(std::string filename) {
    
    std::ifstream shaderFile(filename);
    std::string shaderContent;

    shaderFile.seekg(0, std::ios::end);
    shaderContent.reserve(shaderFile.tellg());
    shaderFile.seekg(0, std::ios::beg);
    shaderContent.assign((std::istreambuf_iterator<char>(shaderFile)),std::istreambuf_iterator<char>());

    if (filename.find(".vert") != std::string::npos) {
        attach(shaderContent, GL_VERTEX_SHADER);
    } else if (filename.find(".frag") != std::string::npos) {
        attach(shaderContent, GL_FRAGMENT_SHADER);
    } else {
        printf("unknown shader filetype for file: %s", filename.c_str());
    }
}

void Shader::attach(std::string shader, GLenum type) {

    const GLchar* shaderCode = shader.c_str();

    GLuint shaderAddress = 0;
    std::string typeString = "";

    if (type == GL_VERTEX_SHADER) {

        typeString = "vertex";
        shaderAddress = glCreateShader(GL_VERTEX_SHADER);
        mFragmentShader = shaderAddress;

    } else if (type == GL_FRAGMENT_SHADER) {

        shaderAddress = glCreateShader(GL_FRAGMENT_SHADER);
        typeString = "fragment";
        mFragmentShader = shaderAddress;
    }     

    glShaderSource(shaderAddress, 1, &shaderCode, NULL);
    glCompileShader(shaderAddress);

    GLint status;
    glGetShaderiv(shaderAddress, GL_COMPILE_STATUS, &status);
    
    if (status) {
    
        std::printf("%s shader compiled successfully\n", typeString.c_str()); 
    
    } else {
    
        char buffer[512];
        glGetShaderInfoLog(shaderAddress, 512, NULL, buffer); 
        std::printf("%s shader failed compilation: %s", typeString.c_str(), buffer);
    
    }
    glAttachShader( mProgram, shaderAddress);
}

void Shader::bind(unsigned int location, glm::mat4 const & matrix) {
    
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); 
}

void Shader::setupBinds() {
    glBindFragDataLocation(mProgram, 0, "outColor");
}

void Shader::bindAttributeArray(std::string attribute) {
        GLint posAttrib = glGetAttribLocation(mProgram, attribute.c_str());
        glEnableVertexAttribArray(posAttrib);
        glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);


}
