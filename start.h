#ifndef START_H
#define START_H

#include <QWidget>
#include <create_user.h>

namespace Ui {
class Start;
}
// добавить в ввод пароля звёздочки (или что то такое)
class Start : public QWidget
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();

    QBrush* brush;
    QPalette* palette;

private slots:
    void on_button_enter_clicked();
    void on_button_create_clicked();
signals:
    void success_connected(User* u);

private:
    Ui::Start *ui;
    void clear_lines();
};

#endif // START_H
