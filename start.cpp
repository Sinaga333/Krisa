#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    QPixmap pix(":/fon/krisulya.jpg");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

Start::~Start()
{
    delete ui;
}

void Start::on_button_enter_clicked()
{
    QString login = ui->line_login->text();
    QString password = ui->line_password->text();
    User* u = new User(login, password);
    if (!Base::exist_user(u))
    {
        clear_lines();
        qDebug() << "Error: exist_user";
        delete u;
    }
    else
    {
        emit success_connected(u);
        this->hide();

    }
}


void Start::on_button_create_clicked()
{
    Create_user* cu = new Create_user(this);
    this->hide();
    cu->show();
    clear_lines();
    connect(cu, &Create_user::success_connected, this, &Start::success_connected);
}

void Start::clear_lines()
{
    ui->line_login->clear();
    ui->line_password->clear();
}

