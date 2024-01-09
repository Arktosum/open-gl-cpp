#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class Window
{
public:
    GLFWwindow *window;
    int width, height;
    double deltaTime;
    // Constructor
    Window(int width, int height, const char *title);

    // Destructor
    ~Window();

    // Function to check if the window should close
    bool shouldClose() const;
    void close() const;

    // Function to update the window (e.g., process input, swap buffers)
    void update(void (*callback)());

    void setCharacterCallback(void (*characterCallback)(GLFWwindow *window, unsigned int keyCode));
    void setkeyboardCallback(void (*keyboardCallback)(GLFWwindow *window, int key, int scancode, int action, int mods));
    void setcursorPosCallback(void (*cursorPosCallback)(GLFWwindow *window, double xPos, double yPos));
    void setmouseButtonPressCallback(void (*mouseButtonPress)(GLFWwindow *window, int button, int action, int mod));

private:
        double lastFrame;
    const char *title;
};

#endif // WINDOW_HPP
