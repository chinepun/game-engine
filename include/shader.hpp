#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
//  vertFrag - Default no of shaders
//  tesselation - Contains default shaders with tesselation shader only
//  geometry - Contains default shaders with geometry shader only
//  geometryAndTesselation - Contains default shaders with geometry and Tesselation shaders
enum class ShaderState { vertFrag, tesselation, geometry, geometryAndTesselation };    


struct ShaderInfo
{
    std::string vertexFile{};
    std::string fragmentFile{};
    std::string tesselationControlShaderFile{};
    std::string tesselationEvaluationShaderFile{};
    std::string geometryFile{};

    ShaderState shaderState;
};

class Shader
{
public:
    explicit Shader(const ShaderInfo& shaderCreateInfo);
    Shader(const Shader& Copy);
    Shader& operator=(const Shader& Copy);
    Shader(Shader&& Move);
    Shader& operator=(Shader&&);
    ~Shader();
    [[nodiscard]] inline GLuint getProgram(){return this->program;}
    operator GLuint [[nodiscard]]();
protected:
// shaderType - GL_VERTEX_SHADER or GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER or GL_TESS_CONTROL_SHADER, or
//              GL_TESS_EVALUATION_SHADER 
    // shaderFileLocation - Location of the shader file
    [[nodiscard]] GLuint compileShader(GLenum shaderType, const std::string &shaderFileLocation);
    void linkShaders(void);
private:
    GLuint program;
    GLuint vertexShader, fragmentShader, tesselationShaderTCS, tesselationShaderTES, geometryShader;
    ShaderInfo shaderInfo;
};

#endif