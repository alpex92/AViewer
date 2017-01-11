#ifndef SCENE_H
#define SCENE_H

#include <include/node.h>

class Scene
{
public:
    Scene();
    Node *getRoot();
private:
    Node *root;
};

#endif // SCENE_H
