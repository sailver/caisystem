#include "authwarning.h"
#include "ui_authwarning.h"

AuthWarning::AuthWarning(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::AuthWarning)
{
    ui->setupUi(this);
}

AuthWarning::~AuthWarning()
{
    delete ui;
}
