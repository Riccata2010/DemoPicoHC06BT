#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void fixedSize();
    void showLed1();
    void showLed2();
    void showLed3();
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void showLed(unsigned int led);
};
#endif // MAINWINDOW_H
