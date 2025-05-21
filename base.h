#ifndef BASE_H
#define BASE_H
#include <tool.h>
#include <vector>
#include <QtSql>
#include <user.h>
#include <boost.h>

class Base
{

public:
    Base();

    static std::vector<Tool*> get_tools(QWidget* parent);
    static std::vector<Boost*> get_boosts(QWidget* parent);
    static bool add_user(User* u);
    static bool exist_user(User* u);
    static bool enter(std::vector<Boost*>& boosts,  User* u);
    static bool enter(std::vector<Tool*>& tools, User* u);
    static bool save(std::vector<Tool*>& tools, std::vector<Boost*>& boosts, User* u);
 private:
    static void close_db(QSqlDatabase& db);
    static bool create_connection(QSqlDatabase& db);
};

#endif // BASE_H
