#include "./glad/glad.h"
#include <math.h>
#include <vector>
class Object3D
{
public:
    unsigned int VBO, VAO;
    void init(void *vertices, unsigned int size)
    {

        // Set up a Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        // Specify the layout of the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        /*
            0 - starting index
            3 - 3 Dimensions
            GL_FLOAT - data type
            GL_FALSE - normalized or not, putting true will convert to NDC
            dimension spacing - dimension * datatype apart in the array. [(0,0,0),(0,0,1)]
        */
        glEnableVertexAttribArray(0);

        // Unbind VAO and VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // glDrawArrays(mode, first, count);
        /*
            GL_POINTS          -  Renderds points every vertex
            GL_LINES           -  Renderds line every two adjacent vertex
            GL_LINE_STRIP      -  Renderds line segements between adjacent
            GL_LINE_LOOP       -  Renderds line segements and finishes with a line from end to start
            GL_TRIANGLES       -  Renderds triangles. Every three vertices define a triangle.
            GL_TRIANGLE_STRIP  -  Renderds series of connected triangles. Each vertex after the first three defines a new triangle.
            GL_TRIANGLE_FAN    -  Renders a series of triangles sharing a common vertex (fan-like arrangement). First vertex is the center, the rest are taken as triangles.
            GL_QUAD_STRIP      -  Renders a strip of connected quadrilaterals. Each pair of vertices after the first two defines a new quad.
        */
    }
};
struct Point3D
{
    float x, y, z;
    Point3D(float x, float y, float z) : x(x), y(y), z(z) {}
};

class Circle : public Object3D
{
public:
    unsigned int numberOfVertices;

    double deg_to_rad(double degrees)
    {
        return (degrees * 3.1415) / 180;
    }
    Circle(float centerX, float centerY, float centerZ, float radius, unsigned int numberOfSides = 20)
    {

        std::vector<Point3D> vertices;
        vertices.emplace_back(centerX, centerY, centerZ);
        for (int i = 0; i <= numberOfSides; ++i)
        {
            float angle = 2.0f * 3.14159f * static_cast<float>(i) / static_cast<float>(numberOfSides);
            float x = centerX + radius * std::cos(angle);
            float y = centerY + radius * std::sin(angle);
            vertices.emplace_back(x, y, 0);
        }

        numberOfVertices = vertices.size();
        GLsizeiptr size = vertices.size() * sizeof(Point3D);

        Object3D::init(vertices.data(), size);
    }
    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
        glBindVertexArray(0);
    }
};

class Rectangle : public Object3D
{
public:
    unsigned int numberOfVertices;
    Rectangle(float x, float y, float width, float height)
    {
        Point3D bl = {x, y, 0.0f};
        Point3D br = {x + width, y, 0.0f};
        Point3D tl = {x, y + height, 0.0f};
        Point3D tr = {x + width, y + height, 0.0f};

        std::vector<Point3D> vertices = {bl, br, tr, tr, tl, bl};
        numberOfVertices = vertices.size();
        GLsizeiptr size = vertices.size() * sizeof(Point3D);

        Object3D::init(vertices.data(), size);
    }
    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
        glBindVertexArray(0);
    }
};