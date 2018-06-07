

#include "OpenGlTest1.h"
#include "OpenGlTest1_Assist.h"
using namespace std;

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
        //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 3.0f, 3.0f,   // ����
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 3.0f, 0.0f,   // ����
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // ����
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 3.0f    // ����
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
    //location = 0 vec3��3��floatֵ GL_FLOAT GL_FALSE����׼�� ����һ����ֵ�Ĳ��� �ڱ����ݵ�ƫ����
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //4. ���VAO
    glBindVertexArray(0);
    return VAO;
}

GLuint getTexture(string strImageName)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_MIRRORED_REPEAT);  // �ͽ�
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_MIRRORED_REPEAT);   // ����

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // ���ز���������
    int width, height;
    unsigned char* image = SOIL_load_image(strImageName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
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
    int framewidth, frameheight;
    glfwGetFramebufferSize(window, &framewidth, &frameheight);
    // ����opengl��Ⱦ������С
    glViewport(0, 0, framewidth, frameheight);   //ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�

    // ע����̻ص�����
    glfwSetKeyCallback(window, key_callback_1);
    
    GLuint VAO = getVAO();
    Shader shader("vertexShader.vs","fragmentShader.frag");
    setCurProgram(shader.Program);
    GLuint texture1 = getTexture("Image/container.jpg");
    GLuint texture2 = getTexture("Image/awesomeface.png");
    
    // ���û���ͼԪ��ʽ GL_LINE �� GL_FILL ���
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
        shader.Use();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shader.Program, "ourTexture2"), 1);
        
        glm::mat4 trans;
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        unsigned int transformLoc = glGetUniformLocation(shader.Program, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glm::mat4 model;
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.Program, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view;
        // ע�⣬���ǽ�����������Ҫ�����ƶ������ķ������ƶ���
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        int viewLoc = glGetUniformLocation(shader.Program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)framewidth/frameheight, 0.1f, 100.0f);
        int projectionLoc = glGetUniformLocation(shader.Program, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
