#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>
#include <QMessageBox>
#include "../DBLAYER/create_project_db.hpp"
#include "../STRUCTURE/database_structure.hpp"

namespace Ui {
class NewProject;
class AddDbServer;
}

class NewProject : public QDialog
{
    Q_OBJECT
public slots:
    void browse();
    void ok();
    void cancel();
    
public:

    explicit NewProject(QWidget *parent = 0);
    ~NewProject();
    
private:
    Ui::NewProject *ui;
    QString directoryName;
    QString projectName;
    QMessageBox errorMessageBox;
};





#endif // NEWPROJECT_H
