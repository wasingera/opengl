#include "camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

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
    /* position.y = 0; */
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    fov -= yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

glm::mat4 Camera::GetPerspectiveMatrix(float fov, float width, float height, float near, float far) {
    return glm::mat4(1.0f);
}

glm::mat4 Camera::GetViewMatrix() {
    // now we find our coordinate system for a UVN camera
    // whatever the camera is looking at needs to be -z --> in NDC space, +z points out of screen

    // the point that the camera is currently looking at
    glm::vec3 target = position + front;

    // negation of vector pointing out of the camera's face
    glm::vec3 n = glm::normalize(position - target);

    // vector pointing to camera's right
    glm::vec3 u = glm::normalize(glm::cross(worldUp, n));

    // vector pointing to camera's relative up
    glm::vec3 v = glm::normalize(glm::cross(n, u));

    // this changes basis from camera space to world space
    glm::mat4 rotate(
        u.x,  v.x,  n.x,  0.0f,
        u.y,  v.y,  n.y,  0.0f,
        u.z,  v.z,  n.z,  0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    // this inverse changes from world space to camera space
    /* glm::mat4 rotate( */
    /*     u.x,  u.y,  u.z,  0, */
    /*     v.x,  v.y,  v.z,  0, */
    /*     n.x,  n.y,  n.z,  0, */
    /*     0.0f, 0.0f, 0.0f, 1.0f */
    /* ); */

    // moves the camera back to the origin
    glm::mat4 trans(glm::translate(glm::mat4(1.0f), -position));

    // to go from camera space to world space we rotate and then translate
    // so we do the opposite to get from world space to camera space
    return rotate * trans;
}
