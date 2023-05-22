#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>

dbmanager::dbmanager()
{
    QString dir = QDir::currentPath();
    QStringList directories = dir.split(QRegularExpression("[/\\\\]"));
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

QSqlQuery dbmanager::getPer()
{
    QSqlQuery query(db);
    query.prepare("SELECT id_P, nom, prenom, adress, cin, fonction, date_embauche, salaire, Libelle "
                  "FROM Personnel p, Departement d WHERE p.dep=d.id_Dep");
    try{
        if (!query.exec()) {
            throw query.lastError();
        }
        return query;
    }catch(QSqlError err){
        qDebug() << err.text();
        return query;
    }
}

bool dbmanager::addPer(const QString &nom, const QString &prenom, const QString &adresse, const QString &fonction, const QString &cin, const QString &date, const float &salaire, const int &Dep)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Personnel (nom,prenom,adress,cin,fonction,date_embauche,dep,salaire) VALUES(:n, :p, :a, :c, :f, :d, :de, :s)");
    query.bindValue(":n",nom);
    query.bindValue(":p",prenom);
    query.bindValue(":a",adresse);
    query.bindValue(":f",fonction);
    query.bindValue(":c",cin);
    query.bindValue(":d",date);
    query.bindValue(":s",salaire);
    query.bindValue(":de",Dep);

    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::modPer(const int &id, const QString &nom, const QString &prenom, const QString &adresse, const QString &fonction, const QString &cin, const QString &date, const float &salaire, const int &Dep)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Personnel SET nom=:n ,prenom=:p ,adress=:a ,cin=:c ,fonction=:f ,date_embauche=:d ,dep=:de ,salaire=:s WHERE id_P=:id");
    query.bindValue(":n",nom);
    query.bindValue(":p",prenom);
    query.bindValue(":a",adresse);
    query.bindValue(":f",fonction);
    query.bindValue(":c",cin);
    query.bindValue(":d",date);
    query.bindValue(":s",salaire);
    query.bindValue(":de",Dep);
    query.bindValue(":id",id);


    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::delPer(const int &id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM Personnel WHERE id_P=:id");
    query.bindValue(":id",id);

    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

QSqlQuery dbmanager::getDep()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Departement");
    try{
        if (!query.exec()) {
            throw query.lastError();
        }
        return query;
    }catch(QSqlError err){
        qDebug() << err.text();
        return query;
    }
}

bool dbmanager::addDep(const QString &lib, const QString &ad)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Departement (libelle,adresse) VALUES(:n, :p)");
    query.bindValue(":n",lib);
    query.bindValue(":p",ad);

    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::modDep(const int &id, const QString &lib, const QString &ad)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Departement SET libelle=:n ,adresse=:p WHERE id_Dep=:id");
    query.bindValue(":n",lib);
    query.bindValue(":p",ad);
    query.bindValue(":id",id);


    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::delDep(const int &id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM Departement WHERE id_Dep=:id");
    query.bindValue(":id",id);

    if(query.exec()){
        return true;
    }
    return false;
}

bool dbmanager::addAb(const QString &date, const QString &datef, const QString &rai, const int &idp)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Absence (date_absence,date_fin,raison,id_P) VALUES(:d, :f, :r, ;p)");
    query.bindValue(":d",date);
    query.bindValue(":f",datef);
    query.bindValue(":r",rai);
    query.bindValue(":p",idp);

    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::modAb(const int &id, const QString &date, const QString &datef, const QString &rai, const int &idp)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Absence SET date_absence=:d ,date_fin=:f ,raison=:r ,id_P=:p WHERE id_A=:id");
    query.bindValue(":d",date);
    query.bindValue(":f",datef);
    query.bindValue(":r",rai);
    query.bindValue(":p",idp);
    query.bindValue(":id",id);


    try{
        if(query.exec()){
            return true;
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        qDebug() << err.text();
        return false;
    }
}

bool dbmanager::delAb(const int &id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM Absence WHERE id_A=:id");
    query.bindValue(":id",id);

    if(query.exec()){
        return true;
    }
    return false;
}

bool dbmanager::login(const QString &logname, const QString &mdp)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Admin WHERE login =:log AND mdp=:mm");
    query.bindValue(":log", logname);
    query.bindValue(":mm", mdp);

    try{
        if (query.exec())
        {
            if (query.next())
            {
                db.close();
                return true;
            }else{
                throw query.lastError();
            }
        }else{
            throw query.lastError();
        }
    }catch(QSqlError err){
        if(err.text() == ""){
            qDebug() << "Invalid";
        }
    }
    return false;
}

