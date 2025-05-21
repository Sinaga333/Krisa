#include "user.h"

User::User()
{}

User::User(QString login, QString password)
    : login(login)
{
    //hpassword = std::hash<QString>{}(password);
    hpassword = hfunk(password);
}

User::User(QString email, QString login, QString password)
    : email(email), login(login)
{
    hpassword = hfunk(password);
}

User::User(int user_id, QString email, QString login, size_t hpassword)
    : user_id(user_id), email(email), login(login), hpassword(hpassword)
{

}

size_t User::hfunk(QString password)
{
    return std::hash<std::string>{}(password.toStdString());
}

int User::get_id()
{
    return user_id;
}
QString User::get_email()
{
    return email;
}
QString User::get_login()
{
    return login;
}

size_t User::get_hpassword()
{
    return hpassword;
}

void User::set_email(QString email)
{
   this->email = email;
}

void User::set_password(QString password)
{
    this->hpassword = hfunk(password);
}

void User::set_id(int id)
{
    this->user_id = id;
}

