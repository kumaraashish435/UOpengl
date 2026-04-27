#include "Shader.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow* window);

int main()
{
    std::cout << "starting application..." << std::endl;

    int success;
    char infoLog[512];


    // GLFW: initialize and configure3
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Window", nullptr, nullptr);
    if (!window)    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))    {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);    


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    Shader shader("vertex.txt", "fragment.txt");
    Shader shader2("vertex.txt", "frag2.txt");


    float vertices[] = {
        //rectangle             color
        0.5f, 0.5f, 0.0f,     1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.0f   , 1.0f, 1.0f, 0.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.Activate();
    shader.setMat4("transform", trans);

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::scale(trans2, glm::vec3(0.5f, 0.5f, 0.5f));
    trans2 = glm::rotate(trans2, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader2.Activate();
    shader2.setMat4("transform", trans2);



    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.Activate();
        shader.setMat4("transform", trans);

        shader2.Activate();
        shader2.setMat4("transform", trans2);

        // draw 
        glBindVertexArray(VAO);
        shader.Activate();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        trans2 = glm::rotate(trans2, glm::radians(-0.1f), glm::vec3(0.0f, 0.0f, 1.0f)); 
        shader2.Activate();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

        // second triangle
        // shader2.Activate();
        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

        // glDrawArrays(GL_LINE_LOOP, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();




    glDeleteProgram(shader.ID);
    std::cout << "exiting application..." << std::endl;


    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
