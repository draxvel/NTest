#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QSqlQuery>
#include <QCloseEvent>
#include <finish.h>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
        
private slots:
    void on_pushButtonStart_clicked();
        
    void on_pushButtonNext_clicked();

    void on_pushButtonPrevious_clicked();

    void ToUi();

    void checkQuestion(int type, int id);

    void getNameSurname(QString text);

    void updateTimer();

    void cleanWidgets();

    void closeEvent(QCloseEvent *event);

signals:
    showFinishForm();
    showReport(int , bool *, QString, double);

private:
    Ui::MainWindow *ui;

    struct OneQuestion
    {
        int id;
        QString question;
        QString note;
        int type;
        QString answer1;
        QString answer2;
        QString answer3;
        QString answer4;
        QString correct;
    };

    OneQuestion *Element = new OneQuestion;
    std::vector <OneQuestion *> vect;

    bool *MassAnswers;

   int ID;
   int SIZE = 0;
   QString currentNameSurname;
   double perQuestion;

   Finish f;

   QTimer *mTimer;
   int mSecondsToEnd = 0;
   QLabel *infoLabel;
   QLabel *timeLabel;
};

#endif // MAINWINDOW_H
