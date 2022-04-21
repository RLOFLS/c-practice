#ifndef GG_Background
#define GG_Background

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "GameItemContract.hpp"

#include "../shader/shader.h"

#include <iostream>

namespace game
{
    class Background  {
    private:
            unsigned int VBO, VAO;

            float vertexs[18] = {
                -1.0f, 0.0f, -1.0f,
                 1.0f, 0.0f, -1.0f,
                 1.0f, 0.0f,  1.0f,
                -1.0f, 0.0f, -1.0f,
                 1.0f, 0.0f,  1.0f,
                -1.0f, 0.0f,  1.0f
            };

            Shader shader = Shader("src/shader/background.vert", "src/shader/background.frag");

    public:

        Background()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), &vertexs, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            
        
        }

        ~Background()
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
        }

        // operator GameItemContract*() {
        //     return this;
        // }

        void draw()
        {
            shader.use();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)600 / (float)600, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            shader.setMat4("projection", projection);
            shader.setMat4("view", view);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            std::cout << "bg draw" << std::endl;
        }

        bool isAlive()
        {
            return true;
        }
    };
} // namespace game



#endif