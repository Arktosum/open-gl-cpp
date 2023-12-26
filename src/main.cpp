#include "window.hpp"
#include "objects.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 800.0f
Shader shader;

float cameraX, cameraY;
float cameraZ = -3.0f;
void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    if (keyCode == GLFW_KEY_A)
        cameraX += 0.1;
    if (keyCode == GLFW_KEY_D)
        cameraX -= 0.1;
    if (keyCode == GLFW_KEY_W)
        cameraY -= 0.1;
    if (keyCode == GLFW_KEY_S)
        cameraY += 0.1;
    if (keyCode == GLFW_KEY_Z)
        cameraZ += 0.1;
    if (keyCode == GLFW_KEY_X)
        cameraZ -= 0.1;
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

float degrees = 0.0f;
void run()
{
    shader.use();
    texture.bind();
    // Rectangle rect1(0.0f,0.0f,0.0f,0.5f,0.5f);
    CUBE cube;
    cube.draw();
    Line x_axis(0.0f,0.0f,0.0f, 1.0f,0.0f,0.0f);
    Line y_axis(0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);
    Line z_axis(0.0f,0.0f,0.0f, 0.0f,0.0f,1.0f);
    // glm::mat4 proj = glm::ortho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f); // ORTHOGONAL
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

    // Left , right , bottom , top , znear,zfar // MAKE SURE EVERYTHING IS A FLOAT!
    glm::vec3 cameraPos = glm::vec3(cameraX, cameraY, cameraZ);  
    // std::cout<<"Camera position : "<<cameraPos.x<<" "<<cameraPos.y<<" "<<cameraPos.z<<std::endl;
    glm::mat4 view = glm::translate(glm::mat4(1.0f),cameraPos);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
    degrees += 0.01;
    if(degrees >= 360.0f) degrees = 0.0f;
    glm::mat4 MVP = proj * view * model;
    GLint MVP_location = glGetUniformLocation(shader.shaderProgram, "MVP");
    glUniformMatrix4fv(MVP_location, 1, GL_FALSE, &MVP[0][0]);
    // GL_FALSE -> if Column major no problem.
    // GL_TRUE -> to convert Row major to column major.
    x_axis.draw();
    y_axis.draw();
    z_axis.draw();

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
