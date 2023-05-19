#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>

dbmanager::dbmanager()
{
    QString dir = QDir::currentPath();
    QRegularExpression separatorRegex("[/\\\\]");
    QStringList directories = dir.split(separatorRegex);
    if (directories.size() > 1) {
        directories.removeLast();
        dir = directories.join("/")+"/Gestion-des-employes-QT-CPP/gedb.db";
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir);
}

bool dbmanager::conn()
{
    return db.open();
}

void dbmanager::disc()
{
    db.close();
}

bool dbmanager::login(const QString &logname, const QString &mdp)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Admin WHERE login =:log AND mdp=:mm");
    query.bindValue(":log", logname);
    query.bindValue(":mm", mdp);
    qDebug() << logname << mdp;

    if (query.exec())
    {
        qDebug() << "wsad";
        if (query.next())
        {
            qDebug() << "Kayn";
            db.close();
            return true;
        }
    }else{
        qDebug() << query.lastError().text();
    }
    return false;
}

