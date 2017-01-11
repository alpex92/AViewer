#ifndef RECENTFILES_H
#define RECENTFILES_H

#include <QMenu>
#include <QSettings>
#include <QFileInfo>

class RecentFiles : public QObject
{
Q_OBJECT
public:
    RecentFiles(QMenu *menu);
    void addFile(QString &fileName);

signals:
    void triggered(const QString);

private slots:
    void onTrigger();

private:
    void updateActions();
    QMenu *parent;
    const QString settingsName;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
};

#endif // RECENTFILES_H
