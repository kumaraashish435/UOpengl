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

// vertex data for draw 3d pyramid
float vertices[] = {

    // FRONT FACE
    -0.5f, 0.0f, 0.5f, 1, 0, 0, 0.0f, 0.447f, 0.894f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 1, 1, 0, 0.0f, 0.447f, 0.894f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1, 1, 1, 0.0f, 0.447f, 0.894f, 0.5f, 1.0f,

    // RIGHT FACE
    0.5f, 0.0f, 0.5f, 1, 1, 0, 0.894f, 0.447f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0, 0, 1, 0.894f, 0.447f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1, 1, 1, 0.894f, 0.447f, 0.0f, 0.5f, 1.0f,

    // BACK FACE
    0.5f, 0.0f, -0.5f, 0, 0, 1, 0.0f, 0.447f, -0.894f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0, 1, 0, 0.0f, 0.447f, -0.894f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1, 1, 1, 0.0f, 0.447f, -0.894f, 0.5f, 1.0f,

    // LEFT FACE
    -0.5f, 0.0f, -0.5f, 0, 1, 0, -0.894f, 0.447f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.0f, 0.5f, 1, 0, 0, -0.894f, 0.447f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 1, 1, 1, -0.894f, 0.447f, 0.0f, 0.5f, 1.0f,

    // BOTTOM FACE
    -0.5f, 0.0f, 0.5f, 1, 0, 0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0, 1, 0, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, -0.5f, 0, 0, 1, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

    -0.5f, 0.0f, 0.5f, 1, 0, 0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0, 0, 1, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.0f, 0.5f, 1, 1, 0, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
// index data for draw 3d pyramid
unsigned int indices[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17};

// cube vertices
GLfloat lightVertices[] = {
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f};

GLuint lightIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7};

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

int main()
{
    std::cout << "starting application..." << std::endl;
    // window
    Window window;
    // shader
    Shader shader("vertex.glsl", "fragment.glsl");

    // VAO, VBO, EBO setup
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);                   // position
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float))); // color

    // normals
    VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));

    // texture coords
    VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, 11 * sizeof(float), (void *)(9 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();

    Shader lightShader("lightVertex.glsl", "lightFragment.glsl");
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0); // position

    lightVAO.Unbind();
    lightVBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 0.95f, 0.8f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);  

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
    glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    

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

        camera.Inputs(window.GetWindow());
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        // activate shader program
        shader.Activate();
        camera.Matrix(shader, "cameraMatrix");

        // Render container
        // bind textures on corresponding texture units
        VAO1.Bind();
        tex.Bind(GL_TEXTURE0);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "cameraMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        // update window
        window.Update();
    }

    std::cout << "exiting application..." << std::endl;

    return 0;
}
