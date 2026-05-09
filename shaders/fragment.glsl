#version 330 core

out vec4 FragColor;

in vec3 OurColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 lightColor;

void main()
{
    FragColor = texture(texture1, TexCoord) * lightColor;
}