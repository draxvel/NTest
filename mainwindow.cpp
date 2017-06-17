#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finish.h"
#include <ctime>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Форма з фіксованими розмірами
    this->setFixedSize(this->geometry().width(),this->geometry().height());

    //Створюємо таймер
    mTimer = new QTimer(this);
    //Оновлємо час в статусБарі щосекунди
    QObject::connect(mTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    //Початкові налаштування. Сторінка "Старт" і кнопки переключення робимо невидимі
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButtonPrevious->setVisible(false);
    ui->pushButtonNext->setVisible(false);

    //Створюємо лейбли для СтатусБару
    infoLabel = new QLabel(this);
    timeLabel = new QLabel(this);
    //додаємо у СтатусБар

    ui->statusBar->addPermanentWidget(infoLabel, 3);

    //При закритті MainWindow передаємо дані у форма Finish
    QObject::connect(this, SIGNAL(showFinishForm()), &f, SLOT(show()));
    QObject::connect(this, SIGNAL(showReport(int, bool *, QString, double)), &f, SLOT(showReport(int, bool *, QString, double)));
}

MainWindow::~MainWindow()
{
    //Вивільнення пам'яті
    delete ui;
    delete mTimer;
    delete infoLabel;
    delete timeLabel;
    delete Element;
    delete [] MassAnswers;
}

void MainWindow::on_pushButtonStart_clicked()
{
    //Ховаємо сторінку "Старт"
    ui->pageStart->hide();
    //Кнопка "Наступне запитання" стає доступною
    ui->pushButtonNext->setVisible(true);

    //Стартує таймер
    mTimer->start(1000);

    //Питання нульове
    ID=0;
    ToUi();
}


void MainWindow::on_pushButtonNext_clicked()
{
    //Перевіряємо дане запитання
    checkQuestion(Element->type, ID);

    if(ID==SIZE-1)
    {
        QMessageBox msgBox;
        msgBox.setText("Увага! Останнє запитання!");
        msgBox.exec();
    }

    //Якщо ще є запитання
    if(ID<SIZE)
    {
        ID++;
        ToUi();
    }
    else
    {
        showFinishForm();
        showReport(SIZE, MassAnswers, currentNameSurname, perQuestion);
        ID++;
        this->close();
    }
}

void MainWindow::on_pushButtonPrevious_clicked()
{
    //Якщо ще є попередні запитання
    if(ID)
    {
        ID--;
        ToUi();
    }
}

void MainWindow::ToUi()
{
    //Нумерація запитання у спочатку у infoLabel потім у СтатусБар
    infoLabel->setText("Запитання: "+QString::number(ID+1)+"/"+QString::number(SIZE+1));

    //Перевірка чи не останнє запитання
    if(ID==SIZE)
    {
        ui->pushButtonNext->setText("Завершити");
        ui->pushButtonNext->setToolTip("Завершити даний тест");
    }
    else
    {
        ui->pushButtonNext->setText("Відповісти");
        ui->pushButtonNext->setToolTip("Наступне запитання");

    }

    if(ID)
    {
       ui->pushButtonPrevious->setVisible(true);
    }
    else ui->pushButtonPrevious->setVisible(false);


    //Сховаємо всі пейджі
    ui->pageOneAswer->hide();
    ui->pageFewAnswers->hide();
    ui->pageWriteAnswer->hide();

    //очищення попередніх дій
    cleanWidgets();


    //------Заповнення віджетів

    //витягуємо все з масива у тимчасову структуру
    Element = vect[ID];

    //Залежно від типу питання заповнюємо віджети інформацією
    switch (Element->type)
    {
        case 1:
       {
                ui->pageOneAswer->show();
                ui->labelText->setText(Element->question);
                ui->labelNote->setText(Element->note);

                ui->radioButtonAnswer1->setText(Element->answer1);
                ui->radioButtonAnswer2->setText(Element->answer2);
                ui->radioButtonAnswer3->setText(Element->answer3);
                ui->radioButtonAnswer4->setText(Element->answer4);
                break;
        }
        case 2:
        {
                ui->pageFewAnswers->show();
                ui->labelText->setText(Element->question);
                ui->labelNote->setText(Element->note);

                ui->checkBoxAnswer1->setText(Element->answer1);
                ui->checkBoxAnswer2->setText(Element->answer2);
                ui->checkBoxAnswer3->setText(Element->answer3);
                ui->checkBoxAnswer4->setText(Element->answer4);
                break;
         }
         case 3:
         {
                ui->pageWriteAnswer->show();
                ui->labelText->setText(Element->question);
                ui->labelNote->setText(Element->note);
                break;
          }
     }
}

