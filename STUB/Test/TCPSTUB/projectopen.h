#ifndef PROJECTOPEN_H
#define PROJECTOPEN_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "../STRUCTURE/include/database_structure.hpp"
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "../SUPPORT/globalDatatypes.hpp"
namespace Ui {
    class projectOpen;
}

class projectOpen : public QDialog {
    Q_OBJECT
    public slots:
        void browse();
        void ok();
        void cancel();
public:
    projectOpen(QWidget *parent = 0);
    ~projectOpen();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::projectOpen *ui;
    QString fileName;
    QMessageBox errorMessageBox;
};

#endif // PROJECTOPEN_H
