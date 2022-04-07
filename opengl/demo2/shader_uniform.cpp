#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

//设置窗口大小回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//接收输入按键
void processInput(GLFWwindow* window);

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "learn opengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "创建创建失败！！" <<  std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "初始化 GLAD 失败" << std::endl;
        return -1;
    }

    glViewport(0, 0, 600, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //顶点着色器
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   vertexColor = vec4(1.0, 0.5, 0.4, 1.0);\n"
        "}\0";

    //片段着色器
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "//in vec4 vertexColor;\n"
        "uniform vec4 ourColor; //可以从外部设置颜色 全局属性\n"
        "void main()\n"
        "{\n"
        "    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "   //FragColor = vertexColor; // 从顶点着色器接收\n"
        "   FragColor = ourColor;\n"
        "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    //检查编译错误
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (! success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "顶点着色器编译失败：" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //检查编译错误
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (! success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "片段着色器编译失败：" << infoLog << std::endl;
    }

    //着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //检查错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (! success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "着色器程序链接失败：" << infoLog << std::endl;
    }
    //链接成功删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    //循环渲染
    while (! glfwWindowShouldClose(window))
    {
        processInput(window);

        //重新绘制颜色
        glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);

        //设置 outColor 颜色
        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //// now render the triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time 

        glfwPollEvents();
        glfwSwapBuffers(window);
        
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//g++ glad.c helloWorld.cpp -o main -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXcursor -lXinerama