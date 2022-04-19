#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1; 
float far  = 100.0; 

void main()
{    
    vec4 textColor = texture(texture1, TexCoords);
    if (textColor.a < 0.1)
        discard;
    FragColor = textColor;
}