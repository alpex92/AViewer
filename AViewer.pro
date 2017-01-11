#-------------------------------------------------
#
# Project created by QtCreator 2013-09-20T15:01:05
#
#-------------------------------------------------

QT += core opengl

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}
else {
    QT += gui
}

TARGET = AViewer
TEMPLATE = app

SOURCES += src/main.cpp\
    src/qt/viewerwidget.cpp \
    src/qt/recentfiles.cpp \
    src/qt/mainwindow.cpp \
    src/qt/checkboxdelegate.cpp \
    src/viewer/utils.cpp \
    src/viewer/selecttool.cpp \
    src/viewer/scenemodel.cpp \
    src/viewer/scene.cpp \
    src/viewer/node.cpp \
    src/viewer/importer.cpp \
    src/viewer/glhelper.cpp \
    src/viewer/glew.c \
    src/viewer/camera.cpp

HEADERS  += include/viewerwidget.h \
    include/utils.h \
    include/selecttool.h \
    include/scenemodel.h \
    include/scene.h \
    include/recentfiles.h \
    include/node.h \
    include/mainwindow.h \
    include/importer.h \
    include/glhelper.h \
    include/checkboxdelegate.h \
    include/camera.h

FORMS += mainwindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    res/default.vert \
    res/default.frag \
    shaders/default.vert \
    shaders/default.frag

DEFINES += GLEW_BUILD

INCLUDEPATH += F:/Libs/GLEW/include/ \
               F:/Libs/glm \
               F:/Libs/assimp/include

LIBS += -LF:/Libs/assimp/lib -lassimp


