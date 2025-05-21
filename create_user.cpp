#include "create_user.h"
#include "ui_create_user.h"

Create_user::Create_user(QWidget *parent) :
    QWidget(NULL),
    ui(new Ui::Create_user)
{
    ui->setupUi(this);
    p = parent;
    QPixmap pix(":/fon/krisulya.jpg");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

}

Create_user::~Create_user()
{
    delete ui;
}


void Create_user::on_button_create_clicked()
{
    if (ui->line_password->text() != ui->line_repit_password->text())
    {
        ui->label->setText("Пароли не совпадают");
        return;
    }
    User* u = new User( ui->line_email->text(),
                        ui->line_login->text(),
                        ui->line_password->text());
    clear_lines();
    if(Base::add_user(u))
    {
        emit success_connected(u);
        qDebug() << "user created";
        p->hide();
        this->hide();
    }
    else
    {
        ui->label->setText("Ошибка регестрации, попробуйте ещё раз");
        delete u;
    }
}


void Create_user::on_button_back_clicked()
{
    p->show();
    this->close();
    clear_lines();
}

void Create_user::clear_lines()
{
    ui->line_login->clear();
    ui->line_password->clear();
    ui->line_repit_password->clear();
    ui->line_email->clear();
}

