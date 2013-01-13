#ifndef WORKSPACEGL_H
#define WORKSPACEGL_H

#include <QtOpenGL>

class WorkspaceGL : public QGLWidget {

    Q_OBJECT

public:
    WorkspaceGL(QWidget *parent);
    virtual ~WorkspaceGL();

};

#endif//WORKSPACEGL_H
