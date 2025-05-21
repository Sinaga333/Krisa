#include "base.h"

Base::Base()
{
    //user_id = 0;
}

bool Base::create_connection(QSqlDatabase& db)
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("dbforkrisa.db");
   db.setHostName("kotop");
   db.setUserName("Ananas");
   db.setPassword("12345");
   if (!db.open())
   {
    qDebug() << "Error connecting";
    return false;
   }
   QStringList list = db.tables();
   if (list.size() == 0)
   {
       qDebug() << "No tables";
   }
   return true;
}

std::vector<Tool*> Base::get_tools(QWidget* parent)
{
    QSqlDatabase db;
    std::vector<Tool*> tools;
    if(create_connection(db))
    {
    qDebug() << "Чтение из базы";
    QSqlQuery qq;
    if (!qq.exec("select * from smthtobuy;"))
    {
        close_db(db);
        qDebug() << "Error";
        return std::vector<Tool*> {NULL};
    }

    QSqlRecord rec = qq.record();
    QString name;
    double cost;
    double sec;
    int id;
    while (qq.next())
    {
        id = qq.value(rec.indexOf("id")).toInt();
        name = qq.value(rec.indexOf("name")).toString();
        cost = qq.value(rec.indexOf("cost")).toDouble();
        sec = qq.value(rec.indexOf("sec")).toDouble();
        tools.push_back(new Tool(id, name, cost, sec, parent));
    }
    close_db(db);
    return tools;
    }
    return std::vector<Tool*> {NULL};
}

std::vector<Boost *> Base::get_boosts(QWidget *parent)
{
    QSqlDatabase db;
    std::vector<Boost*> boosts;
    if(create_connection(db))
    {
        qDebug() << "Чтение из базы";
        QSqlQuery qq;
    if (!qq.exec("select * from boost;"))
    {
        close_db(db);
        qDebug() << "Error";
        return std::vector<Boost*> {NULL};
    }
    QSqlRecord rec = qq.record();
    int tool_id;
    QString name;
    double cost;
    double up;
    while (qq.next())
    {
        tool_id = qq.value(rec.indexOf("id")).toInt();
        name = qq.value(rec.indexOf("name")).toString();
        cost = qq.value(rec.indexOf("cost")).toDouble();
        up = qq.value(rec.indexOf("up")).toDouble();
        boosts.push_back(new Boost(tool_id, name, cost, up, parent));
    }
    close_db(db);
    return boosts;
    }
    return std::vector<Boost*> {NULL};
}

bool Base::add_user(User *u)
{
    QSqlDatabase db;
    qDebug() << "add_user";

    if(create_connection(db))
    {
    QSqlQuery qq;
    QString str("insert into users (email, login, password) values ('%1', '%2', %3);");
    str = str.arg(u->get_email())
            .arg(u->get_login())
            .arg(u->get_hpassword());
    if (!qq.exec(str))
    {
        qDebug() << "add_user fail";
        close_db(db);
        return false;
    }

    str = "select user_id from users where login = '%1';";
    //str = "select * from users;";
    str = str.arg(u->get_login());
    if (!qq.exec(str))
    {
        qDebug() << "fail(";
        close_db(db);
        return false;
    }
    QSqlRecord rec = qq.record();
    while(qq.next())
    {
        u->set_id(qq.value(rec.indexOf("user_id")).toUInt());
        u->set_email(qq.value(rec.indexOf("email")).toString());
        qDebug() << u->get_email();
    }
    close_db(db);
    qDebug() << "add_user +";
    return true;
    }
    return false;
}

