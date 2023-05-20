
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

    bool addPer(const QString& nom,const QString& prenom,const QString& adresse,const QString& fonction,const QString& cin,const QString& date,const float& salaire,const int& Dep);
    bool modPer(const int& id,const QString& nom,const QString& prenom,const QString& adresse,const QString& fonction,const QString& cin,const QString& date,const float& salaire,const int& Dep);
    bool delPer(const int& id);

    bool addDep(const QString& lib,const QString& ad);
    bool modDep(const int& id,const QString& lib,const QString& ad);
    bool delDep(const int& id);

    bool addAb(const QString& date,const QString& datef,const QString& rai,const int& idp);
    bool modAb(const int& id,const QString& date,const QString& datef,const QString& rai,const int& idp);
    bool delAb(const int& id);

    bool login(const QString &logname,const QString &mdp);
private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
