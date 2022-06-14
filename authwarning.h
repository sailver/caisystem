#ifndef AUTHWARNING_H
#define AUTHWARNING_H

#include <QGroupBox>

namespace Ui {
class AuthWarning;
}

class AuthWarning : public QGroupBox
{
    Q_OBJECT

public:
    explicit AuthWarning(QWidget *parent = nullptr);
    ~AuthWarning();

private:
    Ui::AuthWarning *ui;
};

#endif // AUTHWARNING_H
