#include "pophistory.h"
#include "ui_pophistory.h"

popHistory::popHistory(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::popHistory)
{
    ui->setupUi(this);
}

popHistory::~popHistory()
{
    delete ui;
}

void popHistory::showHistory(QString data){
    ui->textBrowser->setText(data);
}

void popHistory::on_clearButton_clicked(){
    ui->textBrowser->clear();
    std::string path=QApplication::applicationDirPath().toStdString()+"/../../../files/history.txt";
    QFile history(QString::fromStdString(path));
    history.open(QFile::WriteOnly|QFile::Truncate);
    history.close();
}
