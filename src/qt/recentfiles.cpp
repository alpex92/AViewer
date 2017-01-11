#include "include/recentfiles.h"

RecentFiles::RecentFiles(QMenu *menu) : parent(menu), settingsName("recentFiles")
{
    for (int i = 0; i < MaxRecentFiles; i++)
    {
        recentFileActs[i] = new QAction(parent);
        recentFileActs[i]->setVisible(false);
        parent->addAction(recentFileActs[i]);

        connect(recentFileActs[i], SIGNAL(triggered()),
                this, SLOT(onTrigger()));
    }

    updateActions();
}

void RecentFiles::onTrigger()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) emit triggered(action->data().toString());
}

void RecentFiles::addFile(QString &fileName)
{
    QSettings settings;
    QStringList files = settings.value(settingsName).toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue(settingsName, files);

    updateActions();
}

void RecentFiles::updateActions()
{
    QSettings settings;
    QStringList files = settings.value(settingsName).toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = QFileInfo(files[i]).fileName();
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }

    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

}




