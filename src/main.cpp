#include "window.hpp"
#include "shader.hpp"
#include "objects.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
Shader shader;

void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    // if (keyCode == GLFW_KEY_A)
    //     sides--;
    // if (keyCode == GLFW_KEY_D)
    //     sides++;
}

void cursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    float normalizedX = static_cast<float>(xPos) / static_cast<float>(WINDOW_WIDTH);
    float normalizedY = static_cast<float>(yPos) / static_cast<float>(WINDOW_HEIGHT);
    normalizedX = 2 * normalizedX - 1.0f;
    normalizedY = 1.0f - (2.0 * normalizedY);

    // std::cout << normalizedX << " " << normalizedY << std::endl;
    GLint mousePosLocation = glGetUniformLocation(shader.shaderProgram, "mousePos");
    glUniform2f(mousePosLocation, static_cast<float>(normalizedX), static_cast<float>(normalizedY));
}



void run()
{
    shader.use();
    // Update the window
    // Rectangle rect1(-1, -1, 2, 2);
    // rect1.draw();

    // glBindVertexArray(primes.VAO);
    // glDrawArrays(GL_POINTS, 0, numberofVertices);
    // glBindVertexArray(0);
}


   
int main()
{
    // Create a window
    Window mainWindow(800, 800, "Main Window");
    mainWindow.setCharacterCallback(characterCallback);
    mainWindow.setcursorPosCallback(cursorPosCallback);
    shader.initialize(
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/vertex.glsl",
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/fragment.glsl"
    );

    double time = 0.0;
    while (!mainWindow.shouldClose())
    {
        time = glfwGetTime();
        GLint timeLocation = glGetUniformLocation(shader.shaderProgram, "time");
        glUniform1f(timeLocation, time);
        // std::cout << time << std::endl;
        // Update the window
        mainWindow.update(run);
    }
   
    return 0;
}
