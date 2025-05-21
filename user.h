#ifndef USER_H
#define USER_H
#include <QString>
#include <string>

class User
{

public:
    User();
    User(QString login, QString password);
    User(QString email, QString login, QString password);
    int get_id();
    QString get_email();
    QString get_login();
    size_t get_hpassword();

    void set_email(QString email);
    void set_password(QString password);
    void set_id(int id);

    double coins;

    static size_t hfunk(QString password);
private:
    User(int user_id, QString email, QString login, size_t hpassword);
    //static int user_id;
    int user_id;
    QString email;
    QString login;
    size_t hpassword;



};

#endif // USER_H
