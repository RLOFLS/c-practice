#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 resColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vec3 Position = vec3(model * vec4(aPos, 1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;

    //环境光强度
    float ambientStrength = 0.8f;
    //计算环境光
    vec3 ambient = ambientStrength * lightColor;

    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //镜面反射
    float specularStrength = 17.0;
    vec3 viewDir = normalize(lightPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm); 
    //32 越大 形成的高光越明显
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 512);
    vec3 specular = specularStrength * spec * lightColor; 

    resColor = ambient + diffuse + specular; 
}