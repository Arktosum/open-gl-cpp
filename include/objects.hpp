#include "./glad/glad.h"
#include <math.h>
#include <vector>
#include "shader.hpp"



class VAO{
    public:
    unsigned int vao;
    VAO(){
        glGenVertexArrays(1, &vao);
    }
    void bindVAO(){glBindVertexArray(vao);}
    void linkAttributes(){
        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }
    void deleteVAO(){
        glDeleteVertexArrays(1, &vao);
    }
};

class VBO{
    public:
    unsigned int vbo,ebo;
    void linkVBO(float* vertices,size_t vertexSize,unsigned int *indices,size_t indexSize){
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        // Copy vertex data to VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

        // Copy index data to EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);
    }
    void deleteVBO(){
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
};


class OBJECT3D
{
public:
    VAO vao;
    VBO vbo;
    OBJECT3D()
    {
        // Vertex data
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left
            0.5f, -0.5f, 0.0f,  // Bottom-right
            0.5f, 0.5f, 0.0f,   // Top-right
            -0.5f, 0.5f, 0.0f   // Top-left
        };

        // Index data
        unsigned int indices[] = {
            0, 1, 2, // First triangle
            2, 3, 0  // Second triangle
        };

        // Create and bind a Vertex Array Object (VAO)
        vao.bindVAO();
        vbo.linkVBO(vertices,sizeof(vertices),indices,sizeof(indices));
        vao.linkAttributes();
    }

    void draw()
    {
        // Draw the rectangle
        glBindVertexArray(vao.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    ~OBJECT3D()
    {
        vao.deleteVAO();
        vbo.deleteVBO();

    }
};


class Rectangle : OBJECT3D{
    public:

    Rectangle(){

    }
};