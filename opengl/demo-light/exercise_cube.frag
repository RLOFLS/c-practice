#version 330 core

out vec4 FragColor; 

in vec3 Normal;
in vec3 FragPos;

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    //环境光强度
    float ambientStrength = 0.8;
    //计算环境光
    vec3 ambient = ambientStrength * cubeColor;

    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //镜面反射
    // float specularStrength = 0.7;
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm); 
    // //32 越大 形成的高光越明显
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 512);
    // vec3 specular = specularStrength * spec * lightColor; 

    float specularStrength = 0.3;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    //32 越大 形成的高光越明显
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor; 
    

    vec3 result = (ambient + diffuse + specular) * cubeColor;

    FragColor = vec4(result, 1.0);
}