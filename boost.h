#ifndef BOOST_H
#define BOOST_H
#include <QtWidgets>

class Boost : public QHBoxLayout
{
    Q_OBJECT
public:
    Boost(int tool_id, QString name, int cost, double up, int emount, QWidget* parent);
    Boost(int tool_id, QString name, int cost, double up, QWidget* parent);

    QPushButton* pPB;
    QLabel* label_emount;
    QLabel* label_up;
    QLabel* label_cost;
    int tool_id;

    void recalculate();
    void recalculate(int i);
    void up_emount();
signals:
    void signal_boost(double cost, double up);
public slots:
    void send_boost();
};


#endif // BOOST_H
