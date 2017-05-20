#ifndef FINISH_H
#define FINISH_H

#include <QDialog>

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

private:
    Ui::Finish *ui;
};

#endif // FINISH_H
