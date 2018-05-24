#ifndef OPENGLTEST_ASSIST_H
#define OPENGLTEST_ASSIST_H

#include "OpenGlTest1.h"

GLuint curProgram;
static GLfloat glopacity = 0.0f;
void setCurProgram(GLuint p)
{
    curProgram = p;
}
void key_callback_1(GLFWwindow* window, int key, int scancode, int action, int mode);
void key_callback_1(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        GLint num1 = glGetUniformLocation(curProgram, "num1");
        glopacity = glopacity + 0.1f;
        glUniform2f(num1, glopacity,1.0f);
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        GLint num1 = glGetUniformLocation(curProgram, "num1");
        glopacity = glopacity - 0.1f;
        glUniform2f(num1, glopacity, 1.0f);
    }
}

#endif //OPENGLTEST_ASSIST_H