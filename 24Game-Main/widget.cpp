#include "widget.h"
#include "ui_widget.h"
#include <sstream>
#include <fstream>
#include <vector>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


bool checkInvalidInput(QString input){
    if(input.length()==2){
        if(input=="10")return 1;
        else return 0;
    }
    else {
        if(input.length()!=1)return 0;
        if(
            !(
                (input>="1"&&input<="9")||
                (input=="J")||(input=="j")||
                (input=="Q")||(input=="q")||
                (input=="K")||(input=="k")
                )
            )
            return 0;
        return 1;
    }
}

void raiseInputError(QString input1,QString input2,QString input3,QString input4){
    bool check=checkInvalidInput(input1)&&checkInvalidInput(input2)&&checkInvalidInput(input3)&&checkInvalidInput(input4);
    if(!check){
        QMessageBox::warning(NULL,"Error","Invalid input",QMessageBox::Ok|QMessageBox::Cancel);
    }
}

int convert(QString str){
    if(str.length()==2)return 10;
    if(str=="J"||str=="j")return 11;
    if(str=="Q"||str=="q")return 12;
    if(str=="K"||str=="k")return 13;
    int res=str.toInt();
    return res;
}

const double Threshold = 1E-6;
const int CardsNumber = 4;
const int ResultValue = 24;
double number[CardsNumber];
std::string result[CardsNumber];

bool PointsGame(int n){
    if (n == 1){
        if (fabs(number[0] - ResultValue) < Threshold){
            return true;
        }
        else{
            return false;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            double a, b;
            std::string expa, expb;
            a = number[i];
            b = number[j];
            number[j] = number[n - 1];
            expa = result[i];
            expb = result[j];
            result[j] = result[n - 1];
            result[i] = '(' + expa + '+' + expb + ')';
            number[i] = a + b;
            if (PointsGame(n - 1))
                return true;
            result[i] = '(' + expa + '-' + expb + ')';
            number[i] = a - b;
            if (PointsGame(n - 1))
                return true;
            result[i] = '(' + expb + '-' + expa + ')';
            number[i] = b - a;
            if (PointsGame(n - 1))
                return true;
            result[i] = '(' + expa + '*' + expb + ')';
            number[i] = a * b;
            if (PointsGame(n - 1))
                return true;
            if (b != 0){
                result[i] = '(' + expa + '/' + expb + ')';
                number[i] = a / b;
                if (PointsGame(n - 1))
                    return true;
            }
            if (a != 0){
                result[i] = '(' + expb + '/' + expa + ')';
                number[i] = b / a;
                if (PointsGame(n - 1))
                    return true;
            }

            number[i] = a;
            number[j] = b;
            result[i] = expa;
            result[j] = expb;
        }
    }
    return false;
}

void Widget::on_retryButton_clicked(){
    ui->outputBrowser->clear();
    ui->input1->clear();
    ui->input2->clear();
    ui->input3->clear();
    ui->input4->clear();
}

void Widget::on_calcButton_clicked(){
    std::ofstream output(QApplication::applicationDirPath().toStdString()+"/../../../files/history.txt",std::ios::out|std::ios::app);
    QString Num1 = ui->input1->text();
    QString Num2 = ui->input2->text();
    QString Num3 = ui->input3->text();
    QString Num4 = ui->input4->text();
    raiseInputError(Num1,Num2,Num3,Num4);

    int elem1=convert(Num1);
    int elem2=convert(Num2);
    int elem3=convert(Num3);
    int elem4=convert(Num4);

    number[0]=elem1*1.0;
    number[1]=elem2*1.0;
    number[2]=elem3*1.0;
    number[3]=elem4*1.0;
    result[0]=Num1.toStdString();
    result[1]=Num2.toStdString();
    result[2]=Num3.toStdString();
    result[3]=Num4.toStdString();

    bool success = PointsGame(CardsNumber);
    if(success){
        ui->outputBrowser->clear();
        ui->outputBrowser->setText("SUCCESS!\n");
        QString str = QString::fromStdString(result[0]+"=24");
        ui->outputBrowser->append(str);
        output<<"SUCCESS!\n"<<result[0]+"=24\n";
    }
    else {
        ui->outputBrowser->clear();
        ui->outputBrowser->setText("FAIL!\n");
        output<<"FAIL!\n";
    }
    output.close();
}


void Widget::on_historyButton_clicked(){
    popHistory *historyWindow = new popHistory;
    historyWindow->setWindowModality(Qt::ApplicationModal);
    historyWindow->show();
    QString data;
    std::string path=QApplication::applicationDirPath().toStdString()+"/../../../files/history.txt";
    QFile history(QString::fromStdString(path));
    if(!history.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(NULL,"Error","Fail to open history file!",QMessageBox::Ok|QMessageBox::Cancel);
    }
    while(!history.atEnd()){
        QByteArray array=history.readLine();
        QString str(array);
        data.append(array);
    }
    historyWindow->showHistory(data);
    history.close();
}

std::vector<std::string> lines;
void Widget::on_fileBrowseButton_clicked(){
    QFileDialog* fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("Please select a file(.txt)");
    fileDialog->setNameFilter(tr("File(*.txt)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setWindowModality(Qt::ApplicationModal);
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    if(fileNames.size()==0)return;
    QFile file(fileNames[0]);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    int lineCount=0;
    int successCount=0;
    while(!file.atEnd()){
        QByteArray array=file.readLine();
        lineCount++;
        QString str(array);
        std::string line=array.toStdString();
        std::stringstream ss;
        std::string Num1;
        std::string Num2;
        std::string Num3;
        std::string Num4;
        ss<<line;
        ss>>Num1>>Num2>>Num3>>Num4;
        raiseInputError(QString::fromStdString(Num1),QString::fromStdString(Num2),QString::fromStdString(Num3),QString::fromStdString(Num4));
        int elem1=convert(QString::fromStdString(Num1));
        int elem2=convert(QString::fromStdString(Num2));
        int elem3=convert(QString::fromStdString(Num3));
        int elem4=convert(QString::fromStdString(Num4));
        number[0]=elem1*1.0;
        number[1]=elem2*1.0;
        number[2]=elem3*1.0;
        number[3]=elem4*1.0;
        result[0]=Num1;
        result[1]=Num2;
        result[2]=Num3;
        result[3]=Num4;
        bool success = PointsGame(CardsNumber);
        if(success){
            successCount++;
            std::string res=line;
            res="+\t"+res;
            lines.push_back(res);
        }
        else {
            std::string res=line;
            res="-\t"+res;
            lines.push_back(res);
        }
    }
    file.close();
    QFile output(fileNames[0]);
    output.open(QIODevice::ReadWrite|QIODevice::Text);
    for(size_t i=0;i<lines.size();++i){
        output.write(QString::fromStdString(lines[i]).toUtf8());
    }
    std::string rateOutput;
    rateOutput=std::to_string(successCount)+"/"+std::to_string(lineCount);
    output.write(QString::fromStdString(rateOutput).toUtf8());
    QMessageBox::warning(NULL,"Complete","Operation completed!",QMessageBox::Ok|QMessageBox::Cancel);
    output.close();
}

