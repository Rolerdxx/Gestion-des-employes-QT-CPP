
#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlDatabase>


class dbmanager
{
public:
    dbmanager();
    bool conn();
    void disc();

    bool login(const QString &logname,const QString &mdp);
private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
