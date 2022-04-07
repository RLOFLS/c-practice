#include <GLFW/glfw3.h>

int main() {

    typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
    GL_GENBUFFERS glGenBuffers = (GL_GENBUFFERS)glfwGetProcAddress("glGenBuffers");
    unsigned int buffer;

    glGenBuffers(1, &buffer);

    return 0;
}