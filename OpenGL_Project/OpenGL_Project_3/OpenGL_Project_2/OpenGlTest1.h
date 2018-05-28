#ifndef OPENGLTEST1_H
#define OPENGLTEST1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// GLEW OpenGL Extension Wrangler Library ����OpenGLָ��
#define GLEW_STATIC
#include <GL/eglew.h>

// GLFW
// GLFW��һ��ר�����OpenGL��C���Կ⣬���ṩ��һЩ��Ⱦ�������������޶ȵĽӿڡ��������û�����OpenGL�����ģ����崰�ڲ����Լ������û����룬������������Ҫ��
#include <GLFW/glfw3.h>

// ͼƬ���ؿ�
#include <SOIL/SOIL.h>
#include "Shader.h"
//#include "OpenGlTest1_Assist.h"

// GLM ��ѧ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// �������Ը���
//GLint nrAttributes;
//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
//// ��ע��������Ǿ����ʼ����һ�����ӣ����ʹ�õ���0.9.9�����ϰ汾
//// �������д������Ҫ��Ϊ:
//// glm::mat4 trans = glm::mat4(1.0f)
//// ֮�󽫲��ٽ�����ʾ
//glm::mat4 trans;
//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//vec = trans * vec;
//std::cout << vec.x << vec.y << vec.z << std::endl;

#endif//OPENGLTEST1_H