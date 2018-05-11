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

// ��ȡ�����������
GLuint getVAO()
{
    // ����λ��
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,   // ���Ͻ�
        0.5f, -0.5f, 0.0f,  // ���½�
        -0.5f, -0.5f, 0.0f, // ���½�
        -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    GLuint indices[] = { // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };

    // ���㻺�����
    GLuint VBO;
    glGenBuffers(1, &VBO);

    // �����������
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // �����������
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // 1. ��VAO
    glBindVertexArray(VAO);

    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    // 3. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //4. ���VAO
    glBindVertexArray(0);
    return VAO;
}

GLuint getShaderProgram()
{
    string sz1,sz2;
    const char* vertexShaderSource = getStrFromFile("vertexShader.txt", sz1);
    const char* fragmentShaderSource = getStrFromFile("fragmentShader.txt", sz2);

    //----- ������ɫ�� ----------------//
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //----- ������־ Ƭ����ɫ��һ�� ----------------//
    GLint suc;
    GLchar infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &suc);
    if (!suc)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << endl;
    }

    //----- Ƭ����ɫ�� ----------------//
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //----- ��ɫ������ ----------------//
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
    glfwInit();// ��ʼ��glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// ��ʼ��OpenGL���ΰ汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ��ʼ��OpenGLģʽ ʹ�ú���ģʽ
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);// ���ò������û����Ĵ��ڴ�С

    // ��������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl_Project1", nullptr, nullptr);
    if (window == nullptr){   
        cout << "Failed to Create GLFW Window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);// ���õ�ǰ����Ϊ��ǰ�߳�������

    // ��:GLEW����OpenGL����ָ��ʹ���ִ���������GGL_FALSE�Ļ�ʹ�ú���ģʽ���������
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
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
    
    GLuint VAO = getVAO();
    GLuint shaderProgram = getShaderProgram();

    // ���û���ͼԪ��ʽ GL_LINE �� GL_FILL ���
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // ���glfw�Ƿ�Ҫ���˳�
    while (glfwWindowShouldClose(window) == false)
    {
        // �¼������� ����¼�(�������롢����ƶ���)���ö�Ӧ�ص�����
        glfwPollEvents();

        // ������պ� �������ɫ 
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        // ��ջ���
        glClear(GL_COLOR_BUFFER_BIT);   // GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT��

        // �������β���
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);

        // �����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
        glfwSwapBuffers(window);
    }

    // ��ֹ����
    glfwTerminate();
    return 0;
}
