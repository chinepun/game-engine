#include "application.hpp"
#include <iostream>
#include "tpf_type_name.h"
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <string>
#include "tiny_loader/tiny_obj_loader.h"
#include <unordered_map>
#include <stdexcept>


namespace std
{
    template<>
    struct hash<Vertex>
    {
        size_t operator()(Vertex const& vertex) const
        {
            return ((hash<glm::vec3>()(vertex.pos) ^
            (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
            (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}


Application::Application(void)
{
    // Create Shader state before activating it
    // ShaderInfo shaderCreateInfo{};
    // shaderCreateInfo.vertexFile = "shaders/example.vert";
    // shaderCreateInfo.fragmentFile = "shaders/example.frag";
    // shaderCreateInfo.tesselationControlShaderFile = "shaders/example.tesc";
    // shaderCreateInfo.tesselationEvaluationShaderFile = "shaders/example.tese";
    // shaderCreateInfo.shaderState = ShaderState::tesselation;

    // Shader shader(shaderCreateInfo);
//    this->shaderProgram = shader;
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao); 
}

Application::~Application(void)
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &this->vao);
}

void Application::loadModel(const std::string &MODEL_PATH)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn,err;

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str()))
    {
        throw std::runtime_error(warn + err);
    }
/*
An OBJ file consists of positions, normals, texture coordinates and faces. Faces
consist of an arbitrary amount of vertices, where each vertex refers to a position,
normal and/or texture coordinate by index. This makes it possible to not just
reuse entire vertices, but also individual attributes.
The attrib container holds all of the positions, normals and texture coordinates
in its attrib.vertices, attrib.normals and attrib.texcoords vectors. The
shapes container contains all of the separate objects and their faces. Each face
consists of an array of vertices, and each vertex contains the indices of the
position, normal and texture coordinate attributes. OBJ models can also define
a material and texture per face, but we will be ignoring those.
The err string contains errors and the warn string contains warnings that oc-
curred while loading the file, like a missing material definition. Loading only
really failed if the LoadObj function returns false. As mentioned above, faces
in OBJ files can actually contain an arbitrary number of vertices, whereas our
application can only render triangles. Luckily the LoadObj has an optional
parameter to automatically triangulate such faces, which is enabled by default.
*/
    for (const tinyobj::shape_t &shape : shapes)
    {
        for (const tinyobj::index_t &index : shape.mesh.indices)
        {
            Vertex vertex{};//Vertex&& vertex{};
            vertex.pos = 
            {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            vertex.texCoord = 
            {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };
            vertex.color = {1.0f, 1.0f, 1.0f};

            if (uniqueVertices.count(vertex) == 0)
            {
                uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                vertices.push_back(vertex);//vertices.emplace_back(vertex);
            }
           indices.push_back(uniqueVertices[vertex]);//indices.emplace_back(uniqueVertices[vertex]);
        }
    }

}

void Application::render(void)
{
    const GLfloat color[] =
    {
        static_cast<GLfloat>(std::sin(glfwGetTime())) * 0.5f + 0.5f,
        static_cast<GLfloat>(std::cos(glfwGetTime())) * 0.5f - 0.5f,
        static_cast<GLfloat>(std::cos(glfwGetTime() * std::sin(glfwGetTime()))) * 0.5f,
        1.0f
    };
    const GLfloat clearbuffer[] =
    {
        static_cast<GLfloat>(std::cos(glfwGetTime())) * 0.5f + 0.5f,
        static_cast<GLfloat>(std::sin(glfwGetTime())) * 0.5f - 0.5f,
        static_cast<GLfloat>(std::cos(glfwGetTime() * std::sin(glfwGetTime()))) * 0.5f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, clearbuffer);
    // glClearColor(1.0f, 0.0f, 0.03f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

//int a{};glGetIntegerv(GL_NUM_EXTENSIONS, &a);std::cout << "EXtensions " << a << std::endl;
    // glPatchParameteri(GL_PATCH_VERTICES, 18);// Makes tesselation to not work
    // Use the program object we created earlier for rendering
    ShaderInfo defaultInfo{};
    ShaderInfo demo{};
    // defaultInfo information
    {
        defaultInfo.vertexFile = "shaders/example.vert";

        defaultInfo.fragmentFile = "shaders/example.frag";
        defaultInfo.tesselationControlShaderFile = "shaders/example.tesc";
        defaultInfo.tesselationEvaluationShaderFile = "shaders/example.tese";
        defaultInfo.geometryFile = "shaders/example.geom";
        defaultInfo.shaderState = ShaderState::vertFrag;

        demo.vertexFile = "shaders/demo.vert";

        demo.fragmentFile = "shaders/example.frag";
        demo.tesselationControlShaderFile = "shaders/example.tesc";
        demo.tesselationEvaluationShaderFile = "shaders/example.tese";
        demo.shaderState = ShaderState::tesselation;
    }
    Shader shaderProgram{ defaultInfo }, shaderDemo{ (defaultInfo) }; 
                //,shaderDemo2{ std::move(shaderProgram) };
//    shaderDemo = (shaderProgram);

    glBindVertexArray(this->vao);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // glPatchParameteri(GL_PATCH_VERTICES, 18);// Makes tesselation to not work
    // Use the program object we created earlier for rendering
    glUseProgram(shaderDemo.getProgram());
//     glUseProgram(shaderProgram);

    // Draw one point
    glPointSize(5.0f);
    GLfloat attrib[] = 
    { 
        static_cast<float>(std::sin(glfwGetTime())) * 0.5f,
        static_cast<float>(std::cos(glfwGetTime())) * 0.6f,
        0.0f, 0.0f
    };
    // Update the value of input attribute 0
    glVertexAttrib4fv(0, attrib);
    
    GLuint buffer;
    glCreateBuffers(1, &buffer);
// Specify the data store parameters for the buffer
glNamedBufferStorage(
                    buffer,       // Name of the buffer
                    1024 * 1024,  // 1 MiB of space
                    nullptr,         // No initial data
                    GL_MAP_WRITE_BIT); // Allow map for writing
// Now bind it to the context using the GL_ARRAY_BUFFER binding point
glBindBuffer(GL_ARRAY_BUFFER, buffer);
// This is the data that we will place into the buffer object
static constexpr float data[] =
{
    0.25, -0.25, 0.5, 1.0,
   -0.25, -0.25, 0.5, 1.0,
    0.25,  0.25, 0.5, 1.0
};
// Get a pointer to the buffer's data store
void *ptr = glMapNamedBuffer(buffer, GL_WRITE_ONLY);
// Copy our data into it
memcpy(ptr, data, sizeof(data));
// Tell OpenGl we are done with the pointer
glUnmapNamedBuffer(buffer);
// First, bind a vertex buffer to the VAO
glVertexArrayVertexBuffer(vao, // Vertex array object
                          0, // First vertex buffer binding
                          buffer,// Buffer object
                          0, // Start from the beginning
                          sizeof(glm::vec4)); // Each vertex is one vec4

// Now, describe the data to OpenGL, tell it where automatic
// vertex fetching for the specified attribute
glVertexArrayAttribFormat(this->vao, // Vertex array object
                          0,        // First Attribute
                          4,         // Four Components
                          GL_FLOAT,  // Floating point data for floats
                          GL_FALSE,  // Normalized- Ignored
                          0         // First elments of the vertex
);
glVertexArrayAttribBinding(this->vao, 0, 0);
glEnableVertexArrayAttrib(vao, 0);

// Put the data into the buffer at offset zero
glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);
// send color to Fragment shader
    glUniform4fv(glGetUniformLocation(shaderProgram.getProgram(), "color"), 1, &color[0]);
    glVertexAttrib4fv(1, color);this->loadModel("viking_room.obj");
    // Draw a triangle with 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
