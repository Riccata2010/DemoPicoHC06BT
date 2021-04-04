#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->installEventFilter(this);
    this->fixedSize();

    QPushButton *b1 = ui->pushButton_1;
    QPushButton *b2 = ui->pushButton_2;
    QPushButton *b3 = ui->pushButton_3;

    connect(b1, &QPushButton::clicked, this, &MainWindow::showLed1);
    connect(b2, &QPushButton::clicked, this, &MainWindow::showLed2);
    connect(b3, &QPushButton::clicked, this, &MainWindow::showLed3);

    QProcess *process = new QProcess(this);
    process->start("../DemoPicoClient/conn-led.sh");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fixedSize()
{
    int w = this->geometry().width();
    int h = this->geometry().height();
    this->setFixedSize(QSize(w, h));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("key press %d", keyEvent->key());
        switch(keyEvent->key()) {
            case 49:{
                showLed1();
                break;
            }
            case 50:{
                showLed2();
                break;
            }
            case 51:{
                showLed3();
                break;
            }
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::showLed1()
{ this->showLed(1); }

void MainWindow::showLed2()
{ this->showLed(2); }

void MainWindow::showLed3()
{ this->showLed(3); }

void MainWindow::showLed(unsigned int led)
{
    QProcess *process = new QProcess(this);

    QString command = "../DemoPicoClient/show-led.sh";
    process->start(command, QStringList() << QString::number(led));

    process->waitForFinished();
    QString output(process->readAllStandardOutput());
}

