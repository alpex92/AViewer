#include "include/checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent) {}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/*option*/,
    const QModelIndex &index) const
{
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor,
    const QModelIndex &index) const
{
    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
    bool value = index.data().toBool();
    CheckBox->setChecked(value);
}

void CheckBoxDelegate::setModelData(QWidget *editor,
    QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
    bool val = CheckBox->isChecked();

    // TODO: SAVE DATA
    //model->setData(index, val, Qt::EditRole);
    //emit QAbstractItemModel::dataChanged(QModelIndex(index), val);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
