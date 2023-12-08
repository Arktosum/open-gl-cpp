#include "window.hpp"
#include "shader.hpp"
#include "objects.hpp"

Shader shader;
int sides = 3;

void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    if (keyCode == GLFW_KEY_A)
        sides--;
    if (keyCode == GLFW_KEY_D)
        sides++;
}

void mouseButtonPressCallback(GLFWwindow *window, int button, int action, int mod)
{
    std::cout << button << std::endl;
}

void run()
{
    shader.use();
    // Update the window
    Rectangle rect1(0, 0, 0.2, 0.2);
    rect1.draw();

    // Rectangle rect2(0.5, 0.5, 0.2, 0.2);
    // rect.draw();

    Circle circle(0.5, 0.5, 0, 0.5f, sides);
    circle.draw();
}

int main()
{
    // Create a window
    Window mainWindow(800, 800, "Main Window");
    mainWindow.setCharacterCallback(characterCallback);
    mainWindow.setmouseButtonPressCallback(mouseButtonPressCallback);

    shader.initialize(
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/vertex.glsl",
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/fragment.glsl");
    // Main loop

    double time = 0.0;
    while (!mainWindow.shouldClose())
    {
        time = glfwGetTime();
        std::cout << time << std::endl;
        // Update the window
        mainWindow.update(run);
    }

    return 0;
}
