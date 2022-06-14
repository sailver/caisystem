#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    cl = new Clock;
    connect(ui->course, SIGNAL(clicked()), this, SLOT(course()));
    connect(ui->time, SIGNAL(clicked()), this, SLOT(time()));
    connect(ui->activity, SIGNAL(clicked()), this, SLOT(activity()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(log()));    
    connect(ui->alarm,SIGNAL(clicked()), this, SLOT(alarm()));
    connect(ui->activity,SIGNAL(clicked()), this, SLOT(activ()));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::course() {
    if(cb_clicked == 1) {
        delete(cb);
        cb_clicked = 0;
    } else {
        cb = new CbListWidget;
        cb->show();
        cb_clicked = 1;
    }
}

void Menu::time() {
    if(cl_clicked == 1) {
        cl->hide();
        cl_clicked = 0;
    } else {
        cl->show();
        cl_clicked = 1;
    }
}

void Menu::log() {
    if(lg_clicked == 1) {
        delete(lg);
        lg_clicked = 0;
    } else {
        lg = new LogUI;
        lg->show();
        lg_clicked = 1;
    }
}

void Menu::alarm() {
    if(al_clicked == 1) {
        delete(al);
        al_clicked = 0;
    } else {
        al = new AListUI();
        al->show();
        al_clicked = 1;
    }
}
void Menu::activ() {
    if(ac_clicked == 1) {
        delete(lg);
        ac_clicked = 0;
    } else {
        ac = new ActivWidget();
        ac->show();
        ac_clicked = 1;
    }
}

void Menu::activity() {
}
