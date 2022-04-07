#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

uniform float faceA = 0.2;

void main()
{
    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 0.1);
    //FragColor = vec4(ourColor, 1.0);
    
   FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), faceA);

   //确保只有快乐的脸朝另一个/反向方向看。
   //FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.5);

    //四个笑脸
   //FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, vec2(TexCoord.x * 2, TexCoord.y * 2 )), 0.5);
}