#ifndef POPHISTORY_H
#define POPHISTORY_H

#include <QWidget>
#include <QFile>
namespace Ui {
class popHistory;
}

class popHistory : public QWidget
{
    Q_OBJECT

public:
    explicit popHistory(QWidget *parent = nullptr);
    void showHistory(QString data);
    ~popHistory();

private slots:


    void on_clearButton_clicked();

private:
    Ui::popHistory *ui;
};

#endif // POPHISTORY_H
