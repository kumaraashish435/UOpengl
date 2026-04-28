#include "Shader.h"

#include "Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main()
{
    std::cout << "starting application..." << std::endl;

    int success;
    char infoLog[512];

    //window
    Window window;

    //shader
    Shader shader("vertex.txt", "fragment.txt");


    //vertex data
    float vertices[] = {
        //rectangle             color
        0.5f, 0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.0f   , 1.0f, 1.0f, 0.0f  // top left
    };

    // index data
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // buffers
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    // bind vertex array object
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // transformation
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.Activate();
    shader.setMat4("transform", trans);


    // render loop
    while (!window.ShouldClose())
    {
        // input
        window.processInput();
        window.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // update transformation
        float time = glfwGetTime();

        // continuously rotate the rectangle
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, time/10.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        // render
        shader.Activate();
        shader.setMat4("transform", trans);

        // draw rectangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // update window
        window.Update();
    }

    glDeleteProgram(shader.ID);
    std::cout << "exiting application..." << std::endl;

    return 0;
}
