#include "finish.h"
#include "ui_finish.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QTextStream>

Finish::Finish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Finish)
{
    ui->setupUi(this);

    //Форма з фіксованими розмірами
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Finish::~Finish()
{
    delete ui;
}

void Finish::showReport(int size, bool *MAssAnswers, QString currentNameSurname, double perQuestion)
{
    int points = 0;
    for(int i = 0; i<=size; i++)
    {
        if (MAssAnswers[i] == true) points++;
    }


    results ="Cтудент: "+currentNameSurname+"\n"+
                             +"Оцінка за тест: "+QString::number(points*perQuestion)+"\n"+
                             +"Правильних відповідей: "+QString::number(points)+"\n"+
                             +"Кількість запитань: "+QString::number(size+1)+"\n"+
                             +"Відсоток успішності: "+QString::number((double(points)/(size+1))*100)+" % ";

    ui->label->setText(results);
}

void Finish::on_pushButton_clicked()
{
    QString fileName =  QFileDialog::getSaveFileName(
                this,
                tr("Save result"),                   //title
                "С:\\",                             //default folder
                "NTest Results (*.ntkR)"            //check only database files
                );

    QString encodeResults = encodeStr(results);

    QFile file(fileName);
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream out(&file);
                out.setCodec("UTF-8");
                out<<encodeResults;
                file.close();

    if(!fileName.isEmpty())
    {
        resSaved = true;
        this->close();
    }
    else resSaved = false;
}

QString Finish::encodeStr(const QString &str)
{
    QByteArray arr(str.toUtf8());
        for(int i =0; i<arr.size(); i++)
            arr[i] = arr[i] ^ key;

        return QString::fromLatin1(arr.toBase64());
}

void Finish::closeEvent(QCloseEvent *event)
{
    if(!resSaved)
    {
        QMessageBox msgBox;
        msgBox.setText("Зберегти результат?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if (res == QMessageBox::No)
        {
            event->accept();
        }
        else
        {
            on_pushButton_clicked();
            event->accept();
        }
    }
}
