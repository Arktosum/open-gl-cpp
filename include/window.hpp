#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./glad/glad.h"
#include <GLFW/glfw3.h>

class Window
{
public:
    // Constructor
    Window(int width, int height, const char *title);

    // Destructor
    ~Window();

    // Function to check if the window should close
    bool shouldClose() const;

    // Function to update the window (e.g., process input, swap buffers)
    void update(void (*callback)());

    void setCharacterCallback(void (*characterCallback)(GLFWwindow *window, unsigned int keyCode));
    void setkeyboardCallback(void (*keyboardCallback)(GLFWwindow *window, int key, int scancode, int action, int mods));
    void setcursorPosCallback(void (*cursorPosCallback)(GLFWwindow *window, double xPos, double yPos));
    void setmouseButtonPressCallback(void (*mouseButtonPress)(GLFWwindow *window, int button, int action, int mod));

private:
    GLFWwindow *window;
    int width, height;
    const char *title;
};

#endif // WINDOW_HPP
