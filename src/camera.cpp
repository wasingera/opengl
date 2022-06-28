#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float pitch, float yaw) :
    position{position}, worldUp{up}, pitch{pitch}, yaw{yaw}, front{glm::vec3(0.0f, 0.0f, -1.0f)}, speed{SPEED},
    sensitivity{SENSITIVITY}, fov{FOV}
{
    updateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    /* glm::vec3 direction; */
    /* direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); */
    /* direction.y = sin(glm::radians(pitch)); */
    /* direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); */
    /* front = glm::normalize(direction); */
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = speed * deltaTime;

    switch (direction) {
        case FORWARD:
            position += front * velocity;
            break;
        case BACKWARD:
            position -= front * velocity;
            break;
        case LEFT:
            position -= right * velocity;
            break;
        case RIGHT:
            position += right * velocity;
            break;
    }
    position.y = 0;
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    fov -= yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}
