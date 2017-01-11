#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QAbstractItemModel>
#include "scene.h"

class SceneModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SceneModel(Scene *scene);

    QModelIndex index (int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent (const QModelIndex & child) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    int rowCount (const QModelIndex & parent = QModelIndex()) const;
    int columnCount (const QModelIndex & parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    
public slots:

private:
    Node *rootItem;
    static Node *itemForIndex(const QModelIndex & index);
    
};

#endif // SCENEMODEL_H
