#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float PITCH = 0.0f;
const float YAW = -90.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = {0.1f};
const float FOV = 45.0f;

class Camera {
    public:

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float pitch;
    float yaw;

    float speed;
    float sensitivity;
    float fov;

    Camera(glm::vec3 position=glm::vec3(0.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f), float pitch=PITCH, float yaw=YAW);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetPerspectiveMatrix(float fov, float width, float height, float near, float far);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch=true);
    void updateCameraVectors();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseScroll(float yoffset);
};

#endif
