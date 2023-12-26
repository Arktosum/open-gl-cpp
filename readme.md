# open-gl-cpp

An openGL utility framework used to build other projects.

VAO - Vertex Array Object
Contains attributes
16 attributes (0 to 15)
for each attribute, we can store any data.
Example
Attribute 0 : Vertex Position (vec3)
Attribute 1 : Vertex Color (vec3)
Attribute 2 : Normal Vector (vec3)
Attribute 4 : Normal Vector (vec3)
etc..

VAOs only store VBOS per attribute. so in reality,
Attribute 0: VBO0
Attribute 1: VBO1
Attribute 2: VBO2
Attribute 3: VBO3
etc...

VBO : Vertex Buffer object.
Like the name suggests, it's a buffer or an array where we can store any data,
by specifiying the size , data etc...

Each VAO has it's unique ID

so let's take a triangle,
x1,y1,x2,y2,x3,y3
in this order, we store the data in a VBO and then store in a VAO
and by using the ID we can render the triangle whenever we want!


Open GL draws its triangles in CCW order.
we can specify the order differently by using index buffers.
like if we want to draw a rectangle, we need 6 vertices, we are reusing a vertex twice.

Shared vertices are a big problem and we need to minimize and reuse vertices instead of defining them again.

V0,V1,V3,V3,V1,V2
v3 is sent twice to the VBO(Vertex Position).
INSTEAD, we'll pass 4 vertices and tell open gl the order or index in a
VBO ( Index Buffer )



 // Local Coordinates
 // Object is the center

// Global Coordinates
// World center is the center
// Many objects are in the world.

// View Cordinates
// Camera is the center , no perspective

// Clip coordinates
// View coordinates counts for perspective
// Everything beyond the clip is deleted.

// Screen Coordinates.
// Flattened coordinates so we can see in our 2D window.


Local ->ModelMatrix -> World
World -> ViewMatrix -> View
View -> ProjectionMatrix -> Clip
Clip -> Screen