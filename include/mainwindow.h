#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QDragEnterEvent>
#include <QUrl>

#include "recentfiles.h"
#include "importer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:

    // File opening
    void on_actionOpen_triggered();
    void openFile(QString filePath);

    // Loading
    void onLoadStarted();
    void onLoadComplete();

    // Collapse/Expand groups
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    // Enable/disable controls etc.
    void on_checkBox_toggled(bool enabled);
    void on_radioButton_2_toggled(bool enabled);
    void changeColor(int);
    // Update FOV
    void on_lineEdit_editingFinished();
    // Update aspect ratio
    void on_lineEdit_8_editingFinished();
    // Change left dock title
    void on_tabWidget_currentChanged(int index);
    
private:

    void init();
    void initUI();
    void initComponents();

    Ui::MainWindow *ui;

    RecentFiles *recentFiles;
    Importer *importer;


};

#endif // MAINWINDOW_H
