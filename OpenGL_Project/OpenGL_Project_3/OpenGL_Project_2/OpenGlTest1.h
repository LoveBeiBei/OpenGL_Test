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

// GLM 数学库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// 顶点属性个数
//GLint nrAttributes;
//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
//// 下面这行代码就需要改为:
//// glm::mat4 trans = glm::mat4(1.0f)
//// 之后将不再进行提示
//glm::mat4 trans;
//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//vec = trans * vec;
//std::cout << vec.x << vec.y << vec.z << std::endl;

#endif//OPENGLTEST1_H