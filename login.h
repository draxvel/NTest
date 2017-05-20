#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    QString GetStudentName();

signals:
    loginDone();
    passNameSurname(QString text);

private slots:
    void on_pushButonOpenDB_clicked();

    void setConnectionDB ();
    void populateComboboxStudents ();

    void on_pushButtonOk_clicked();

private:
    Ui::Login *ui;

    QString fileName;
    QSqlDatabase database;

    QString StudentId [50];
    int Passwords [50];
};

#endif // LOGIN_H
