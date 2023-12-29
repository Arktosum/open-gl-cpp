#include "window.hpp"
#include "objects.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Window mainWindow(1920, 1080, "Main Window");
Cube* cube;

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = -3.0f;
float cameraDegree = 0.0f;

enum CAMERA_AXIS
{
    CAMERA_X,
    CAMERA_Y,
    CAMERA_Z
};
CAMERA_AXIS cameraAxis = CAMERA_AXIS::CAMERA_X;

float sensitivity = 1.0f;
void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    if (keyCode == GLFW_KEY_A)
        cameraX += sensitivity;
    if (keyCode == GLFW_KEY_D)
        cameraX -= sensitivity;
    if (keyCode == GLFW_KEY_W)
        cameraY -= sensitivity;
    if (keyCode == GLFW_KEY_S)
        cameraY += sensitivity;
    if (keyCode == GLFW_KEY_Z)
        cameraZ += sensitivity;
    if (keyCode == GLFW_KEY_X)
        cameraZ -= sensitivity;
    if (keyCode == GLFW_KEY_Q)
        sensitivity += 0.1f;
    if (keyCode == GLFW_KEY_E)
        sensitivity -= 0.1f;
    if (keyCode == GLFW_KEY_I)
        cameraDegree += sensitivity;
    if (keyCode == GLFW_KEY_J)
        cameraDegree -= sensitivity;
    if (keyCode == GLFW_KEY_L)
    {
        cameraAxis = CAMERA_AXIS::CAMERA_X;
        std::cout << "Selected Axis : "
                  << "X" << std::endl;
        cameraDegree = 0.0f;
    }

    if (keyCode == GLFW_KEY_M)
    {
        cameraAxis = CAMERA_AXIS::CAMERA_Y;
        std::cout << "Selected Axis : "
                  << "Y" << std::endl;
        cameraDegree = 0.0f;
    }

    if (keyCode == GLFW_KEY_N)
    {
        cameraAxis = CAMERA_AXIS::CAMERA_Z;
        std::cout << "Selected Axis : "
                  << "Z" << std::endl;
        cameraDegree = 0.0f;
    }

    std::cout << "Sensitivity : " << sensitivity << std::endl;
}

void cursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    float normalizedX = static_cast<float>(xPos) / static_cast<float>(mainWindow.width);
    float normalizedY = static_cast<float>(yPos) / static_cast<float>(mainWindow.height);
    normalizedX = 2 * normalizedX - 1.0f;
    normalizedY = 1.0f - (2.0 * normalizedY);

    // std::cout << normalizedX << " " << normalizedY << std::endl;
    GLint mousePosLocation = glGetUniformLocation(cube->shaders[0].shaderProgram, "mousePos");
    glUniform2f(mousePosLocation, static_cast<float>(normalizedX), static_cast<float>(normalizedY));
}

// GLuint uniformID = glGetUniformLocation(shader.shaderProgram,"name");
// glUniform2f(uniformID, x,y);
// glUniform1f(uniformID,x);

float degrees = 0.0f;

void run()
{

    // Rectangle rect1(0.0f,0.0f,0.0f,0.5f,0.5f);

    Line x_axis(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    Line y_axis(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    Line z_axis(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    // glm::mat4 proj = glm::ortho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f); // ORTHOGONAL
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(mainWindow.width / mainWindow.height), 0.1f, 100.0f);
    // Left , right , bottom , top , znear,zfar // MAKE SURE EVERYTHING IS A FLOAT!
    glm::vec3 cameraPos = glm::vec3(cameraX, cameraY, cameraZ);
    float cameraRotX = (float)(cameraAxis == CAMERA_X);
    float cameraRotY = (float)(cameraAxis == CAMERA_Y);
    float cameraRotZ = (float)(cameraAxis == CAMERA_Z);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), cameraPos) * glm::rotate(glm::mat4(1.0f), glm::radians(cameraDegree), glm::vec3(cameraRotX, cameraRotY, cameraRotZ));

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                if (!((j == 0) || (j == 255)))
                    continue;
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f * i, 1.0f * j, 1.0f * k));
                glm::mat4 MVP = proj * view * model;
                GLint MVP_location = glGetUniformLocation(cube->shaders[0].shaderProgram, "MVP");
                glUniformMatrix4fv(MVP_location, 1, GL_FALSE, &MVP[0][0]);
                cube->draw();
            }
        }
    }

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
    cube = new Cube();
   
    cube->addShader(
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/vertex.glsl",
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/fragment.glsl");

    cube->addTexture("E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/assets/image.png",0);

    // glDeleteTextures(1,&texture);
    double time = 0.0;
    while (!mainWindow.shouldClose())
    {
        time = glfwGetTime();
        GLint timeLocation = glGetUniformLocation(cube->shaders[0].shaderProgram, "time");
        glUniform1f(timeLocation, time);
        // std::cout << time << std::endl;
        // Update the window
        mainWindow.update(run);
    }

    return 0;
}
