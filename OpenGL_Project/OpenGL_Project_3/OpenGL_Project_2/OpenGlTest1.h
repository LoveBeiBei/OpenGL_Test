#ifndef OPENGLTEST1_H
#define OPENGLTEST1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// GLEW OpenGL Extension Wrangler Library 管理OpenGL指针
#define GLEW_STATIC
#include <GL/eglew.h>

// GLFW
// GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文，定义窗口参数以及处理用户输入，这正是我们需要的
#include <GLFW/glfw3.h>

// 图片加载库
#include <SOIL/SOIL.h>
#include "Shader.h"
//#include "OpenGlTest1_Assist.h"



// 顶点属性个数
//GLint nrAttributes;
//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

#endif//OPENGLTEST1_H