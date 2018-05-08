

#include<iostream>
#include "OpenGlTest1_Assist.h"

int main()
{
    // 初始化glfw
    glfwInit();
    // 初始化OpenGL主次版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 初始化OpenGL模式 使用核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 设置不允许用户更改窗口大小
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl_Project1", nullptr, nullptr);
    if (window == nullptr)
    {   
        std::cout << "Failed to Create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 设置当前窗口为当前线程上下文
    glfwMakeContextCurrent(window);

    // 坑:GLEW管理OpenGL函数指针使用现代化技术，GGL_FALSE的话使用核心模式会出现问题
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // 获取window大小 上面设置的800 600
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    // 设置opengl渲染画布大小
    glViewport(0, 0, width, height);   //前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）

    // 注册键盘回调函数
    glfwSetKeyCallback(window, key_callback);
    
    // 检查glfw是否被要求退出
    while (glfwWindowShouldClose(window) == false)
    {
        // 事件处理函数 检查事件(键盘输入、鼠标移动等)调用对应回调函数
        glfwPollEvents();

        // 设置清空后 缓冲填充色 
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        // 清空缓冲
        glClear(GL_COLOR_BUFFER_BIT);   // GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。

        // 函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);

    }

    // 终止窗口
    glfwTerminate();
    return 0;
}