#version 330 core

out vec4 FragColor;

in vec3 OurColor;
in vec2 TexCoord;
in vec3 Normal; 
in vec3 crntPos;

uniform sampler2D texture1;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambient = 0.1;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - crntPos);
    float diffuse = max(dot(norm, lightDir), 0.0);

    FragColor = texture(texture1, TexCoord) * lightColor * (diffuse + ambient);
}