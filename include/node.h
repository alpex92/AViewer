#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <list>
#include <glm/glm.hpp>

typedef unsigned int uint;

class Node
{
public:

    struct Face
    {
        uint p1;
        uint p2;
        uint p3;

        Face() {}
        Face(uint _p1, uint _p2, uint _p3)
            : p1(_p1), p2(_p2), p3(_p3) { }
    };

    struct Surface
    {
        std::vector<uint> indicies;
        bool selected;
    };

    Node(std::string _name = "Node");
    ~Node();

    // Child/parent
    Node *getParent();
    Node *childAt(int i);
    void addChild(Node *child);
    int childCount();

    // Identification
    int getRow();
    int setRow(int newRow);
    std::string getName();

    // Selection
    bool isSelected();
    void select(bool isSelected);

    // Visibility
    bool isVisible();
    void setVisible(bool visible);

    // Data add
    void addVerex(glm::vec3 vertex);
    void addTexCord(glm::vec3 texCord);
    void addNormal(glm::vec3 normal);
    void addIndex(uint index);

    // Data getters
    std::vector<glm::vec3> *getVerticies();
    std::vector<glm::vec3> *getTexCords();
    std::vector<glm::vec3> *getNormals();
    std::vector<Face> *getFaces();
    std::vector<uint> *getIndicies();
    glm::mat4 getModelMatrix();

    // Size getters
    int getVerticiesCount();
    int getIndiciesCount();

private:

    std::vector<glm::vec3> verticies;
    std::vector<glm::vec3> texCords;
    std::vector<glm::vec3> normals;
    std::vector<uint> indicies;

    std::vector<Face> faces;
    std::vector<Surface> surfaces;

    glm::mat4 modelMatrix;

    bool selected;
    bool visible;

    std::string name;
    int row;
    Node *parent;
    std::vector<Node*> children;

};

#endif // NODE_H
