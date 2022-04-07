#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() 
{
    glewExperimental = true;

    if (! glfwInit()) {
        fprintf(stderr, "初始化 glew 失败!!");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    GLFWwindow* window;

    window = glfwCreateWindow(500, 500, "window1", NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "创建 window 失败!!");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // 初始化 glew
    glewExperimental = true;

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw nothing, see you in tutorial 2 !

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );


}