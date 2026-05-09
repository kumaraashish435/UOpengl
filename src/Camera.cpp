#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Position = position;
    this->width = width;
    this->height = height;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);
    glm::mat4 projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader &shader, const char *uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow *window)
{
    // Look around object
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = false;
        }

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xOffset =
            sensitivity * (float)(mouseX - width / 2) / width;

        float yOffset =
            sensitivity * (float)(mouseY - height / 2) / height;

        yaw += xOffset * 100.0f;
        pitch -= yOffset * 100.0f;

        // Prevent flipping
        if (pitch > 89.0f)
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;

        // Convert spherical coordinates to cartesian
        glm::vec3 direction;

        direction.x =
            cos(glm::radians(yaw)) *
            cos(glm::radians(pitch));

        direction.y =
            sin(glm::radians(pitch));

        direction.z =
            sin(glm::radians(yaw)) *
            cos(glm::radians(pitch));

        // Orbit around target
        Position = target - glm::normalize(direction) * distance;

        // Look at target
        Orientation = glm::normalize(target - Position);

        glfwSetCursorPos(window, width / 2, height / 2);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}