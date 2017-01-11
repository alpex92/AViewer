#include "include/importer.h"
#include "include/node.h"

#include <assimp/postprocess.h>
#include <QTextCodec>

Importer::Importer(Scene *_scene) : scene(_scene)
{
    loadWatcher = new QFutureWatcher<bool>();
    lastFileName = "None";
}

Importer::~Importer()
{
    delete loadWatcher;
}

QFutureWatcher<bool> *Importer::getWatcher()
{
    return loadWatcher;
}

const QString Importer::getlastFileName()
{
    return lastFileName;
}

void Importer::import(const QString fileName)
{
    QFuture<bool> future = QtConcurrent::run(this, &Importer::doImport, fileName);
    loadWatcher->setFuture(future);
}

bool Importer::doImport(const QString &fileName)
{
    // Save file name
    lastFileName = fileName;

    // Create an instance of the Importer class
    Assimp::Importer importer;

    // Get data from file
    const aiScene* importScene = importer.ReadFile(fileName.toStdString(),
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_GenNormals |
    aiProcess_JoinIdenticalVertices |
    aiProcess_SortByPType);

    if(!importScene) return false;

    // Get root of import scene
    aiNode *importRoot = importScene->mRootNode;
    aiMesh **meshes = importScene->mMeshes;

    // Process recursively
    processNode(importRoot, scene->getRoot(), meshes);

    return true;
}

void Importer::processNode(aiNode *importNode, Node *parentSceneNode, aiMesh **meshes)
{
    int childCount = importNode->mNumChildren;
    int meshCount = importNode->mNumMeshes;

    if (childCount != 0 || meshCount != 0)
    {
        // Create new node, add as child
        std::string name = std::string(importNode->mName.C_Str());
        Node *node = new Node(name);
        parentSceneNode->addChild(node);

        // Process children recursively
        for (int i = 0 ; i < childCount; ++i)
            processNode(importNode->mChildren[i], node, meshes);

        // Process meshes
        for (int i = 0 ; i < meshCount; ++i)
        {
            aiMesh *mesh = meshes[importNode->mMeshes[i]];
            Node *meshNode = NULL;

            // Don't create new node if it's only one mesh
            if (meshCount == 1) meshNode = node;
            else
            {
                meshNode = new Node();
                node->addChild(meshNode);
            }

            // Proceess single mesh

            // Copy verticies, texCords, normals
            copyVector(mesh->mVertices, node->getVerticies(), mesh->mNumVertices);
            copyVector(mesh->mTextureCoords[0], node->getTexCords(), mesh->mNumUVComponents[0]);
            copyVector(mesh->mNormals, node->getNormals(), mesh->mNumVertices);

            // TODO: copy transformation matrix

            //aiMatrix4x4 transform = importNode->mTransformation;

            // Get iFaces and count
            aiFace *aifaces = mesh->mFaces;
            uint faceCount = mesh->mNumFaces;

            // Get faces and indicies vectors from node
            std::vector<Node::Face> *faces = meshNode->getFaces();
            std::vector<uint> *indicies = meshNode->getIndicies();

            // Reserve vectors space
            faces->reserve(faceCount);
            indicies->reserve(faceCount * 3);

            // Copy faces and indicies
            for(uint i = 0; i < faceCount; ++i)
            {
                faces->push_back(Node::Face(aifaces[i].mIndices[0],
                                           aifaces[i].mIndices[1],
                                           aifaces[i].mIndices[2]));
                for(int j = 0; j < 3; j++)
                    indicies->push_back(aifaces[i].mIndices[j]);
            }

            // TODO: Calc surfaces

        }

    }

}

void Importer::copyVector(aiVector3D *source, std::vector<glm::vec3> *target, uint count)
{
    target->reserve(count);
    for(uint i = 0; i < count; ++i)
    {
        glm::vec3 vertex(source[i].x, source[i].y, source[i].z);
        target->push_back(vertex);
    }
}



