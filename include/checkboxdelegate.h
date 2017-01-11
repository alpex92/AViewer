#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QCheckBox>
#include <QItemDelegate>

class CheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT

public:

    CheckBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // COMBOBOXDELEGATE_H
