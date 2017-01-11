#ifndef CONTROLS_H
#define CONTROLS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraAction
{
    CAMERA_RESET,
    CAMERA_FIT_VIEW,
    CAMERA_TOP,
    CAMERA_BOTTOM,
    CAMERA_LEFT,
    CAMERA_RIGHT,
    CAMERA_FRONT,
    CAMERA_REAR
};

class Camera
{
public:
    Camera();
    Camera(float newFOV, float newAspectRatio);
    void updateFOV(float newFOV);
    void updateAspectRatio(float ratio);

    float getSphereR();
    void setSphreRFixed(bool fixed);
    void setSphereR(float r);

    // TODO:
    /*
      1. LookAt
      2. MoveTo
    */

    void rotateBy(int dx, int dy);
    void rotateToRad(float horizontal, float vertical);
    void pan(int dx, int dy);
    void zoom(int delta);

    void reset();
    void calcMatrices();

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

private:
    void calcVectors();
    float fov, aspectRatio;
    float horizontalAngle, verticalAngle;
    float rotateSpeed, panSpeed, zoomSpeed;
    float sphereR;
    bool fixedR;
    glm::vec3 direction, right, up, target;
    glm::mat4 projectionMatrix, viewMatrix;
};

#endif // CONTROLS_H
