#include "scenarioinformationinput.h"
#include "ui_scenarioinformationinput.h"

ScenarioInformationInput::ScenarioInformationInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScenarioInformationInput)
{
    ui->setupUi(this);
}

ScenarioInformationInput::~ScenarioInformationInput()
{
    delete ui;
}
