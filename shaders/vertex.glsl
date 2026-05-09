#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;

out vec3 OurColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 crntPos;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
    // World position
    crntPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = cameraMatrix * vec4(crntPos, 1.0);

    OurColor = aColor;
    TexCoord = aTexCoord;

    // Transform normals correctly
    Normal = mat3(transpose(inverse(model))) * aNormal;
}