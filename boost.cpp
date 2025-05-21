#include "boost.h"


Boost::Boost(int tool_id, QString name, int cost, double up, int emount, QWidget *parent)
    :QHBoxLayout(parent), tool_id(tool_id)
{
    setContentsMargins(5,5,0,10);
    pPB = new QPushButton(name);
    connect(pPB, &QPushButton::clicked, this, &Boost::send_boost);
    label_emount = new QLabel(QString::number(emount));
    label_cost = new QLabel(QString::number(cost));
    label_up = new QLabel(QString::number(up));

    recalculate(emount);

    addWidget(label_emount);
    addWidget(pPB);
    addWidget(label_up);
    addWidget(label_cost);
}

Boost::Boost(int tool_id, QString name, int cost, double up, QWidget *parent)
    :QHBoxLayout(parent), tool_id(tool_id)
{
    setContentsMargins(5,5,0,10);
    pPB = new QPushButton(name);

    pPB = new QPushButton(name);
    connect(pPB, &QPushButton::clicked, this, &Boost::send_boost);
    label_emount = new QLabel(QString::number(0));
    label_cost = new QLabel(QString::number(cost));
    label_up = new QLabel(QString::number(up));

    addWidget(label_emount);
    addWidget(pPB);
    addWidget(label_up);
    addWidget(label_cost);
}

void Boost::recalculate()
{
    double x = 7;
    label_cost->setText(QString::number(label_cost->text().toInt() * x));
}

void Boost::recalculate(int i)
{
    double x = 7;
    label_cost->setText(QString::number(label_cost->text().toInt() * pow(x, i)));
}

void Boost::up_emount()
{
    label_emount->setText(QString::number(label_emount->text().toInt() + 1));
    recalculate();
}

void Boost::send_boost() // шлёт бусть
{
    emit signal_boost(label_cost->text().toDouble(), label_up->text().toDouble());
}
