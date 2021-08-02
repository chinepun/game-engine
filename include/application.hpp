#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    bool operator==(const Vertex& other) const
    {
        return this->pos == other.pos && this->color == other.color && this->texCoord == other.texCoord;
    }

};

class Application
{
public:
    Application(void);
    void render(void);
    void loadModel(const std::string& MODEL_PATH);
    // [[nodiscard]] inline Shader getShaderProgram(){return this->shaderProgram;}
    ~Application(void);
private:
    GLuint vao;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices; 
};

#endif
