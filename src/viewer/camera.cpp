#include "include/camera.h"

Camera::Camera()
{
    reset();
    fov = 60.0f;
    aspectRatio = 1.0f / 1.0f;
    fixedR = false;
}

Camera::Camera(float newFOV, float newAspectRatio)
{
    Camera();
    updateFOV(newFOV);
    updateAspectRatio(newAspectRatio);
}

void Camera::reset()
{
    horizontalAngle = 0.0f; //M_PI;
    verticalAngle = 0.0f; //M_PI/2.0f;

    rotateSpeed = 0.01f;
    panSpeed = 0.0025f;
    zoomSpeed = 0.0025f;
    sphereR = 25;
    target = glm::vec3(0, 0, 0);

    calcVectors();
}
void Camera::updateFOV(float newFOV)
{
    if (newFOV > 0 && newFOV < 180) fov = newFOV;
}

void Camera::updateAspectRatio(float ratio)
{
    if (ratio >= 0) aspectRatio = ratio;
}

float Camera::getSphereR()
{
    return sphereR;
}

void Camera::setSphreRFixed(bool fixed)
{
    fixedR = true;
}

void Camera::setSphereR(float r)
{
    if (r > 0 && r < FLT_MAX) sphereR = r;
}

void Camera::calcVectors()
{
    // Calc direction vector
    direction =  glm::vec3(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
                );

    // Calc right vector
    right = glm::vec3(
                sin(horizontalAngle - M_PI/2.0f),
                0,
                cos(horizontalAngle - M_PI/2.0f)
            );

    // Calc top vector
    up = glm::cross(right, direction);
}

void Camera::rotateBy(int dx, int dy)
{
    // Change angles
    verticalAngle -= dy * rotateSpeed;
    horizontalAngle -= dx * rotateSpeed;

    // Calc new values
    calcVectors();
}

void Camera::rotateToRad(float horizontal, float vertical)
{
    // TODO: Check angles
    horizontalAngle = horizontal;
    verticalAngle = vertical;
    calcVectors();
}

void Camera::pan(int dx, int dy)
{
    target -= right * (float)dx * panSpeed * sphereR;
    target += up * (float)dy * panSpeed * sphereR;
}

void Camera::zoom(int delta)
{
   if (!fixedR) sphereR -= delta * zoomSpeed * sphereR;
}

void Camera::calcMatrices()
{
    // Projection matrix display range : 0.1 unit <-> 10000 units
    projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 10000.0f);

    // Camera matrix
    viewMatrix = glm::lookAt(
        target - direction * sphereR,
        target,
        up
    );
}

glm::mat4 Camera::getProjectionMatrix()
{
    return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return viewMatrix;
}
