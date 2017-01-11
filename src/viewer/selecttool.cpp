#include "include/selecttool.h"

using namespace glm;

SelectTool::SelectTool(Camera *camera)
{
    this->camera = camera;
}

glm::vec3 SelectTool::screenCordToVec(float mouse_x, float mouse_y, float width, float height)
{
    float x = (2.0f * mouse_x) / width - 1.0f;
    float y = 1.0f - (2.0f * mouse_y) / height;
    vec4 ray_clip = vec4(x, y, -1.0, 1.0);
    vec4 ray_eye = inverse(camera->getProjectionMatrix()) * ray_clip;
    ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
    return vec3(normalize((inverse(camera->getViewMatrix()) * ray_eye)));
}
