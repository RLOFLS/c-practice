#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../common/shader.h"
#include "../common/camera_origin.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../common/stb_image.h"

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback( GLFWwindow * window, int button, int action, int mods);

//相机
glcar::CameraOrigin camera(glm::vec3(0.0f, 0.0f, 10.0f));
unsigned int lastX = SRC_WIDTH / 2;
unsigned int lastY = SRC_HEIGHT / 2;
bool firstMouse = true;
bool mouseRightmove = false;

unsigned int loadTexture(char const * path);

float rgb(float val);

float lightX = 12.0f;

//定向光/
int main()
{
    //初始窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "light-exercise", NULL, NULL);
    if (window == NULL) {
        std::cout << "创建窗口失败" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //设置改变窗口大小回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //设置鼠标移动回调
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    //设置鼠标滚轮回调
    glfwSetScrollCallback(window, scroll_callback);

    //鼠标点击事件
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    //设置隐藏树光标
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    //glad加载所有opengl函数指针
    if (! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "glad加载初始失败" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //正方体着色器程序
    //平行光
    //Shader cubeShader("exercise3.vert", "exercise3.frag");

    //点光
    //Shader cubeShader("exercise3.vert", "exercise3_point.frag");

    //聚光灯
    Shader cubeShader("exercise3.vert", "exercise3_spot.frag");

    //光方块
    Shader lightCubeShader("exercise_cube_light.vert", "exercise_cube_light.frag");

    //正方形顶点
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    unsigned int VBO, cubeVAO, lightVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //光方块
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int diffuseMap = loadTexture("container2.png");
    unsigned int specularMap = loadTexture("container2_specular.png");

    //发光
    unsigned int emissionMap = loadTexture("matrix.jpg");

    // shader configuration
    // --------------------
    cubeShader.use(); 
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);
    cubeShader.setInt("material.emission", 2);

    glm::vec3 position[] = {
        glm::vec3(0.0f),
        glm::vec3(2.0f, 3.0f, -2.0f),
        glm::vec3(-1.0f, -1.5f, 3.0f),
        glm::vec3(-3.0f, 2.0f, 1.0f)
    };

    //渲染循环
    while (! glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        float angle = 20.0f;
        glm::vec3 lightPos = glm::vec3(lightX, 6.0f, 0.0f);

        glm::mat4 lightmodel(1.0f);
        lightmodel = glm::scale(lightmodel, glm::vec3(0.3f, 0.3f, 0.3f));
        //lightmodel = glm::rotate(lightmodel, (float)glfwGetTime() * 2.0f, glm::vec3(0.2f, 1.0f, 0.0f));
        lightmodel = glm::translate(lightmodel, lightPos);

        lightPos = glm::vec3(lightmodel[3][0], lightmodel[3][1] , lightmodel[3][2]);

        //world
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);
        //model
        glm::mat4 model = glm::mat4(1.0f);

        cubeShader.use();
        
       // 
        //平行光
        //cubeShader.setVec3("light.direction", glm::vec3(0.0f, 2.0f, 5.0f));

        //点光
        // cubeShader.setVec3("light.position", lightPos);
        // cubeShader.setFloat("light.constant",  1.0f);
        // cubeShader.setFloat("light.linear",    0.014f);
        // cubeShader.setFloat("light.quadratic", 0.007f);

        //聚光灯
        cubeShader.setVec3("light.position", lightPos);
        cubeShader.setVec3("light.direction", glm::vec3(12.0f, 6.0f, 0.0f));
        cubeShader.setFloat("light.cutOff",   glm::cos(glm::radians(6.0f)));
        //边缘平滑
        cubeShader.setFloat("light.outerCutOff", glm::cos(glm::radians(6.7f)));
        cubeShader.setFloat("light.constant",  1.0f);
        cubeShader.setFloat("light.linear",    0.014f);
        cubeShader.setFloat("light.quadratic", 0.007f);

         // light properties
        cubeShader.setVec3("light.ambient", lightColor * glm::vec3(0.2f)); 
        cubeShader.setVec3("light.diffuse", lightColor * glm::vec3(0.7f));
        cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        cubeShader.setVec3("viewPos", camera.position);

        // material properties
        cubeShader.setFloat("material.shininess", 64.0f);

        cubeShader.setMat4("view", camera.getViewMatrix());
        cubeShader.setMat4("projection", projection);

        for (int i = 0; i < 4; i++)
        {
            float angle = 10.0f;
            glm::vec3 pos = position[i];
            model = glm::mat4(1.0f);
            //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::rotate(model, glm::radians(angle * i), glm::vec3(1.0f, 1.0f, 1.0f));
            model = glm::translate(model, pos);
            cubeShader.setFloat("time", (float)glfwGetTime());
            cubeShader.setMat4("model", model);

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);

            // bind specular map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);

            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, emissionMap);

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //光方块
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", camera.getViewMatrix());
        lightCubeShader.setMat4("model", lightmodel);
        lightCubeShader.setVec3("lightColor", lightColor);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    
    glfwTerminate();
    return 0;
}

float rgb(float val) 
{
    if(val <= 127)
        return 0.5 * val/127.0;
    else
        return 0.5 + 0.5 * val/128.0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_pos_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (! mouseRightmove) {
        return;
    }

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset, false);
}

void mouse_button_callback( GLFWwindow * window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        lastX = x;
        lastY = y;
        mouseRightmove = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        mouseRightmove = false;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        lightX -= 0.1;
    } 

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        lightX += 0.1;
    } 
    
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}