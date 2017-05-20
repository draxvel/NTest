#include "finish.h"
#include "ui_finish.h"

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

    ui->label->setText("Cтудент: "+currentNameSurname+"\n"+
                             +"\t Оцінка за тест: "+QString::number(points*perQuestion)+"\n"+
                             +"Правильних відповідей: "+QString::number(points)+"\n"+
                             +"Кількість запитань: "+QString::number(size+1)+"\n"+
                             +"Відсоток успішності: "+QString::number((double(points)/(size+1))*100)+" % ");
}
