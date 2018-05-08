

#include<iostream>
#include "OpenGlTest1_Assist.h"

int main()
{
    // ��ʼ��glfw
    glfwInit();
    // ��ʼ��OpenGL���ΰ汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ��ʼ��OpenGLģʽ ʹ�ú���ģʽ
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ���ò������û����Ĵ��ڴ�С
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // ��������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl_Project1", nullptr, nullptr);
    if (window == nullptr)
    {   
        std::cout << "Failed to Create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // ���õ�ǰ����Ϊ��ǰ�߳�������
    glfwMakeContextCurrent(window);

    // ��:GLEW����OpenGL����ָ��ʹ���ִ���������GGL_FALSE�Ļ�ʹ�ú���ģʽ���������
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // ��ȡwindow��С �������õ�800 600
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    // ����opengl��Ⱦ������С
    glViewport(0, 0, width, height);   //ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�

    // ע����̻ص�����
    glfwSetKeyCallback(window, key_callback);
    
    // ���glfw�Ƿ�Ҫ���˳�
    while (glfwWindowShouldClose(window) == false)
    {
        // �¼������� ����¼�(�������롢����ƶ���)���ö�Ӧ�ص�����
        glfwPollEvents();

        // ������պ� �������ɫ 
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        // ��ջ���
        glClear(GL_COLOR_BUFFER_BIT);   // GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��

        // �����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
        glfwSwapBuffers(window);

    }

    // ��ֹ����
    glfwTerminate();
    return 0;
}