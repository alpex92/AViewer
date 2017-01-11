#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "scene.h"
#include "camera.h"

class SelectTool
{
public:
    SelectTool(Camera *camera);
    glm::vec3 screenCordToVec(float mouse_x, float mouse_y, float width, float height);

private:
    Camera *camera;

};

#endif // SELECTTOOL_H
