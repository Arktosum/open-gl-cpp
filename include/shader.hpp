#include "./glad/glad.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
    unsigned int shaderProgram;
    void initialize(const std::string vertexShaderFilepath, const std::string fragmentShaderFilepath);
    void use();
};