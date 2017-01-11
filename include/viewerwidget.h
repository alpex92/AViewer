#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include "glhelper.h"
#include "camera.h"
#include "scene.h"
#include "selecttool.h"

#include <QGLWidget>
#include <QAction>
#include <QMouseEvent>
#include <QRubberBand>

#include <glm/gtc/type_ptr.hpp>


enum ToolAction {
    ACTION_SELECT,
    ACTION_HAND,
    ACTION_MOVE
};

Q_DECLARE_METATYPE(ToolAction)
Q_DECLARE_METATYPE(CameraAction)

class ViewerWidget : public QGLWidget
{
    Q_OBJECT

public:

    ViewerWidget(QWidget *parent = 0);
    ~ViewerWidget();

    void setColor(QColor color);
    void setFOV(float fov);
    void setAspectRatio(float ratio);
    Scene *getScene();

public slots:
    void setAction(QAction *action);
    void cameraAction(QAction *action);
    void addNode(Node* node);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *event);
    void initProgram();
    void initBuffers();
    void drawNode(Node *node);
private:
    Camera *camera;
    Scene *scene;
    SelectTool *selectTool;
    GLuint vertexBuffer, elementbuffer, vertexArray;
    GLuint programID, colorID, matrixID;
    QPoint startPos, lastPos;
    QRubberBand *rubberBand;
    QColor modelColor, clearColor;
    ToolAction currentAction;
    bool legacyMode;
};

#endif // VIEWERWIDGET_H
