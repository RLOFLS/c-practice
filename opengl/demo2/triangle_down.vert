#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

//ๅ็งป้
uniform float xOffset = 0.0;

void main()
{
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0); // just add a - to the y position
    ourColor = aColor;
    //ourColor = aPos;
}