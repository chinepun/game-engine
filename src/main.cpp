#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <iostream>

#include "application.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << "\nFramebuffer resized to " << '(' << 0 << ',' << 0
              << ')' << "->" << '(' << width << ',' << height << ')' << '\n';
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::function<void(GLFWwindow*, int, int)> m = framebuffer_size_callback;


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)->void
    { 
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
        std::cout << "\nFramebuffer resized to " << '(' << 0 << ',' << 0
                << ')' << "->" << '(' << width << ',' << height << ')' << '\n';
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
   int present = glfwJoystickPresent(GLFW_JOYSTICK_1); 
    
    while(!glfwWindowShouldClose(window))
    {
        // If JoyStick is Present
        if (present)
        {
            std::cout << "Game Pad 1 is Connected. Status:" << present << "\n";
 
            int axesCount;
            const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            std::cout << "number of axes available " << axesCount << '\n';
            
            std::cout << '\n';
            std::cout << "First Axes(Left) " << axes[0] << '\t' << "\tSecond Axes(Left) " << axes[1]
                      << "\nThird Axes(Right) " << axes[2] << '\t' << "\tFourth Axes(Right) " << axes[3]
                      << "\nFifth Axes(L2) " << axes[4] << '\t' << "\tSixth Axes(R2) " << axes[5];
/*
Note:If Analog is turned off, Then Right Analog overwrites buttons(1, 2, 3 & 4)
*/
            std::cout << '\n';
            int buttonCount;
            const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
            if (GLFW_PRESS == buttons[0])    std::cout << "1(+Y) Pressed\n";
            else if (GLFW_PRESS == buttons[1])    std::cout << "2(+X) Pressed\n";
            else if (GLFW_PRESS == buttons[2])    std::cout << "3(-Y) Pressed\n";
            else if (GLFW_PRESS == buttons[3])    std::cout << "4(-X) PRessed\n";
            else if (GLFW_PRESS == buttons[4])    std::cout << "L1/LB Pressed\n";
            else if (GLFW_PRESS == buttons[5])    std::cout << "R1/RB Pressed\n";
            else if (GLFW_PRESS == buttons[6])    std::cout << "L2/LT Pressed\n";
            else if (GLFW_PRESS == buttons[7])    std::cout << "R2/RT Pressed\n";
            else if (GLFW_PRESS == buttons[8])    std::cout << "Select(Left) Pressed\n";
            else if (GLFW_PRESS == buttons[9])    std::cout << "Start(Right) Pressed\n";
            else if (GLFW_PRESS == buttons[10])   std::cout << "Left Analog(LS) Pressed\n";
            else if (GLFW_PRESS == buttons[11])   std::cout << "Right Analog(RS) Pressed\n"; 
            else if (GLFW_PRESS == buttons[12])   std::cout << "Up Arrow(Analog must be turned on) Presssed\n";
            else if (GLFW_PRESS == buttons[13])   std::cout << "Right Arrow(Analog must be turned on) Pressed\n";
            else if (GLFW_PRESS == buttons[14])   std::cout << "Down Arrow(Analog must be turned on) Pressed\n";
            else if (GLFW_PRESS == buttons[15])   std::cout << "Left Arrow(Analog must be turned on) Pressed\n";
            else std::cout << "not Detected\n";
        
            const char *name = glfwGetJoystickName(GLFW_JOYSTICK_1);
            std::cout << "\nName " << name << " has " << buttonCount << " buttons" << '\n';
        
            std::cout << "-------------------------\n"; 
        }
        Application myApplication;
        processInput(window);
        myApplication.render();
/*
The glfwSwapBuffers will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW’s
window) that is used to render to during this render iteration and show it as output to the screen.
*/
        glfwSwapBuffers(window);
    /*
    The glfwPollEvents function checks if any events are
    triggered (like keyboard input or mouse movement events), updates the window state, and calls the
    corresponding functions (which we can register via callback methods).
*/
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}