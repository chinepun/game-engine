#include "shader.hpp"
#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include "tpf_type_name.h"

Shader::Shader(const ShaderInfo& shaderCreateInfo)
{
    this->shaderInfo = shaderCreateInfo;
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        this->vertexShader = compileShader(GL_VERTEX_SHADER, this->shaderInfo.vertexFile);
        this->fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->shaderInfo.fragmentFile);
        this->tesselationShaderTCS =  compileShader(GL_TESS_CONTROL_SHADER, this->shaderInfo.tesselationControlShaderFile);
        this->tesselationShaderTES = compileShader(GL_TESS_EVALUATION_SHADER, this->shaderInfo.tesselationEvaluationShaderFile);
        break;
    case ShaderState::geometry:
        this->vertexShader = compileShader(GL_VERTEX_SHADER, this->shaderInfo.vertexFile);
        this->fragmentShader =  compileShader(GL_FRAGMENT_SHADER, this->shaderInfo.fragmentFile);      
        this->geometryShader = compileShader(GL_GEOMETRY_SHADER, this->shaderInfo.geometryFile);
        break;
    case ShaderState::geometryAndTesselation:
        this->vertexShader = compileShader(GL_VERTEX_SHADER, this->shaderInfo.vertexFile);
        this->fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->shaderInfo.fragmentFile);
        this->geometryShader = compileShader(GL_GEOMETRY_SHADER, this->shaderInfo.geometryFile);
        this->tesselationShaderTCS = compileShader(GL_TESS_CONTROL_SHADER, this->shaderInfo.tesselationControlShaderFile); 
        this->tesselationShaderTES = compileShader(GL_TESS_EVALUATION_SHADER, this->shaderInfo.tesselationEvaluationShaderFile);
        break;
    default:// ShaderState::vertFrag
        this->vertexShader = compileShader(GL_VERTEX_SHADER, this->shaderInfo.vertexFile);
        this->fragmentShader = compileShader(GL_FRAGMENT_SHADER, this->shaderInfo.fragmentFile);
        break;
    }
    this->linkShaders();
}

Shader::Shader(const Shader& Copy)
: shaderInfo{ Copy.shaderInfo }, program{ Copy.program }
{
    std::cout << "Copy Constructor Called\t";
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->tesselationShaderTCS = Copy.tesselationShaderTCS;
        this->tesselationShaderTES = Copy.tesselationShaderTES;
        break;
    case ShaderState::geometry:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->geometryShader = Copy.geometryShader;
        break;
    case ShaderState::geometryAndTesselation:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->geometryShader = Copy.geometryShader;
        this->tesselationShaderTCS = Copy.tesselationShaderTCS; 
        this->tesselationShaderTES = Copy.tesselationShaderTES;
        break;
    default:// ShaderState::vertFrag
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        break;
    }
}

Shader& Shader::operator=(const Shader& Copy)
{
    std::cout << "Copy Assignment Called\t";
    this->shaderInfo = Copy.shaderInfo;
    this->program = Copy.program;
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->tesselationShaderTCS = Copy.tesselationShaderTCS;
        this->tesselationShaderTES = Copy.tesselationShaderTES;
        break;
    case ShaderState::geometry:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->geometryShader = Copy.geometryShader;
        break;
    case ShaderState::geometryAndTesselation:
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        this->geometryShader = Copy.geometryShader;
        this->tesselationShaderTCS = Copy.tesselationShaderTCS; 
        this->tesselationShaderTES = Copy.tesselationShaderTES;
        break;
    default:// ShaderState::vertFrag
        this->vertexShader = Copy.vertexShader;
        this->fragmentShader = Copy.fragmentShader;
        break;
    }
    
    return *this;
}

Shader::Shader(Shader&& Move)
: shaderInfo{ std::move(Move.shaderInfo) }, program{ std::move(Move.program) }
{
    std::cout << "Move Constructor Called\t";
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->tesselationShaderTCS = std::move(Move.tesselationShaderTCS);
        this->tesselationShaderTES = std::move(Move.tesselationShaderTES);
        break;
    case ShaderState::geometry:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->geometryShader = std::move(Move.geometryShader);
        break;
    case ShaderState::geometryAndTesselation:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->geometryShader = std::move(Move.geometryShader);
        this->tesselationShaderTCS = std::move(Move.tesselationShaderTCS); 
        this->tesselationShaderTES = std::move(Move.tesselationShaderTES);
        break;
    default:// ShaderState::vertFrag
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        break;
    }

}

