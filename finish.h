#ifndef FINISH_H
#define FINISH_H

#include <QDialog>
#include <QString>
#include <QCloseEvent>

namespace Ui {
class Finish;
}

class Finish : public QDialog
{
    Q_OBJECT

public:
    explicit Finish(QWidget *parent = 0);
    ~Finish();

public Q_SLOTS:
    void showReport(int size, bool *MAssAnswers, QString currentNameSurname, double perQuestion);

private slots:
    void on_pushButton_clicked();

    QString encodeStr(const QString& str);

    void closeEvent(QCloseEvent *event);

private:
    Ui::Finish *ui;

    QString results;

    bool resSaved = false;

    const  quint32 key = 073; //шифр
};

#endif // FINISH_H
