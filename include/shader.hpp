#include "./glad/glad.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
    unsigned int shaderProgram;
    void initializePath(const std::string vertexShaderFilepath, const std::string fragmentShaderFilepath);
    void initialize(const std::string vertexSourceCode,const std::string fragmentSourceCode);
    void use();
};