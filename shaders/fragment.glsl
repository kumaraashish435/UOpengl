#version 330 core

out vec4 FragColor;

in vec3 OurColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D texture1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    // Ambient
    float ambient = 0.2;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - crntPos);
    float diffuse = max(dot(norm, lightDir), 0.0);

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - crntPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;

    if(diffuse > 0.0)
{
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    }

    float specular = specularStrength * spec;
    // Texture
    vec4 texColor = texture(texture1, TexCoord);
     // Final lighting
    vec3 lighting = lightColor.rgb * (ambient + diffuse + specular);

    FragColor = vec4(texColor.rgb * lighting, texColor.a);
}