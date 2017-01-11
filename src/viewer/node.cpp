#include "include/node.h"
#include <algorithm>

Node::Node(std::string _name) : name(_name)
{
    verticies = std::vector<glm::vec3>();
    texCords = std::vector<glm::vec3>();
    normals = std::vector<glm::vec3>();
    indicies = std::vector<uint>();

    faces = std::vector<Face>();
    surfaces = std::vector<Surface>();

    children = std::vector<Node*>();
    modelMatrix = glm::mat4(1.0);

    parent = NULL;
    row = 0;
    selected = false;
    visible = true;
}

Node::~Node() { }

Node *Node::getParent()
{
    return parent;
}

Node *Node::childAt(int i)
{
    return children.at(i);
}

int Node::childCount()
{
    return children.size();
}

void Node::addChild(Node *child)
{
    children.push_back(child);
    child->parent = this;
    child->row = children.size() - 1;
}

int Node::getRow()
{
    return row;
}

int Node::setRow(int newRow)
{
    row = newRow;
    return row;
}

std::string Node::getName()
{
    return name;
}

bool Node::isSelected()
{
    return selected;
}

void Node::select(bool isSelected)
{
    if (selected != isSelected) selected = isSelected;
}

bool Node::isVisible()
{
    return visible;
}

void Node::setVisible(bool visible)
{
    this->visible = visible;
}

std::vector<glm::vec3> *Node::getVerticies()
{
    return &verticies;
}

std::vector<glm::vec3> *Node::getTexCords()
{
    return &texCords;
}

std::vector<glm::vec3> *Node::getNormals()
{
    return &normals;
}

std::vector<Node::Face> *Node::getFaces()
{
    return &faces;
}

int Node::getVerticiesCount()
{
    return verticies.size();
}

std::vector<uint> *Node::getIndicies()
{
    return &indicies;
}

int Node::getIndiciesCount()
{
    return indicies.size();
}

glm::mat4 Node::getModelMatrix()
{
    return modelMatrix;
}

void Node::addVerex(glm::vec3 vertex)
{
    verticies.push_back(vertex);
}

void Node::addTexCord(glm::vec3 texCord)
{
    texCords.push_back(texCord);
}

void Node::addNormal(glm::vec3 normal)
{
    normals.push_back(normal);
}

void Node::addIndex(uint index)
{
    indicies.push_back(index);
}
