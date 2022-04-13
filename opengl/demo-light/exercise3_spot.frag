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
    //聚光灯
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
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
    vec3 lightDir = normalize(light.position - FragPos);

    // check if lighting is inside the spotlight cone
    //float theta = dot(lightDir, normalize(light.direction));

    //if (theta > light.cutOff) {
        // ambient
        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

        // spotlight (soft edges)
        float theta = dot(lightDir, normalize(light.direction)); 
        float epsilon = (light.cutOff - light.outerCutOff);
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        diffuse  *= intensity;
        specular *= intensity;

        //emisson
        vec3 show = step(vec3(1.0), vec3(1.0) - texture(material.specular, TexCoords).rgb);
        vec3 emission =  texture(material.emission, TexCoords + vec2(0.0, time)).rgb * show;

        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        ambient  *= attenuation;  
        diffuse   *= attenuation;
        specular *= attenuation;
        emission *= attenuation;

        vec3 result = ambient + diffuse + specular + emission;
        FragColor = vec4(result, 1.0);
    //} else {
         // else, use ambient light so scene isn't completely dark outside the spotlight.
    //     FragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
   //}

    
} 