#include "include/viewerwidget.h"
#include "include/utils.h"

ViewerWidget::ViewerWidget(QWidget *parent): QGLWidget(parent), lastPos(QPoint(0, 0))
{
    setAutoBufferSwap(true);
    scene = new Scene();
    camera = new Camera();
    selectTool = new SelectTool(camera);

    // Set colors
    modelColor = QColor(255, 255, 255);
    clearColor = QColor(51, 51, 51);
}

ViewerWidget::~ViewerWidget()
{
    delete selectTool;
    delete camera;
    delete scene;
}

Scene *ViewerWidget::getScene()
{
    return scene;
}

// Called at start
// @Override
void ViewerWidget::initializeGL()
{
    glewInit();

    /*
    legacyMode = !(QGLFormat::openGLVersionFlags()
                   & QGLFormat::OpenGL_Version_3_3);
                   */
    legacyMode = true;

    if (!legacyMode)
    {
        initProgram();
        initBuffers();
    }

    qglClearColor(clearColor);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

// Resize view
// @Override
void ViewerWidget::resizeGL(int width, int height)
{
    /*
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    */

    camera->updateAspectRatio((float)width/(float)height);
    glViewport(0, 0, width, height);
}

// Redraw
// @Override
void ViewerWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawNode(scene->getRoot());
}

void ViewerWidget::initProgram()
{
    std::vector<GLuint> shaderList;

    std::string strVertexShader = Utils::readFile(":/shaders/default.vert").toStdString();
    std::string strFragmentShader = Utils::readFile(":/shaders/default.frag").toStdString();

    shaderList.push_back(GLHelper::CreateShader(GL_VERTEX_SHADER, strVertexShader));
    shaderList.push_back(GLHelper::CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));

    programID = GLHelper::CreateProgram(shaderList);
    colorID = glGetUniformLocation(programID, "inColor");
    matrixID = glGetUniformLocation(programID, "MVP");

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}


void ViewerWidget::drawNode(Node *node)
{
    // Set color
    const GLfloat color[] = {
        modelColor.redF(),
        modelColor.greenF(),
        modelColor.blueF()
    };

    camera->calcMatrices();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 modelMatrix = node->getModelMatrix();
    glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    if (!legacyMode)
    {
        glUseProgram(programID);

        // Set uniforms
        glUniform3fv(colorID, 1, color);
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

        // Set data
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        // Draw stuff
        glDrawElements(GL_TRIANGLES, node->getIndiciesCount(), GL_UNSIGNED_SHORT, 0);

        // Disable
        glDisableVertexAttribArray(0);
        glUseProgram(0);
    }
    else
    {
        // Set color
        glColor3fv(color);

         // Draw verticies
        glBegin(GL_TRIANGLES);

        // Get pointer and length
        const glm::vec3 *vertexPos = node->getVerticies()->data();
        const uint *indicies = node->getIndicies()->data();
        int count = node->getIndiciesCount();

        for (int i = 0; i < count; i++)
            glVertex3fv(glm::value_ptr(vertexPos[indicies[i]]));

        glEnd();

        // Apply matrix
        glLoadMatrixf(glm::value_ptr(mvp));
    }

    for(int i = 0; i < node->childCount(); ++i)
        drawNode(node->childAt(i));

}

void ViewerWidget::setAction(QAction *action)
{
    currentAction = action->data().value<ToolAction>();
    Qt::CursorShape shape;

    switch (currentAction)
    {
        case ACTION_SELECT:
        shape = Qt::ArrowCursor;
        break;

        case ACTION_HAND:
        shape = Qt::OpenHandCursor;
        break;

        case ACTION_MOVE:
        shape = Qt::SizeAllCursor;
    }

    setCursor(shape);
}

void ViewerWidget::cameraAction(QAction *action)
{
    CameraAction camAction = action->data().value<CameraAction>();

    switch (camAction)
    {
        case CAMERA_RESET:
        camera->reset();
        break;
        case CAMERA_FIT_VIEW:
        // TODO: Implement Fit View
        break;
        case CAMERA_TOP:
        camera->rotateToRad(0.0f, -M_PI/2);
        break;
        case CAMERA_BOTTOM:
        camera->rotateToRad(0.0f, M_PI/2);
        break;
        case CAMERA_LEFT:
        camera->rotateToRad(-M_PI/2, 0.0f);
        break;
        case CAMERA_RIGHT:
        camera->rotateToRad(M_PI/2, 0.0f);
        break;
        case CAMERA_FRONT:
        camera->rotateToRad(0.0f, 0.0f);
        break;
        case CAMERA_REAR:
        camera->rotateToRad(M_PI, 0.0f);
        break;
    }

    updateGL();

}


void ViewerWidget::addNode(Node* node)
{
    scene->getRoot()->addChild(node);

    if (!legacyMode)
    {
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(glm::vec3) * node->getVerticiesCount(),
                     node->getVerticies()->data(), GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                       sizeof(unsigned short) * node->getIndiciesCount(),
                     node->getIndicies()->data(), GL_STATIC_DRAW);
    }
}

void ViewerWidget::setColor(QColor color)
{
    modelColor = color;
    updateGL();
}

void ViewerWidget::setFOV(float fov)
{
    camera->updateFOV(fov);
    updateGL();
}

void ViewerWidget::setAspectRatio(float ratio)
{
    camera->updateAspectRatio(ratio);
    updateGL();
}

void ViewerWidget::initBuffers()
{
    // VBO
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // VAO
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    // Indidices buffer
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
}

// @Override
void ViewerWidget::wheelEvent(QWheelEvent *event)
{
    camera->zoom(event->delta());
    updateGL();
}
// @Override
void ViewerWidget::mousePressEvent(QMouseEvent *event)
{
    // Save position anyway
    startPos = event->pos();
    lastPos = startPos;

    if (currentAction == ACTION_SELECT)
    {
        selectTool->screenCordToVec(startPos.x(), startPos.y(), width(), height());
    }
}

// @Override
void ViewerWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (currentAction == ACTION_HAND)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            camera->rotateBy(dx, dy);
            updateGL();
        }
        else if (event->buttons() & Qt::RightButton)
        {
            camera->pan(dx, dy);
            updateGL();
        }
    }
    else if (currentAction == ACTION_SELECT)
    {

    }
    else event->ignore();

    lastPos = event->pos();
}

// @Override
void ViewerWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (currentAction == ACTION_SELECT)
    {

        // TODO: process selection
    }

}
