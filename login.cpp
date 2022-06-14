#include "login.h"
#include "ui_login.h"
#include "sources/user_system/user.h"

using namespace std;

Login::Login(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit->setText("testuser");
    ui->lineEdit_2->setText("123456");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(login()));
    connect(ui->lineEdit_2,SIGNAL(returnPressed()),ui->pushButton,SLOT(clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::login() {
    if(isLogin == 1) {
        delete(m);
        ui->pushButton->setText("登录");
        isLogin = 0;
        return;
    }
    string name = ui->lineEdit->text().toStdString();
    string password = ui->lineEdit_2->text().toStdString();
    User *user = new User();
    if(user->login(name,password)) {
        isLogin = 1;
        ui->info->setText("");
        ui->pushButton->setText("退出登录");
        m = new Menu;
        m->show();
    } else {
        ui->info->setText("无效用户信息");
    }
}
