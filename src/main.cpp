#include "window.hpp"
#include "objects.hpp"
#include "linalg.hpp"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
Shader shader;

float cameraX, cameraY, cameraZ;

void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    if (keyCode == GLFW_KEY_A)
        cameraX += 1;
    if (keyCode == GLFW_KEY_D)
        cameraX -= 1;
    if (keyCode == GLFW_KEY_W)
        cameraY += 1;
    if (keyCode == GLFW_KEY_S)
        cameraY -= 1;
    if (keyCode == GLFW_KEY_Z)
        cameraZ += 1;
    if (keyCode == GLFW_KEY_X)
        cameraZ -= 1;
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

// GLuint uniformID = glGetUniformLocation(shader.shaderProgram,"name");
// glUniform2f(uniformID, x,y);
// glUniform1f(uniformID,x);
Window mainWindow(800, 800, "Main Window");

Texture texture;

double degree = 0;
void run()
{
    shader.use();
    texture.bind();
    // Rectangle rect1(-0.5, 0.5, 1, 1);
    // rect1.draw();
    CUBE cube;
    cube.draw();
    Matrix4x4 model,view,projection;

    projection = Matrix4x4::orthogonalProjection();
    model = Matrix4x4::rotateX(cameraX) * model;
    model = Matrix4x4::rotateY(cameraY) * model;
    model = Matrix4x4::rotateZ(degree) * model;


    view = Matrix4x4::translate(0,0.0,-0.1f) * view;
    Matrix vec(4,1);
    vec.data[0][0] = -0.5f;
    vec.data[1][0] = -0.5f;
    vec.data[2][0] = -0.5f;
    vec.data[3][0] = 1.0f;

    degree += 0.01;
    if (degree >= 360)
        degree = 0;
    Matrix out = projection * view * model * vec;

    out.print();
    GLint modelLoc = glGetUniformLocation(shader.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.toFloatArray());

    GLint viewLoc = glGetUniformLocation(shader.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.toFloatArray());

    GLint projectionLoc = glGetUniformLocation(shader.shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.toFloatArray());

}

int main()
{
    // Create a window
    mainWindow.setCharacterCallback(characterCallback);
    mainWindow.setcursorPosCallback(cursorPosCallback);
    shader.initialize(
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/vertex.glsl",
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/fragment.glsl");

    texture.init("E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/assets/image.png");
    GLuint text0uni = glGetUniformLocation(shader.shaderProgram, "tex0");
    glUniform1i(text0uni, 0);

    // glDeleteTextures(1,&texture);
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
