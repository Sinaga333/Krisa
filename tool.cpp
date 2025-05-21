#include "tool.h"

Tool::Tool(int id, QString name, int cost, double sec, QWidget *parent)
    : QHBoxLayout(parent), id(id)
{
    boost = 1;
    setContentsMargins(5,5,0,10);
    pPB = new QPushButton(name);
    connect(pPB, SIGNAL(clicked()), SLOT(send_cost_sec())); // написать увеличение счёта
    label_sec = new QLabel(QString::number(sec));
    label_cost = new QLabel(QString::number(cost));
    label_emount = new QLabel(QString::number(0));
    addWidget(label_emount);
    addWidget(pPB);
    addWidget(label_sec);
    addWidget(label_cost);
}

Tool::Tool(int id, QString name, int cost, double sec, int emount, QWidget *parent)
    : QHBoxLayout(parent), id(id)
{
    boost = 1;
    setContentsMargins(5,5,0,10);
    pPB = new QPushButton(name);
    connect(pPB, SIGNAL(clicked()), SLOT(send_cost_sec()));
    label_sec = new QLabel(QString::number(sec));
    label_emount = new QLabel(QString::number(emount));//
    label_cost = new QLabel(QString::number(cost));//
    recalculate(emount);
    addWidget(label_emount);
    addWidget(pPB);
    addWidget(label_sec);
    addWidget(label_cost);
}

void Tool::up_emount()
{
    label_emount->setText(QString::number(label_emount->text().toInt() + 1));
    recalculate();
}

double Tool::total_per_sec()
{
    return label_emount->text().toDouble() * label_sec->text().toDouble();
}

void Tool::recalculate()
{
    double x = 1.1;
    label_cost->setText(QString::number(label_cost->text().toDouble() * x));
}

void Tool::recalculate(int i)
{
    double x = pow(1.1, i);
    label_cost->setText(QString::number(label_cost->text().toDouble() * x));
}

void Tool::set_boost(int emount, double boost) //в начале типа если были бусты
{

    this->boost += boost*emount;
    label_sec->setText(QString::number(label_sec->text().toDouble() * this->boost));
}

void Tool::slot_boost(double up) // ну оно постоянно рабоатет
{
    qDebug() << "slot_boost" << boost;
    double prev = total_per_sec();
    label_sec->setText(QString::number((label_sec->text().toDouble() / boost) * (boost + up)));
    boost += up;
    qDebug() << "slot_boost 2" << boost;
    emit change_sec_boost(prev, total_per_sec());
}


void Tool::send_cost_sec()
{
    emit cost_sec(label_cost->text().toInt(), label_sec->text().toDouble());
}