bool Base::exist_user(User *u)
{
    QSqlDatabase db;
    if(create_connection(db))
    {
    QSqlQuery qq;
    QString str("select user_id, email, coins from users where login = '%1' AND password = '%2';");
    str = str.arg(u->get_login())
            .arg(u->get_hpassword());
    if (!qq.exec(str))
    {
        qDebug() << "exist_user fail";
        close_db(db);
        return false;
    }
    QSqlRecord rec = qq.record();
    int i = 0;
    while(qq.next())
    {
        u->set_id(qq.value(rec.indexOf("user_id")).toInt());
        u->set_email(qq.value(rec.indexOf("email")).toString());
        u->coins = qq.value(rec.indexOf("coins")).toDouble();
        i++;
    }
    if ( i != 1)
    {
        qDebug() << "exist_user fail i = " << i;
        close_db(db);
        return false;
    }
    close_db(db);
    return true;
    }
    return false;
}

bool Base::enter(std::vector<Boost *> &boosts, User *u)
{
    QSqlDatabase db;
    if(create_connection(db))
    {
        QSqlQuery qq;
    QString str = "select boost_id_1 from users_boosts where user_id = '%1'";
    str = str.arg(u->get_id());
    if (!qq.exec(str))
    {
        qDebug() << "enter error 1";
        close_db(db);
        return false;
    }
    QSqlRecord rec = qq.record();
    while(qq.next())
    {
        qDebug() << "enter reading b";
        for (int i = 0; i < boosts.size(); i++)
        {
            qDebug() << "enter reading boost";
            QString ind = "boost_id_%1";
            ind = ind.arg(i+1);
            boosts[i]->label_emount->setText(
                QString::number(qq.value(rec.indexOf(ind)).toInt()));
            boosts[i]->recalculate(qq.value(rec.indexOf(ind)).toInt());
            qDebug() << "enter reading boost" << boosts[i]->label_emount->text();

        }
    }
    qDebug() << "enter good";
    return true;

    }
    return false;
}

bool Base::enter(std::vector<Tool *>& tools, User* u)
{
    QSqlDatabase db;
    if(create_connection(db))
    {
        QSqlQuery qq;
        QString str = "select tool_id_1, tool_id_2, tool_id_3 from users_tools where user_id = '%1'";
        str = str.arg(u->get_id());
        if (!qq.exec(str))
        {
            qDebug() << "enter error 1";
            close_db(db);
            return false;
        }
        QSqlRecord rec = qq.record();

        while(qq.next())
        {
            qDebug() << "enter reading";
           for (int i = 0; i < tools.size(); i++)
            {
               QString ind = "tool_id_%1";
                ind = ind.arg(i+1);
                tools[i]->label_emount->setText(
                        QString::number(qq.value(rec.indexOf(ind)).toInt()));
                tools[i]->recalculate(qq.value(rec.indexOf(ind)).toInt());

            }
        }

        qDebug() << "enter good";
        return true;

    }
    return false;
}

void Base::close_db(QSqlDatabase &db)
{
    db.close();
    db.removeDatabase("qt_sql_default_connection");
}

bool Base::save(std::vector<Tool*>& tools, std::vector<Boost*>& boosts, User* u) // запись тулсов и деняк
{
    QSqlDatabase db;
    if(create_connection(db))
    {
        QSqlQuery qq;
        QString str = "insert or replace into users_tools(user_id, tool_id_1, tool_id_2,  tool_id_3) VALUES (%1, %2, %3, %4);";
        int i = 0;
        str = str.arg(u->get_id())
                .arg(tools[i++]->label_emount->text())
                .arg(tools[i++]->label_emount->text())
                .arg(tools[i++]->label_emount->text());
        if (!qq.exec(str))
        {
            qDebug() << "exit error 1";
            close_db(db);
            return false;
        }
        str = "insert into users(coins) values (%1);";
        str = str.arg(u->coins);
        if(!qq.exec(str))
        {
            qDebug() << "exit error 2";
            close_db(db);
            return false;
        }
        str = "insert or replace into users_boosts(user_id, boost_id_1) VALUES (%1, %2);";
        i = 0;
        str = str.arg(u->get_id())
                  .arg(boosts[i++]->label_emount->text());
        if (!qq.exec(str))
        {
            qDebug() << "exit error 1";
            close_db(db);
            return false;
        }
    close_db(db);
    return true;
    }
    return false;

}

