#include "Shader.h"
#include "Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"


//vertex data
float vertices[] = {
    //rectangle             color                  texture coords
     0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,           // top right
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,           // bottom right
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,           // bottom left
    -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f,           // top left
};

// index data
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main()
{
    std::cout << "starting application..." << std::endl;

    int success;
    char infoLog[512];

    //window
    Window window;
    //shader
    Shader shader("vertex.txt", "fragment.txt");

    

    // buffers
    // unsigned int VBO, VAO, EBO;
    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);                 // position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float))); // color

    VAO1.Unbind();
    VBO1.Unbind();


    // // bind vertex array object
    // glBindVertexArray(VAO);  // Now everything I do gets stored in VAO

    // // bind vertex buffer and copy data
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // bind element buffer and copy data
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // //position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // //color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);



    // load and create texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("tex.jpeg", &width, &height, &nrChannels, 0);
    if (data)    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shader.Activate();



    // render loop
    while (!window.ShouldClose())
    {
        // input
        window.processInput();
        window.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // // update transformation
        // float time = glfwGetTime();

        // // continuously rotate the rectangle
        // glm::mat4 trans = glm::mat4(1.0f);
        // trans = glm::rotate(trans, time/10.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        // // render
        // shader.Activate();
        // shader.setMat4("transform", trans);

        shader.Activate();

        // draw rectangle
        // glBindVertexArray(VAO);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // update window
        window.Update();
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    glDeleteProgram(shader.ID);
    std::cout << "exiting application..." << std::endl;

    return 0;
}
