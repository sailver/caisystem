#ifndef COURSEFILEITEM_H
#define COURSEFILEITEM_H

#include <QGroupBox>
#include <io.h>
#include "sources/file_system/CaiDirectory.h"
using namespace std;

namespace Ui {
class courseFileItem;
}

class courseFileItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit courseFileItem(QWidget *parent = nullptr, FileData *file = nullptr);
    ~courseFileItem();

private:
    Ui::courseFileItem *ui;

};

#endif // COURSEFILEITEM_H
