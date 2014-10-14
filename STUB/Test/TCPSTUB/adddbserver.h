#ifndef ADDDBSERVER_H
#define ADDDBSERVER_H

#include <QDialog>
#include <QMessageBox>
#include "../SUPPORT/globalDatatypes.hpp"
namespace Ui {
class AddDbServer;
}

class AddDbServer : public QDialog
{
    Q_OBJECT
public slots:
    void save();
    void cancel();
    
public:
    explicit AddDbServer(QWidget *parent = 0);
    ~AddDbServer();
    
private:
    Ui::AddDbServer *ui;
     QMessageBox errorMessageBox;
};

#endif // ADDDBSERVER_H
