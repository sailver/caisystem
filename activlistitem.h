#ifndef ACTIVLISTITEM_H
#define ACTIVLISTITEM_H

#include <QGroupBox>
#include "sources/activity_system/basic.h"

namespace Ui {
class ActivListItem;
}

class ActivListItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit ActivListItem(QWidget *parent = nullptr, ActivBasic *a = nullptr);
    ~ActivListItem();

private:
    Ui::ActivListItem *ui;
};

#endif // ACTIVLISTITEM_H
