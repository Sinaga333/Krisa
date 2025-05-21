#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Start* s, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(s, &Start::success_connected, this, &MainWindow::slot_success_enter);
    ui->lable_coins_per_click->setText("1");
    ui->lable_coins_per_sec->setText("0");

    QPixmap pix(":/fon/krisulya.jpg");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    //ui->pic_2->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    QVBoxLayout* pvlayout = new QVBoxLayout;
    QVBoxLayout* pvlayout_boosts = new QVBoxLayout;
    pvlayout->setContentsMargins(5,5,0,5);
    pvlayout_boosts->setContentsMargins(5,5,0,5);

    ptimer = new QTimer(this);
    ptimer->start(1000);

    ui->scrollArea->setLayout(pvlayout);
    ui->scrollArea_2->setLayout(pvlayout_boosts);

    ptools = Base::get_tools(this);
    pboosts = Base::get_boosts(this);
    for(int i = 0; i < ptools.size() ; i++)
    {
    for (int j = 0; j < pboosts.size() ; j++)
    {
        if(pboosts[j]->tool_id == ptools[i]->id)
        {
            connect(pboosts[j], &Boost::signal_boost, this, &MainWindow::up_boost);
            connect(this, &MainWindow::signal_up_boost, ptools[i], &Tool::slot_boost);
            connect(ptools[i], &Tool::change_sec_boost, this, &MainWindow::slot_change_sec_boost);
            pvlayout_boosts->addLayout(pboosts[j]);
        } //работает и не трогать)
        //сделать запись и чтение
       connect(ptools[i], &Tool::cost_sec, this, &MainWindow::up_per_sec);
       pvlayout->addLayout(ptools[i]);
    }
    //надо понять куда вставить
     qDebug() << "main";
    }
    //set_boosts();
    ui->scrollArea->setLayout(pvlayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_boosts()
{
    qDebug() << "set_boosts";
    // тут будет типа назначение бустов для тулов
    for(int i = 0; i < ptools.size() ; i++)
    {
        for (int j = 0; j < pboosts.size() ; j++)
        {
            if(pboosts[j]->tool_id == ptools[i]->id)
            {
                qDebug() << "set_boosts" << pboosts[i]->label_emount->text().toInt();
                qDebug() << "set_boosts" << pboosts[i]->label_up->text().toDouble();
                ptools[i]->set_boost(pboosts[i]->label_emount->text().toInt(), pboosts[i]->label_up->text().toDouble());
            }
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    double c = ui->lable_coins_per_click->text().toDouble();
    c +=  ui->lable_coins->text().toDouble();
    ui->lable_coins->setText(QString::number(c));
}

void MainWindow::up_per_sec(int cost, double sec)
{
    if (cost <= ui->lable_coins->text().toDouble())
    {
        ui->lable_coins->setText(QString::number(ui->lable_coins->text().toDouble()-cost));
        ui->lable_coins_per_sec->setText(QString::number(ui->lable_coins_per_sec->text().toDouble() + sec));
        Tool* t = qobject_cast<Tool*>(sender());
        t->up_emount();
    }
}

void MainWindow::up_boost(int cost, double up)
{
    qDebug() << "up_boost";
    if (cost <= ui->lable_coins->text().toDouble())
    {
        ui->lable_coins->setText(QString::number(ui->lable_coins->text().toDouble()-cost));
        emit signal_up_boost(up);
        Boost* b = qobject_cast<Boost*>(sender());
        b->up_emount();
    }
}

void MainWindow::slot_change_sec_boost(double prev, double now)
{
    qDebug() << "slot_change_sec_boost";
    ui->lable_coins_per_sec->setText(QString::number(ui->lable_coins_per_sec->text().toDouble() - prev + now));
}

 void MainWindow::timer_event()
 {
     Base::save(ptools, pboosts, u);
     ui->lable_coins->setText(QString::number(ui->lable_coins->text().toDouble() + ui->lable_coins_per_sec->text().toDouble()));
 }

 void MainWindow::slot_success_enter(User* u)
 {
     this->u = u;
     connect(ptimer, SIGNAL(timeout()), SLOT(timer_event()));
     ui->lable_coins->setText(QString::number(u->coins));
     Base::enter(ptools, u);
     qDebug() << "base2";
     Base::enter(pboosts, u);
     for (int i = 0; i < ptools.size(); i++)
     {
         ui->lable_coins_per_sec->setText(
                     QString::number(ui->lable_coins_per_sec->text().toDouble() +
                     ptools[i]->total_per_sec()));
     }
     this->show();
     set_boosts();
 }
