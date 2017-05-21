#include "login.h"
#include "ui_login.h"

#include <mainwindow.h>

#include <QFileDialog>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QtSql>

#include <QMessageBox>

#include <QDebug>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

QString Login::GetStudentName()
{
    return ui->comboBoxStudents->currentText();
}

void Login::on_pushButonOpenDB_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),                    //title
                "С:\\",                             //default folder
                "Test File (*.db)" //check only database files
                );
    setConnectionDB();
}

void Login::setConnectionDB()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(fileName);

    if(!database.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Помилка відкриття БД!");
        msgBox.exec();
    }
    else
    {
        ui->comboBoxStudents->setEnabled(true);
        populateComboboxStudents();
    }
}

void Login::populateComboboxStudents()
{
    if(ui->comboBoxStudents->count() == 0)
       {
            QSqlQuery query;

            query.exec("SELECT * FROM Student");

            for(int i=0; query.next(); i++)
            {
                StudentId[i] = query.value(0).toInt();
                Passwords[i] = query.value(3).toInt();
                ui->comboBoxStudents->addItem(query.value(1).toString() +" " + query.value(2).toString());
            }

             ui->lineEditPassword->setEnabled(true);
             ui->pushButtonOk->setEnabled(true);
        }
    ui->lineEditPassword->setFocus();
}


void Login::on_pushButtonOk_clicked()
{
    int index = ui->comboBoxStudents->currentIndex();

    if(ui->lineEditPassword->text().toInt() == Passwords[index])
    {
        loginDone();
        passNameSurname((ui->comboBoxStudents->currentText()));
        this->close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Невірний пароль!");
        msgBox.exec();
        ui->lineEditPassword->clear();
    }
}

