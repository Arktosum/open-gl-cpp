
#include "shader.hpp"

std::string readFile(const std::string &filename)
{
    std::fstream myFile;
    myFile.open(filename, std::ios::in);
    if (!myFile.is_open())
    {
        throw std::runtime_error("File not open!" + filename);
    }

    std::string file_data;
    std::string line;
    while (getline(myFile, line))
    {
        file_data += line + "\n";
    }

    myFile.close();
    return file_data;
}

void Shader::initialize(const std::string vertexShaderFilepath, const std::string fragmentShaderFilepath)
{
    // Set up the shader program (you need to implement shader loading separately)
    // Use a simple shader program with a vertex and fragment shader
    // Bind the shader program here
    // Load and compile vertex shader

    std::string vertexSourceCode = readFile(vertexShaderFilepath);
    std::string fragmentSourceCode = readFile(fragmentShaderFilepath);
    const char *vertexShaderSource = vertexSourceCode.c_str();
    const char *fragmentShaderSource = fragmentSourceCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors (you should add proper error handling)
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Load and compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors (you should add proper error handling)
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link shaders to create a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program linking errors (you should add proper error handling)
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    // Delete the shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
};

void Shader::use()
{
    glUseProgram(shaderProgram);
}