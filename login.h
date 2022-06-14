#ifndef LOGIN_H
#define LOGIN_H

#include <QGroupBox>
#include "menu.h"

namespace Ui {
class Login;
}

class Login : public QGroupBox
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    int isLogin = 0;
    Menu *m;
private slots:
    void login();
};

#endif // LOGIN_H
