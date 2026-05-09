#ifndef CAMERA_H
#define CAMERA_H


#include "Application.h"
#include "Shader.h"

class Camera
{
public:
    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    float distance = 3.0f;

    glm::vec3 target = glm::vec3(0.0f);

    int height;
    int width;
    bool firstClick = true;

    // Camera options
    float speed = 0.1f;
    float sensitivity = 100.0f;

    // Constructor with vectors
    Camera(int width, int height, glm::vec3 position);

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    void Matrix(Shader& shader, const char* uniform);
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

    void Inputs(GLFWwindow* window);
    
private:
    void updateCameraVectors();
};


#endif // CAMERA_H