#include "logui.h"
#include "ui_logui.h"
using namespace std;

LogUI::LogUI(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::LogUI)
{
    ui->setupUi(this);
    this->showLog();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(showLog()));
}

LogUI::~LogUI()
{
    delete ui;
}

void LogUI::showLog() {
    syslog *log = new syslog;
    log->open();
    string text = log->show();
    log->close();
    ui->textEdit->setText(QString::fromStdString(text).replace("\\n","\n"));
}

void LogUI::search() {
    int type = ui->comboBox->currentIndex();
    string str = ui->lineEdit->text().toStdString();
    syslog *log = new syslog;
    log->open();
    string text = log->search(type, str);
    log->close();
    ui->textEdit->setText(QString::fromStdString(text).replace("\\n","\n"));
}
