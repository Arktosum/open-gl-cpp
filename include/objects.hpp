#include "./glad/glad.h"
#include <math.h>
#include <vector>
#include "shader.hpp"
#include <stb/stb_image.h>


class Texture{
    public:
    GLuint textureID;
    int imgWidth,imgHeight,numColchannels; // STBI not allowing unsigned int??
    void init(std::string texturePath){
            // Texture
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(texturePath.c_str(),&imgWidth,&imgHeight,&numColchannels,0);
        glGenTextures(1,&textureID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textureID);

        // What to happen if minimized or maximized.
        // Nearest neighbor or Linear interpolation
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgWidth,imgHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(bytes);
        glBindTexture(GL_TEXTURE_2D,0);
    }
    void bind(){
        glBindTexture(GL_TEXTURE_2D,textureID);
    }
};

class VBO
{
public:
    unsigned int vbo, ebo;
    void link(float *vertices, size_t vertexSize, unsigned int *indices, size_t indexSize)
    {
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        // Copy vertex data to VBO
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

        // Copy index data to EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);
    }
    void destroy()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};
class VAO
{
public:
    unsigned int vao;
    VAO()
    {
        glGenVertexArrays(1, &vao);
    }
    void bind() { glBindVertexArray(vao); }
    void unbind() { glBindVertexArray(0); }
    void linkAttributes(VBO& vbo, GLuint layout, GLuint dimensions, GLenum type, GLsizeiptr stride, void *offset)
    {
        // Set vertex attribute pointers
        vbo.bind();
        glVertexAttribPointer(layout, dimensions, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vbo.unbind();
    }
    void destroy()
    {
        glDeleteVertexArrays(1, &vao);
    }
};

class OBJECT3D
{
public:
    VAO vao;
    VBO vbo;
    OBJECT3D()
    {}
    void draw(){}
    ~OBJECT3D()
    {
        vao.destroy();
        vbo.destroy();
    }
};

class Rectangle : OBJECT3D
{
public:
    Rectangle(float x, float y ,float width, float height) // To normalize
    {
        
        // Vertex data
        float vertices[] = {
            x,y,0,                     1,0,          
            x+width,y,0,               0,0,
            x+width,y+height,0,        0,1,
            x,y+height,0,              1,1
        };

        // Index data
        unsigned int indices[] = {
            0, 1, 2, // First triangle
            2, 3, 0  // Second triangle
        };

        // Create and bind a Vertex Array Object (VAO)
        vao.bind();
        vbo.link(vertices, sizeof(vertices), indices, sizeof(indices));
        vao.linkAttributes(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
        vao.linkAttributes(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3*sizeof(float)));
        // vao.linkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

        vao.unbind();
    }

    void draw(){
        // Draw the rectangle
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


class CUBE : OBJECT3D
{
public:
    unsigned int vertexCount;
    CUBE() // To normalize
    {
        // Vertex data
        float vertices[] = {
    // Front face
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,  0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        // Right face
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f
    };

        // Index data
        unsigned int indices[] = {
         0, 1, 2, 2, 3, 0, // Front face
        4, 5, 6, 6, 7, 4, // Back face
        8, 9, 10, 10, 11, 8, // Right face
        12, 13, 14, 14, 15, 12, // Left face
        16, 17, 18, 18, 19, 16, // Top face
        20, 21, 22, 22, 23, 20  // Bottom face
        };
        vertexCount = sizeof(indices)/sizeof(unsigned int);
        // Create and bind a Vertex Array Object (VAO)
        vao.bind();
        vbo.link(vertices, sizeof(vertices), indices, sizeof(indices));
        vao.linkAttributes(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void *)0);
        vao.linkAttributes(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3*sizeof(float)));
        // vao.linkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

        vao.unbind();
    }

    void draw(){
        // Draw the rectangle
        vao.bind();
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};



class Line : OBJECT3D
{
public:
    Line(float x1, float y1, float z1,float x2,float y2,float z2) // To normalize
    {
        
        // Vertex data
        float vertices[] = {
            x1,y1,z1,
            x2,y2,z2
        };

        // Index data
        unsigned int indices[] = {
            0, 1
        };

        // Create and bind a Vertex Array Object (VAO)
        vao.bind();
        vbo.link(vertices, sizeof(vertices), indices, sizeof(indices));
        vao.linkAttributes(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
        // vao.linkAttributes(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void *)(3*sizeof(float)));
        // vao.linkAttributes(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

        vao.unbind();
    }

    void draw(){
        // Draw the rectangle
        vao.bind();
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


class Circle : OBJECT3D
{
public:
    unsigned int sides;
    Circle(float centerX,float centerY,float radius,unsigned int segments) // To normalize
    {
        // Vertex data
        sides = segments;
        float vertices[3*(segments+1)]; 
        double degree_to_radians_ratio = 3.141592/180;
        double angle = (360/segments)*degree_to_radians_ratio;
        double current_angle = 0;
        vertices[0] = centerX;
        vertices[1] = centerY;
        vertices[2] = 0.0f;
        for(int i = 1; i <= segments; i++){
            vertices[3*i+0] = centerX + radius*cos(current_angle);
            vertices[3*i+1] = centerY + radius*sin(current_angle);
            vertices[3*i+2] = 0.0f;
            current_angle += angle;
        }

        
        unsigned int indices[3*sides];
        
        unsigned int prev = 1;
        for(int i =0 ; i < sides-1; i++){
            indices[3*i+0] = 0;
            indices[3*i+1] = prev;
            indices[3*i+2] = prev+1;
            prev+=1;
        }
        // Join last point with first point.
        indices[3*(sides-1) + 0] = 0;
        indices[3*(sides-1) + 1] = sides;
        indices[3*(sides-1) + 2] = 1;



        // Create and bind a Vertex Array Object (VAO)
        vao.bind();
        vbo.link(vertices, sizeof(vertices), indices, sizeof(indices));
        vao.linkAttributes(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);

        vao.unbind();
    }

    void draw(){
        // Draw the rectangle
        vao.bind();
        glDrawElements(GL_TRIANGLE_FAN, sides*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

