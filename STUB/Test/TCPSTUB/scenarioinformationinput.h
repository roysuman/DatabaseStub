#ifndef SCENARIOINFORMATIONINPUT_H
#define SCENARIOINFORMATIONINPUT_H

#include <QDialog>

namespace Ui {
class ScenarioInformationInput;
}

class ScenarioInformationInput : public QDialog
{
    Q_OBJECT
    
public:
    explicit ScenarioInformationInput(QWidget *parent = 0);
    ~ScenarioInformationInput();
    
private:
    Ui::ScenarioInformationInput *ui;
};

#endif // SCENARIOINFORMATIONINPUT_H
