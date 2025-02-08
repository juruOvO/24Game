#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <math.h>
#include <QApplication>
#include <pophistory.h>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_calcButton_clicked();

    void on_retryButton_clicked();

    void on_historyButton_clicked();

    void on_fileBrowseButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