Shader& Shader::operator=(Shader&& Move)
{
    std::cout << "Move Assignment Called1\t";

    this->shaderInfo = std::move(Move.shaderInfo);
    this->program = std::move(Move.program);
    std::cout << "Move Assignment Called\t" << Tpf_GetTypeCategory(Move.shaderInfo) << " MA\n";
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->tesselationShaderTCS = std::move(Move.tesselationShaderTCS);
        this->tesselationShaderTES = std::move(Move.tesselationShaderTES);
        break;
    case ShaderState::geometry:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->geometryShader = std::move(Move.geometryShader);
        break;
    case ShaderState::geometryAndTesselation:
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        this->geometryShader = std::move(Move.geometryShader);
        this->tesselationShaderTCS = std::move(Move.tesselationShaderTCS); 
        this->tesselationShaderTES = std::move(Move.tesselationShaderTES);
        break;
    default:// ShaderState::vertFrag
        this->vertexShader = std::move(Move.vertexShader);
        this->fragmentShader = std::move(Move.fragmentShader);
        break;
    }

    return *this;
}

[[nodiscard]] GLuint Shader::compileShader(GLenum shaderType, const std::string &shaderFileLocation)
// shaderType - GL_VERTEX_SHADER or GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER or GL_TESS_CONTROL_SHADER, or
//              GL_TESS_EVALUATION_SHADER
// shaderFileLocation - Location of the shader file
{
    GLuint shader; // vertex or fragment or geometry or tesselation shaderID to be returned at end of function
    std::string shaderCodeString; // stores the shader code in string format
    const char* shaderCode; // converts the shader code into const char*

    std::ifstream shaderFile(shaderFileLocation);// Opens vertex shader
    if (!shaderFile.is_open())  std::cout << "Couldn't Open file " << shaderFileLocation << '.';

    std::stringstream stream;// stores shader code in a stream
    stream << shaderFile.rdbuf();
    shaderCodeString = stream.str();// extracts the shader code from the stream
    stream.str( std::string() );// clear the stream containing the shader
    stream.clear();// To be sure stream is cleared
    shaderFile.close();// close the current file

    shaderCode = shaderCodeString.c_str();// converts vertex shader code to const char*
 
    // Creating and Compilation of Shader code
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // error handling shader code
    int success;// for checking if compilation of shader is succesful
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)// shader code didn't compile
    {
        int error;// stores error message in address
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error);
        std::unique_ptr<char> message = std::make_unique<char>(error * sizeof(char));
        glGetShaderInfoLog(shader, error, &error, message.get());
        std::cout << "shader could not compile.\nError : " << message.release();
        glDeleteShader(shader);
        return EXIT_FAILURE;
    }

    return shader;
}

void Shader::linkShaders(void)
{
    // Create program, attach shaders to it, and link it
    this->program = glCreateProgram();
    // Attach shaders to the program
    switch (this->shaderInfo.shaderState)
    {
    case ShaderState::tesselation:
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        glAttachShader(this->program, tesselationShaderTCS);
        glAttachShader(this->program, tesselationShaderTES);
        break;
    case ShaderState::geometry:
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        glAttachShader(this->program, geometryShader);
        break;
    case ShaderState::geometryAndTesselation:
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        glAttachShader(this->program, tesselationShaderTCS);
        glAttachShader(this->program, tesselationShaderTES); 
        glAttachShader(this->program, geometryShader);
        break;
    default:
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        break;
    }
    // link shaders
    glLinkProgram(this->program);

    // error handling for linking
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int error;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &error);
        std::unique_ptr<char> message = std::make_unique<char>(error * sizeof(char));
        glGetProgramInfoLog(program, error, &error, message.get());
        std::cout << "Could not link program\nError : " << message.release();
        glDeleteProgram(program);
    }

    // Clean up resources
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    glDeleteShader(this->geometryShader);
    glDeleteShader(this->tesselationShaderTCS);
    glDeleteShader(this->tesselationShaderTES);

    glDetachShader(this->program, this->vertexShader);
    glDetachShader(this->program, this->fragmentShader);
    glDetachShader(this->program, this->tesselationShaderTCS);
    glDetachShader(this->program, this->tesselationShaderTES); 
    glDetachShader(this->program, this->geometryShader);
 
}

// Conversion of Shader into Gluint but gives warning
Shader::operator GLuint()
{
    std::cout << "\nWarning:Narrowing Conversion from Shader to GLuint."
              << "\nReturning Shader Program Currently.";
    return this->program;
}

Shader::~Shader()
{
    glDeleteProgram(this->program);
}