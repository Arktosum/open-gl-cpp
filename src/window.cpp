#include "window.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char *title) : width(width), height(height), title(title)
{

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Set GLFW options if needed
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize Glad" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to initialize Glad");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST); // Used for depth testing! important in 3D
    
}

void Window::setCharacterCallback(void (*characterCallback)(GLFWwindow *window, unsigned int keyCode))
{
    glfwSetCharCallback(window, characterCallback);
}

void Window::setkeyboardCallback(void (*keyboardCallback)(GLFWwindow *window, int key, int scancode, int action, int mods))
{
    glfwSetKeyCallback(window, keyboardCallback);
}

void Window::setcursorPosCallback(void (*cursorPosCallback)(GLFWwindow *window, double xPos, double yPos))
{
    glfwSetCursorPosCallback(window, cursorPosCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // DISABLE,CENTER,HIDDEN etc...
}

void Window::setmouseButtonPressCallback(void (*mouseButtonPressCallback)(GLFWwindow *window, int button, int action, int mods))
{
    glfwSetMouseButtonCallback(window, mouseButtonPressCallback);

    // button - 0 left
    //          1 right
    //          2 middle
}

Window::~Window()
{
    // Terminate GLFW
    glfwTerminate();
}
void Window::close() const{
    glfwSetWindowShouldClose(window,true);
}
bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::update(void (*callback)())
{
    // Clear the color buffer to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the shader program
    callback();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

// return-type (*function-name)(param-1, param-2)