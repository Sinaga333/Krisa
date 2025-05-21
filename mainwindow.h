#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <tool.h>
#include <base.h>>
#include <start.h>
#include <QPixmap>
#include <client.h>
#include <boost.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Start* s, QWidget *parent = nullptr);
    ~MainWindow();

    void set_boosts();

public slots:
    void on_pushButton_clicked();
    void up_per_sec(int cost, double sec);
    void up_boost(int cost, double up);
    void slot_change_sec_boost(double prev, double now);
    void timer_event();
    void slot_success_enter(User* u);
    //void slot_boost(int cost, double up); // ловит сигнал из буст
private:
    Ui::MainWindow *ui;
    QTimer* ptimer;
    std::vector<Tool*> ptools;
    std::vector<Boost*> pboosts;
    User* u;
signals:
    void signal_up_boost(double up);
};
#endif // MAINWINDOW_H
