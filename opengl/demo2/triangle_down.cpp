#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

//设置窗口大小回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//接收输入按键
void processInput(GLFWwindow* window);
//调整顶点着色器，使三角形倒置
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

    //着色器程序
    Shader shaderProgram = Shader("triangle_down.vert", "triangle_down.frag"); 

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right 
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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
        shaderProgram.use();
        //过统一指定水平偏移，并使用此偏移值在顶点着色器中将三角形移动到屏幕的右侧
        //shaderProgram.setFloat("xOffset", 0.5);

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
    shaderProgram.destory();

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