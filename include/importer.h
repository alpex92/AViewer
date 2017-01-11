#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QFutureWatcher>
#include <QtConcurrentRun>
//#include </*QtConcurrent/*/QtConcurrentRun>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "scene.h"

class Importer : public QObject
{
Q_OBJECT
public:
    Importer(Scene *_scene);
    ~Importer();
    QFutureWatcher<bool> *getWatcher();
    void import(const QString fileName);
    const QString getlastFileName();
private:
    bool doImport(const QString &fileName);
    void processNode(aiNode *importNode, Node *parentSceneNode, aiMesh **meshes);
    void copyVector(aiVector3D *source, std::vector<glm::vec3> *target, uint count);
    Scene *scene;
    QFutureWatcher<bool> *loadWatcher;
    QString lastFileName;
};

#endif // IMPORTER_H
