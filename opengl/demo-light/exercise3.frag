#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular; 

    //
    sampler2D emission;

    float shininess;
}; 

struct Light {
    //
    //vec3 position;
    //平行光 方向
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform float time;

void main()
{

    vec3 lightDir = normalize(light.direction);

    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

    //emisson
    vec3 show = step(vec3(1.0), vec3(1.0) - texture(material.specular, TexCoords).rgb);
    vec3 emission =  texture(material.emission, TexCoords + vec2(0.0, time)).rgb * show;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 