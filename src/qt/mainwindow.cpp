#include <QMimeData>
#include "ui_mainwindow.h"

#include "include/mainwindow.h"
#include "include/importer.h"
#include "include/scenemodel.h"
#include "include/checkboxdelegate.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    QCoreApplication::setOrganizationName("Alpex");
    QCoreApplication::setApplicationName("AViewer");

    initComponents();
    initUI();
}

void MainWindow::initComponents()
{
    importer = new Importer(ui->widget->getScene());
    connect(importer->getWatcher(), SIGNAL(started()), this, SLOT(onLoadStarted()));
    connect(importer->getWatcher(), SIGNAL(finished()), this, SLOT(onLoadComplete()));

    SceneModel *sceneModel = new SceneModel(ui->widget->getScene());
    ui->treeView->setModel(sceneModel);

    /*
    CheckBoxDelegate *delegate = new CheckBoxDelegate(ui->treeView);
    ui->treeView->setItemDelegateForColumn(1, delegate);
    */
}

void MainWindow::initUI()
{

    // Add recent files
    recentFiles = new RecentFiles(ui->menuRecent_files);
    connect(recentFiles, SIGNAL(triggered(QString)), this, SLOT(openFile(QString)));

    // FOV validator
    ui->lineEdit->setValidator(new QDoubleValidator(1, 180, 2));
    // Aspect ratio validator
    ui->lineEdit_8->setValidator(new QDoubleValidator(1, 10, 2));

    // Configure actionGroup
    QActionGroup *actionGroup = new QActionGroup(ui->mainToolBar);
    actionGroup->setExclusive(true);

    // Add actions
    actionGroup->addAction(ui->actionSelect);
    actionGroup->addAction(ui->actionHand);
    actionGroup->addAction(ui->actionMove);

    // Connect toolbar actions
    connect(actionGroup, SIGNAL(triggered(QAction*)), ui->widget, SLOT(setAction(QAction*)));

    // Connect camera actions
    connect(ui->menuCamera, SIGNAL(triggered(QAction*)), ui->widget, SLOT(cameraAction(QAction*)));

    // Set toolbar actions
    ui->actionSelect->setData(QVariant::fromValue<ToolAction>(ACTION_SELECT));
    ui->actionHand->setData(QVariant::fromValue<ToolAction>(ACTION_HAND));
    ui->actionMove->setData(QVariant::fromValue<ToolAction>(ACTION_MOVE));

    // Set camera actions
    ui->actionReset->setData(QVariant::fromValue<CameraAction>(CAMERA_RESET));
    ui->actionFitView->setData(QVariant::fromValue<CameraAction>(CAMERA_FIT_VIEW));
    ui->actionTop->setData(QVariant::fromValue<CameraAction>(CAMERA_TOP));
    ui->actionBottom->setData(QVariant::fromValue<CameraAction>(CAMERA_BOTTOM));
    ui->actionLeft->setData(QVariant::fromValue<CameraAction>(CAMERA_LEFT));
    ui->actionRight->setData(QVariant::fromValue<CameraAction>(CAMERA_RIGHT));
    ui->actionFront->setData(QVariant::fromValue<CameraAction>(CAMERA_FRONT));
    ui->actionRear->setData(QVariant::fromValue<CameraAction>(CAMERA_REAR));

    // Make select tool active
    ui->actionHand->trigger();

    // Color change
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(changeColor(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(changeColor(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), this, SLOT(changeColor(int)));

    // Hide frames
    ui->frame->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->frame_4->setVisible(false);

    // Set dock title
    on_tabWidget_currentChanged(0);

    /*
    ui->treeView->setStyleSheet(
                "QTreeView::indicator:unchecked {image: url(:/icons/eye_grey.png);}"
                "QTreeView::indicator:checked {image: url(:/icons/eye.png);}"
                "QCheckBox::indicator:unchecked {image: url(:/icons/eye_grey.png);}"
                "QCheckBox::indicator:checked {image: url(:/icons/eye.png);}"
              );
    */

    // Hide panel
    //ui->dockWidget->hide();

    // Configure treeViews
    //ui->treeView->setModel();
    //ui->treeView_2->setModel();
}

void MainWindow::changeColor(int)
{
    int r = ui->horizontalSlider->value();
    int g = ui->horizontalSlider_2->value();
    int b = ui->horizontalSlider_3->value();
    ui->widget->setColor(QColor(r, g, b));
}

void MainWindow::on_lineEdit_editingFinished()
{
    // TODO: FIX FOV
    ui->widget->setFOV(ui->lineEdit->text().toFloat());
}

void MainWindow::on_lineEdit_8_editingFinished()
{
    // TODO: FIX Aspect Ratio
    ui->widget->setAspectRatio(ui->lineEdit_8->text().toFloat());
}

void MainWindow::openFile(QString filePath)
{
    if (!filePath.isEmpty()) importer->import(filePath);
}

void MainWindow::onLoadStarted()
{
    ui->statusBar->showMessage(tr("Importing model.."));
}

void MainWindow::onLoadComplete()
{
    bool result = importer->getWatcher()->result();
    QString fileName = importer->getlastFileName();
    if (!result) {
        ui->statusBar->showMessage(tr("Import failed"));
        QMessageBox::warning(this, tr("Import failure"),
                             tr("Can't import file ") + fileName + ".");
    }
    else
    {
        ui->statusBar->showMessage(tr("Import complete"));
        recentFiles->addFile(fileName);
        ui->treeView->reset();
        ui->widget->updateGL();
    }

}

void MainWindow::on_actionOpen_triggered()
{
    openFile(QFileDialog::getOpenFileName());
}

void MainWindow::on_pushButton_clicked()
{
    ui->frame->setVisible(!ui->frame->isVisible());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->frame_2->setVisible(!ui->frame_2->isVisible());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->frame_3->setVisible(!ui->frame_3->isVisible());
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->frame_4->setVisible(!ui->frame_4->isVisible());
}

void MainWindow::on_checkBox_toggled(bool enabled)
{
    ui->label_2->setEnabled(enabled);
    ui->lineEdit_2->setEnabled(enabled);
}

void  MainWindow::on_radioButton_2_toggled(bool enabled)
{
    ui->rgb_group->setEnabled(enabled);
    ui->horizontalSlider->setEnabled(enabled);
    ui->horizontalSlider_2->setEnabled(enabled);
    ui->horizontalSlider_3->setEnabled(enabled);
}

 void MainWindow::on_tabWidget_currentChanged(int index)
 {
     QString title;

     switch (index)
     {
        case 0:
            title = tr("Scene graph");
        break;
        case 1:
            title = tr("Project files");
        break;
     }

     ui->dockWidget_2->setWindowTitle(" " + title);
 }

// @Override
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

// @Override
void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    QString filename = urls.takeFirst().toLocalFile();
    //const QMimeData* mimeData = event->mimeData();

    // TODO: use mime data to determine if it's project or single file

    openFile(filename);
}

MainWindow::~MainWindow()
{
    delete ui;
}
