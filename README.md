# Gestion-des-employes-QT-CPP

# Partie codage

## Login

login fonction

```cpp
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
```

## Personnel Management

Getting data from the database
used try catch throw

```cpp
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
```

declaring map

```cpp
std::map<int, std::map<QString, QVariant>> personnelData;
```

filling map

```cpp
QSqlQuery query = mdb.getPer();
    while (query.next()) {
        int id = query.value(0).toInt();
        std::map<QString, QVariant> data;
        data["nom"] = query.value(1).toString();
        data["prenom"] = query.value(2).toString();
        data["adress"] = query.value(3).toString();
        data["cin"] = query.value(4).toString();
        data["fonction"] = query.value(5).toInt();
        data["date_embauche"] = query.value(6).toDate();
        data["salaire"] = query.value(7).toDouble();
        data["Departement"] = query.value(8).toString();
        personnelData[id] = data;
    }
```

displaying data from map to tablewidget

```cpp
ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    int row = 0;
    for (const auto& entry : personnelData) {
        int id = entry.first;
        const std::map<QString, QVariant>& data = entry.second;

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(data.at("nom").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(data.at("prenom").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(data.at("adress").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(data.at("cin").toString()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(data.at("fonction").toString()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(data.at("date_embauche").toDate().toString("M/d/yyyy"))); // Date d'embauche
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(data.at("salaire").toString()));
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(data.at("Departement").toString()));

        row++;
    }
    ui->tableWidget->resizeColumnsToContents();
```

adding user

```cpp
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
```


modifying Personnel

```cpp
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
```


deleting Personnel

```cpp
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
```

when user clicks on table the fields fill automaticly

```cpp
void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
        selected = ui->tableWidget->model()->index(index.row(),0).data().toString().toInt();
        ui->Nom_edit->setText(ui->tableWidget->model()->index(index.row(),1).data().toString());
        ui->Prenom_edit->setText(ui->tableWidget->model()->index(index.row(),2).data().toString());
        ui->Adr_edit->setText(ui->tableWidget->model()->index(index.row(),3).data().toString());
        ui->Cin_edit->setText(ui->tableWidget->model()->index(index.row(),4).data().toString());
        ui->Fct_edit->setText(ui->tableWidget->model()->index(index.row(),5).data().toString());
        ui->dateEdit->setText(ui->tableWidget->model()->index(index.row(),6).data().toString());
        ui->Salaire_edit_3->setText(ui->tableWidget->model()->index(index.row(),7).data().toString());
}
```

## Departement Managemant

declaring vector with a `Departement` type

```cpp
struct Departement {
    int id;
    QString libelle;
    QString adresse;
};
std::vector<Departement> departementData;
```


filling the vector from database

```cpp
QSqlQuery query = mdb.getDep();
    while (query.next()) {
        Departement departement;
        departement.id = query.value("id_Dep").toInt();
        departement.libelle = query.value("libelle").toString();
        departement.adresse = query.value("adresse").toString();
        departementData.push_back(departement);
    }
```


filling tablewidget with data from the vector


```cpp
for (long long unsigned int row = 0; row < departementData.size(); ++row) {
        const Departement& departement = departementData[row];
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(departement.id)));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(departement.libelle));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(departement.adresse));
    }
```


## Absence Management

displaying data directly from the database

```cpp
QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from Absence");
    ui->tableView_2->setModel(model);
```

filling the fields when the user clicks on a row

```cpp
void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QString time_format = "M/d/yyyy h:mm AP";
    QDateTime b = QDateTime::fromString(ui->tableView_2->model()->index(index.row(),1).data().toString(), time_format);
    QDateTime c = QDateTime::fromString(ui->tableView_2->model()->index(index.row(),2).data().toString(), time_format);
    selectedAb = ui->tableView_2->model()->index(index.row(),0).data().toString().toInt();
    ui->start->setDateTime(b);
    ui->end->setDateTime(c);
    ui->Raison_edit->setText(ui->tableView_2->model()->index(index.row(),3).data().toString());
    ui->perso_edit->setText(ui->tableView_2->model()->index(index.row(),4).data().toString());
}
```


