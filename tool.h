#ifndef TOOL_H
#define TOOL_H

#include <QtWidgets>
#include <cmath>

class Tool : public QHBoxLayout
{
    Q_OBJECT
public:
    Tool(int id, QString name, int cost, double sec, QWidget *parent = 0);
    Tool(int id, QString name, int cost, double sec, int emount, QWidget *parent = 0);
    QPushButton* pPB;
    QLabel* label_sec;
    QLabel* label_cost;
    QLabel* label_emount;
    double boost;
    int id; // добавить

    void up_emount();
    double total_per_sec();
    void recalculate();
    void recalculate(int i);
    void set_boost(int emount, double boost);
signals:
    void cost_sec(int cost, double sec);
    void change_sec_boost(double prev, double now);
public slots:
    void slot_boost(double up); //улучшение при покупке буста
    void send_cost_sec();
};

#endif // TOOL_H
