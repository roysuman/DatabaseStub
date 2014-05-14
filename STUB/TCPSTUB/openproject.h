#ifndef OPENPROJECT_H
#define OPENPROJECT_H

#include <QDialog>

#include <QMessageBox>
#include <QFileDialog>
#include "../DBLAYER/create_project_db.hpp"
#include "../STRUCTURE/database_structure.hpp"
#include "openproject.h"

namespace Ui {
    class openProject;

}

class openProject : public QDialog {
    Q_OBJECT
public:
    openProject(QWidget *parent = 0);
    ~openProject();
//
//protected:
//    void changeEvent(QEvent *e);

private:
    Ui::openProject *ui;
    QString projectName;
    QMessageBox errorMessageBox;
public slots:
    void browse();
    void ok();
    void cancel();

};

#endif // OPENPROJECT_H
