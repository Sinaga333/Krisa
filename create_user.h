#ifndef CREATE_USER_H
#define CREATE_USER_H

#include <QWidget>
#include <base.h>
#include <user.h>
namespace Ui {
class Create_user;
}
// добавить в ввод пароля звёздочки (или что то такое)
class Create_user : public QWidget
{
    Q_OBJECT

public:
    explicit Create_user(QWidget *parent = nullptr);
    ~Create_user();
    QWidget *p;
private slots:
    void on_button_create_clicked();
    void on_button_back_clicked();
signals:
    void success_connected(User* u);

private:
    Ui::Create_user *ui;
    void clear_lines();

};

#endif // CREATE_USER_H