void MainWindow::checkQuestion(int type, int id)
{
    Element = vect[ID];

    //Отримаємо правльну відповідь
    QString tempCorrectAnswer = Element->correct;

    switch (type) {
    case 1:
           {
                if(ui->radioButtonAnswer1->isChecked() && tempCorrectAnswer[0] == "1") MassAnswers[id] = true;
               else
                if(ui->radioButtonAnswer2->isChecked() && tempCorrectAnswer[1] == "1") MassAnswers[id] = true;
               else
                if(ui->radioButtonAnswer3->isChecked() && tempCorrectAnswer[2] == "1") MassAnswers[id] = true;
               else
                if(ui->radioButtonAnswer4->isChecked() && tempCorrectAnswer[3] == "1") MassAnswers[id] = true;
                else
                    MassAnswers[id] = false;
               break;
           }

    case 2:
           {
               bool itsOk = true;

               if(!ui->checkBoxAnswer1->isChecked() && tempCorrectAnswer[0] == "1")
                   itsOk = false;
            else
               if(!ui->checkBoxAnswer2->isChecked() && tempCorrectAnswer[1] == "1")
                   itsOk = false;
            else
               if(!ui->checkBoxAnswer3->isChecked() && tempCorrectAnswer[2] == "1")
                   itsOk = false;
            else
               if(!ui->checkBoxAnswer4->isChecked() && tempCorrectAnswer[3] == "1")
                   itsOk = false;

               if(itsOk) MassAnswers[id] = true;
               else
                   MassAnswers[id] = false;
               break;
           }

    case 3:
           {
            if(ui->textEditAnswer->toPlainText().toLower() == tempCorrectAnswer) MassAnswers[id] = true;
            else
                MassAnswers[id] = false;
           }
    default:
        break;
    }
}

void MainWindow::getNameSurname(QString text)
{
    QSqlQuery query;

    //Наповнюємо масив, який складається з питань
    query.exec("SELECT id FROM Question");

    while (query.next())
    {
        SIZE = query.value(0).toInt();
    }

    query.exec("SELECT * FROM Question");

    for (int i = 0; i<=SIZE; i++)
    {
        query.next();

        Element = new OneQuestion;

        Element->id = query.value(0).toInt();

        Element->question = query.value(1).toString();
        Element->note = query.value(2).toString();
        Element->type = query.value(3).toInt();

        Element->answer1 = query.value(4).toString();
        Element->answer2 = query.value(5).toString();
        Element->answer3 = query.value(6).toString();
        Element->answer4 = query.value(7).toString();
        Element->correct = query.value(8).toString();

        vect.push_back(Element);
    }

    Element = NULL;

    ID = 0;

    MassAnswers = new bool [SIZE];

    std::random_shuffle(vect.begin(), vect.end());

    //Витягнемо інформацію з БД для початкової сторінки
    query.exec("SELECT * FROM About");

    QString title;
    int time;
    QString author;

   if(query.next())
   {
        title = query.value(0).toString();
        time  = query.value(1).toInt();
        author = query.value(2).toString();
        perQuestion = query.value(3).toDouble();
    }

    currentNameSurname = text;
    ui->labelText->setText("Привіт, "+currentNameSurname);
    ui->labelNote->setText("За декілька секунд розпочнеться тестування \""+title+"\". \n"+
                           "Для проходження тесту у вас є "+QString::number(time)+" хв. \n"+
                           "Кожна правильна відповідь оцінюється у "+QString::number(perQuestion)+" б. \n"+
                           "Автор тесту - "+author+". \n"
                           "Щоб розпочати тестування натисніть кнопку нижче. \n"+
                           "\t\tБажаємо успіхів!");

    mSecondsToEnd = 60*time;
}

void MainWindow::updateTimer()
{
    --mSecondsToEnd;
       if ( mSecondsToEnd > 0)
       {
           if(mSecondsToEnd>60)
               timeLabel->setText("Залишилось часу: " + QString::number(mSecondsToEnd/60) + " хв "+ QString::number(mSecondsToEnd%60) + " c ");
           else  timeLabel->setText("Залишилось часу: " + QString::number(mSecondsToEnd) + " c ");

           ui->statusBar->addPermanentWidget(timeLabel);
       }
       else
       {
           mTimer->stop();
           showFinishForm();
           showReport(SIZE, MassAnswers, currentNameSurname, perQuestion);
           this->close();
       }
}

void MainWindow::cleanWidgets()
{
    ui->radioButtonAnswer1->setAutoExclusive(false);
    ui->radioButtonAnswer1->setChecked(false);

    ui->radioButtonAnswer2->setAutoExclusive(false);
    ui->radioButtonAnswer2->setChecked(false);

    ui->radioButtonAnswer3->setAutoExclusive(false);
    ui->radioButtonAnswer3->setChecked(false);

    ui->radioButtonAnswer4->setAutoExclusive(false);
    ui->radioButtonAnswer4->setChecked(false);

    ui->checkBoxAnswer1->setChecked(false);
    ui->checkBoxAnswer2->setChecked(false);
    ui->checkBoxAnswer3->setChecked(false);
    ui->checkBoxAnswer4->setChecked(false);

    ui->textEditAnswer->clear();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ID<=SIZE)
    {
        QMessageBox msgBox;
        msgBox.setText("Вийти з програми? Результат не буде збережено.");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if (res == QMessageBox::No)
        {
            event->ignore();
        }
        else
            event->accept();
    }
}

