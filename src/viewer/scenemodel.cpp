#include "include/scenemodel.h"
#include <QIcon>

SceneModel::SceneModel(Scene *scene)
{
    rootItem = scene->getRoot();
}

QModelIndex SceneModel::index (int row, int column, const QModelIndex & parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();

    Node *parentItem, *childItem;

    if (!parent.isValid()) parentItem = rootItem;
    else parentItem = itemForIndex(parent);

    childItem = parentItem->childAt(row);

    if (childItem) return createIndex(row, column, childItem);
    else return QModelIndex();
}

QModelIndex SceneModel::parent (const QModelIndex & child) const
{
    if (!child.isValid()) return QModelIndex();

    Node *childItem = itemForIndex(child);
    Node *parentItem = childItem->getParent();

    if (!parentItem || parentItem == rootItem) return QModelIndex();

    int row = parentItem->getRow();

    if (parentItem) return createIndex(row, 0, parentItem);

    return QModelIndex();
}

QVariant SceneModel::data (const QModelIndex & index, int role) const
{
    if (!index.isValid()) return QVariant();

    Node *item = itemForIndex(index);
    QString name = QString::fromStdString(item->getName());

    int col = index.column();

    if (col == 0 && role == Qt::DisplayRole)
        return name;
    else if (col == 0 && role == Qt::DecorationRole)
        return QIcon(":/icons/brick.png");
    /*
    else if (col == 1 && role == Qt::CheckStateRole)
      return (item->isVisible()) ? Qt::Checked : Qt::Unchecked;
    */
    else
        return QVariant();
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
             switch (section) {
                 case 0:
                     return tr("Name");
                 case 1:
                     return tr("Visible");
                 default:
                     return QVariant();
             }
         }

    return QVariant();
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return 0;

    return (index.column() == 0) ?
                Qt::ItemIsEnabled | Qt::ItemIsSelectable :
                Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

int SceneModel::rowCount (const QModelIndex & parent) const
{
    Node *parentItem;

    if (!parent.isValid()) parentItem = rootItem;
    else parentItem = itemForIndex(parent);

    return parentItem->childCount();
}

int SceneModel::columnCount (const QModelIndex & parent) const
{
    // Fix count later
    return 1;
}

Node* SceneModel::itemForIndex(const QModelIndex & index)
{
    return static_cast<Node*>(index.internalPointer());
}
