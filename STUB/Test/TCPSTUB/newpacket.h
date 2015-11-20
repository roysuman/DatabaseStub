#ifndef NEWPACKET_H
#define NEWPACKET_H

#include <QDialog>

namespace Ui {
    class newPacket;
}

class newPacket : public QDialog {
    Q_OBJECT
public:
    newPacket(QWidget *parent = 0);
    ~newPacket();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::newPacket *ui;
};

#endif // NEWPACKET_H
