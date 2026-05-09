#include "Shader.h"
#include "Window.h"
#include "Application.h"

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

#include "Texture.h"

#include "Camera.h"


// //vertex data
// float vertices[] = {
//     //rectangle             color                  texture coords
//      0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f,           // top right
//      0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,           // bottom right
//     -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,           // bottom left
//     -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f,           // top left
// };

// // index data
// unsigned int indices[] = {
//     0, 1, 3,
//     1, 2, 3
// };

//vertex data for draw 3d pyramid
float vertices[] = {
    // positions          // colors           // texture coords
     -0.5f, 0.0f,  0.5f,  1.0f, 0.0f, 0.0f,   0.5f, 1.0f,   // front-left
     -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // back-left
      0.5f, 0.0f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // back-right
      0.5f, 0.0f,  0.5f,  1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // front-right
      0.0f, 1.0f,  0.0f,  1.0f, 1.0f, 1.0f,   0.5f, 2.0f    // top
};  
// index data for draw 3d pyramid
unsigned int indices[] = {
    // Side faces
    0, 1, 4,   // left side
    1, 2, 4,   // back side
    2, 3, 4,   // right side
    3, 0, 4,   // front side

    // Bottom face
    0, 1, 2,
    0, 2, 3
};

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

int main()
{
    std::cout << "starting application..." << std::endl;
    //window
    Window window;
    //shader
    Shader shader("vertex.glsl", "fragment.glsl");

    //VAO, VBO, EBO setup
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);                 // position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float))); // color

    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float))); // texture coords

    VAO1.Unbind();
    VBO1.Unbind();

    // texture
    Texture tex("tex.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

    shader.Activate();
    tex.texUnit(shader, "texture1", 0);



    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.3f, 3.0f));

    // render loop
    while (!window.ShouldClose())
    {
        // input
        window.processInput();
        window.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // activate shader program
        shader.Activate();

        camera.Inputs(window.GetWindow());
        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "MVP");

        // Render container
        // bind textures on corresponding texture units
        VAO1.Bind();
        tex.Bind(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        // update window
        window.Update();
    }

    std::cout << "exiting application..." << std::endl;

    return 0;
}
