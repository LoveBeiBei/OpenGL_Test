#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "OpenGlTest1.h"
#include "OpenGlTest1_Assist.h"
#include "VertexShader_1.h"

const char* getStrFromFile(string fileName, string& str)
{
    ifstream in(fileName, ios::in);
    istreambuf_iterator<char> beg(in), end;
    string strOut(beg, end);
    str = strOut;
    in.close();
    return str.c_str();
}

// 获取顶点数组对象
GLuint getVAO()
{
    // 顶点位置
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    GLuint indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    // 顶点缓冲对象
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // 索引缓冲对象
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // 顶点数组对象
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // 1. 绑定VAO
    glBindVertexArray(VAO);

    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //4. 解绑VAO
    glBindVertexArray(0);
    return VAO;
}

GLuint getShaderProgram()
{
    string sz1,sz2;
    const char* vertexShaderSource = getStrFromFile("vertexShader.txt", sz1);
    const char* fragmentShaderSource = getStrFromFile("fragmentShader.txt", sz2);

    //----- 顶点着色器 ----------------//
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //----- 错误日志 片段着色器一样 ----------------//
    GLint suc;
    GLchar infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &suc);
    if (!suc)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << endl;
    }

    //----- 片段着色器 ----------------//
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //----- 着色器程序 ----------------//
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    return shaderProgram;
}

int main()
{
    glfwInit();// 初始化glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 初始化OpenGL主次版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// 初始化OpenGL模式 使用核心模式
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);// 设置不允许用户更改窗口大小

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl_Project1", nullptr, nullptr);
    if (window == nullptr){   
        cout << "Failed to Create GLFW Window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);// 设置当前窗口为当前线程上下文

    // 坑:GLEW管理OpenGL函数指针使用现代化技术，GGL_FALSE的话使用核心模式会出现问题
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
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
    
    GLuint VAO = getVAO();
    GLuint shaderProgram = getShaderProgram();

    // 配置绘制图元方式 GL_LINE 线 GL_FILL 填充
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // 检查glfw是否被要求退出
    while (glfwWindowShouldClose(window) == false)
    {
        // 事件处理函数 检查事件(键盘输入、鼠标移动等)调用对应回调函数
        glfwPollEvents();

        // 设置清空后 缓冲填充色 
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        // 清空缓冲
        glClear(GL_COLOR_BUFFER_BIT);   // GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT。

        // 画三角形操作
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);

        // 函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
        glfwSwapBuffers(window);
    }

    // 终止窗口
    glfwTerminate();
    return 0;
}
