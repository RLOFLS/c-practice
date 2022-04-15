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
    Shader cubeShader("exercise4_mult.vert", "exercise4_mult.frag");

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

    // shader configuration
    // --------------------
    cubeShader.use(); 
    cubeShader.setInt("material.diffuse", 0);
    cubeShader.setInt("material.specular", 1);

    glm::vec3 position[] = {
        glm::vec3(0.0f),
        glm::vec3(6.0f, 0.0f, 0.0f),
        glm::vec3(-6.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 6.0f),
        glm::vec3(0.0f, 0.0f, -6.0f),
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3(6.0f, 3.0f, 0.0f),
        glm::vec3(-6.0f, 3.0f, 0.0f),
        glm::vec3(0.0f, 3.0f, 6.0f),
        glm::vec3(0.0f, 3.0f, -6.0f),
    };
    glm::vec3 ponitLightColor[] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
    };
    
    glm::vec3 lightColor = ponitLightColor[0];
    cubeShader.setVec3("pointLights[0].position", pointLightPositions[0]);
    cubeShader.setVec3("pointLights[0].ambient", lightColor * glm::vec3(0.2f)); 
    cubeShader.setVec3("pointLights[0].diffuse", lightColor * glm::vec3(0.7f));
    cubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[0].constant",  1.0f);
    cubeShader.setFloat("pointLights[0].linear",    0.014f);
    cubeShader.setFloat("pointLights[0].quadratic", 0.007f);

    lightColor = ponitLightColor[1];
    cubeShader.setVec3("pointLights[1].position", pointLightPositions[1]);
    cubeShader.setVec3("pointLights[1].ambient", lightColor * glm::vec3(0.2f)); 
    cubeShader.setVec3("pointLights[1].diffuse", lightColor * glm::vec3(0.7f));
    cubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[1].constant",  1.0f);
    cubeShader.setFloat("pointLights[1].linear",    0.014f);
    cubeShader.setFloat("pointLights[1].quadratic", 0.007f);

    lightColor = ponitLightColor[2];
    cubeShader.setVec3("pointLights[2].position", pointLightPositions[2]);
    cubeShader.setVec3("pointLights[2].ambient", lightColor * glm::vec3(0.2f)); 
    cubeShader.setVec3("pointLights[2].diffuse", lightColor * glm::vec3(0.7f));
    cubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[2].constant",  1.0f);
    cubeShader.setFloat("pointLights[2].linear",    0.014f);
    cubeShader.setFloat("pointLights[2].quadratic", 0.007f);

    lightColor = ponitLightColor[3];
    cubeShader.setVec3("pointLights[3].position", pointLightPositions[3]);
    cubeShader.setVec3("pointLights[3].ambient", lightColor * glm::vec3(0.2f)); 
    cubeShader.setVec3("pointLights[3].diffuse", lightColor * glm::vec3(0.7f));
    cubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    cubeShader.setFloat("pointLights[3].constant",  1.0f);
    cubeShader.setFloat("pointLights[3].linear",    0.014f);
    cubeShader.setFloat("pointLights[3].quadratic", 0.007f);

    //渲染循环
    while (! glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //world
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SRC_WIDTH / (float)SRC_HEIGHT, 0.1f, 100.0f);
        //model
        glm::mat4 model = glm::mat4(1.0f);

        cubeShader.use();
        // material properties
        cubeShader.setFloat("material.shininess", 64.0f);
        cubeShader.setVec3("viewPos", camera.position);
        cubeShader.setMat4("view", camera.getViewMatrix());
        cubeShader.setMat4("projection", projection);

        //定义定向光
        glm::vec3 dirLightColor = glm::vec3(rgb(247.2), rgb(112.6), rgb(43.1));
        glm::vec3 dirLightDir = glm::vec3(0.0f, -2.0f, 0.0f);
        cubeShader.setVec3("dirLight.direction", dirLightDir);
        cubeShader.setVec3("dirLight.ambient", dirLightColor * glm::vec3(0.9f));
        cubeShader.setVec3("dirLight.diffuse", dirLightColor * glm::vec3(0.9f));
        cubeShader.setVec3("dirLight.specular", dirLightColor * glm::vec3(0.2f));

        //聚光灯
        glm::vec3 spotLightColor = glm::vec3(rgb(0.0), rgb(255.0), rgb(158.0));
        glm::vec3 spotLightPos = glm::vec3(9.0f, 0.0f, 0.0f);
        cubeShader.setVec3("spotLight.position", spotLightPos);
        cubeShader.setVec3("spotLight.direction", glm::vec3(9.0f, 0.0f, 0.0f));

        cubeShader.setVec3("spotLight.ambient", spotLightColor * glm::vec3(0.2f)); 
        cubeShader.setVec3("spotLight.diffuse", spotLightColor * glm::vec3(0.7f));
        cubeShader.setVec3("spotLight.specular", spotLightColor * glm::vec3(0.4f));

        cubeShader.setFloat("spotLight.cutOff",   glm::cos(glm::radians(9.0f)));
        cubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(9.2f)));

        cubeShader.setFloat("spotLight.constant",  1.0f);
        cubeShader.setFloat("spotLight.linear",    0.07f);
        cubeShader.setFloat("spotLight.quadratic", 0.017f);

        for (int i = 0; i < 5; i++)
        {
            float angle = 10.0f;
            glm::vec3 pos = position[i];
            model = glm::mat4(1.0f);
            model = glm::translate(model, pos);
        
            cubeShader.setMat4("model", model);

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);

            // bind specular map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);

            glBindVertexArray(cubeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //光方块
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", camera.getViewMatrix());
        for (int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
            lightCubeShader.setMat4("model", model);
            lightCubeShader.setVec3("lightColor", ponitLightColor[i]);
            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, dirLightDir);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f,3.0f));
        lightCubeShader.setMat4("model", model);
        lightCubeShader.setVec3("lightColor", dirLightColor);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 24, 6);

        model = glm::mat4(1.0f);
        model = glm::translate(model, spotLightPos);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f,0.2f));
        lightCubeShader.setMat4("model", model);
        lightCubeShader.setVec3("lightColor", spotLightColor);
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