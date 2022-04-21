#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "src/game/Game.hpp"

const unsigned int SCR_WIDRH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDRH, SCR_HEIGHT, "demo", NULL, NULL);
    if (window == NULL) {
        std::cout << "create window fail" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //glad加载所有opengl函数指针
    if (! gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "glad加载初始失败" << std::endl;
        return -1;
    }

    unsigned int VBO, VAO;

    float vertexs[] = {
        -1.0f,  -0.1f, -1.0f,
        1.0f,  -0.1f, -1.0f,
        1.0f,  -0.1f,  1.0f,
        1.0f,  -0.1f,  1.0f,
        -1.0f, - 0.1f,  1.0f,
        -1.0f,  -0.1f, -1.0f,
    };

    Shader shader = Shader("src/shader/background.vert", "src/shader/background.frag");
    glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), &vertexs, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            
            
   // game::Game gameObj;

    while (! glfwWindowShouldClose(window))
    {
        glClearColor(0.3, 0.3, 0.3, 0.2);
        glClear(GL_COLOR_BUFFER_BIT);

        //gameObj.render();

        shader.use();

            glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)600 / (float)600, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);
            shader.setMat4("model", glm::mat4(1.0f));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
    

}