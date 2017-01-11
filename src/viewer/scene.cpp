#include "include/scene.h"

Scene::Scene() : root(NULL)
{
    root = new Node("Root");
}

Node *Scene::getRoot()
{
    return root;
}
