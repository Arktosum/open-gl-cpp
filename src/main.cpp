#include "window.hpp"
#include "objects.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
Window mainWindow(1000, 1000, "Main Window");
class Camera
{
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 direction;
    float fov = 45.0f;
    Camera()
    {
        position = glm::vec3(0.0f, 0.0f, 3.0f);
        // glm::mat4 proj = glm::ortho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f); // ORTHOGONAL
        // Left , right , bottom , top , znear,zfar // MAKE SURE EVERYTHING IS A FLOAT!
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    void update()
    {
        proj = glm::perspective(glm::radians(fov), (float)(mainWindow.width / mainWindow.height), 0.1f, 100.0f);
        glm::vec3 target = position + front;
        view = glm::lookAt(position, target, up);
    }
};
Camera *camera;
bool wireFrameMode = false;
void characterCallback(GLFWwindow *window, unsigned int keyCode)
{
    float cameraSpeed = 0.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position += cameraSpeed * camera->front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position -= cameraSpeed * camera->front;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->position += cameraSpeed * camera->up;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera->position -= cameraSpeed * camera->up;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
    {
        if (wireFrameMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireFrameMode = !wireFrameMode;
    }
}

float lastX = mainWindow.width / 2, lastY = mainWindow.height / 2;
double pitch = 0.0f;
double yaw = -90.0f;
double roll = 0.0f;
bool firstMouse = true;
void cursorPosCallback(GLFWwindow *window, double xPos, double yPos)
{
    float normalizedX = static_cast<float>(xPos) / static_cast<float>(mainWindow.width);
    float normalizedY = static_cast<float>(yPos) / static_cast<float>(mainWindow.height);
    normalizedX = 2 * normalizedX - 1.0f;
    normalizedY = 1.0f - (2.0 * normalizedY);

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    camera->direction = direction;
    camera->front = glm::normalize(direction);
}

// GLuint uniformID = glGetUniformLocation(shader.shaderProgram,"name");
// glUniform2f(uniformID, x,y);
// glUniform1f(uniformID,x);

class Block
{
public:
    Cube *cube;
    glm::vec3 position;

    Block(glm::vec3 position) : position(position) {}
    void draw()
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 MVP = camera->proj * camera->view * model;
        GLint MVP_location = glGetUniformLocation(cube->shaders[0]->shaderProgram, "MVP");
        glUniformMatrix4fv(MVP_location, 1, GL_FALSE, &MVP[0][0]);
        cube->draw();
    }
};

Block* block;
void run()
{

    block->draw();
    // std::cout << camera->position.x << " " << camera->position.y << " " << camera->position.z << " " << std::endl;
    // GL_FALSE -> if Column major no problem.
    // GL_TRUE -> to convert Row major to column major.
    camera->update();
}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera->fov -= (float)yoffset;
    if (camera->fov < 1.0f)
        camera->fov = 1.0f;
    if (camera->fov > 45.0f)
        camera->fov = 45.0f;
}

int main()
{
    // Create a window
    mainWindow.setCharacterCallback(characterCallback);
    mainWindow.setcursorPosCallback(cursorPosCallback);
    glfwSetInputMode(mainWindow.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(mainWindow.window, scroll_callback);
    Cube *cube = new Cube();
    cube->addShader(
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/vertex.glsl",
        "E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/src/shaders/fragment.glsl");

    cube->addTexture("E:/Programming/Github Repositories/Work In Progress/open-gl-cpp/assets/Rectangle 45.png", 0);

    camera = new Camera();
    block = new Block(glm::vec3(0.0f, 0.0f, 0.0f));
    block->cube = cube;
    while (!mainWindow.shouldClose())
    {
        // Update the window
        mainWindow.update(run);
    }

    return 0;
}
