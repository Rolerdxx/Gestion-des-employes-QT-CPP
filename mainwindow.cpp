#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(700,300);
    this->setStyleSheet("QMainWindow {background-image: url(./images/1.png);}");
    perRef();
    defRef();
    depRef();
    abRef();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::perRef()
{
    mdb.conn();
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
    mdb.disc();

//    for(int i=0; i<ui->tableWidget->rowCount(); ++i){
//        ui->tableWidget->removeRow(i);
//    }
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
}

void MainWindow::defRef()
{
    mdb.conn();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT Libelle FROM Departement");
    ui->depa->setModel(model);
    mdb.disc();
}

void MainWindow::depRef()
{
    mdb.conn();
    QSqlQuery query = mdb.getDep();
    while (query.next()) {
        Departement departement;
        departement.id = query.value("id_Dep").toInt();
        departement.libelle = query.value("libelle").toString();
        departement.adresse = query.value("adresse").toString();
        departementData.push_back(departement);
    }
    for (long long unsigned int row = 0; row < departementData.size(); ++row) {
        const Departement& departement = departementData[row];
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(departement.id)));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(departement.libelle));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(departement.adresse));
    }
    mdb.disc();
//    mdb.conn();
//    QSqlQueryModel *model = new QSqlQueryModel;
//    model->setQuery("select * from Departement");
//    ui->tableView_5->setModel(model);
//    mdb.disc();
}

void MainWindow::abRef()
{
    mdb.conn();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from Absence");
    ui->tableView_2->setModel(model);
    mdb.disc();
}



void MainWindow::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}





void MainWindow::on_login_clicked()
{
    mdb.conn();
    if(mdb.login(ui->username->text(), ui->password->text())){
        this->setStyleSheet("QMainWindow {background-image: url(./images/3.png);}");
        ui->stackedWidget->setCurrentIndex(1);
        setFixedSize(900,386);
    }
    mdb.disc();
}




void MainWindow::on_peromenu_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/2.png);}");
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_back1_btn_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/3.png);}");
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_Ajouter_btn_clicked()
{
    mdb.conn();
    if(mdb.addPer(ui->Nom_edit->text(),ui->Prenom_edit->text(),ui->Adr_edit->text(),ui->Fct_edit->text(),ui->Cin_edit->text(),ui->dateEdit->text(),ui->Nom_edit->text().toFloat(),ui->depa->currentIndex()+1)){
        qDebug() << "yay";
        perRef();
    }
    mdb.disc();
}


void MainWindow::on_Modifier_btn_clicked()
{
    mdb.conn();
    if(mdb.modPer(selected,ui->Nom_edit->text(),ui->Prenom_edit->text(),ui->Adr_edit->text(),ui->Fct_edit->text(),ui->Cin_edit->text(),ui->dateEdit->text(),ui->Salaire_edit_3->text().toFloat(),ui->depa->currentIndex()+1)){
        qDebug() << "yay mod";
        perRef();
    }
    mdb.disc();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
//    selected = ui->tableView->model()->index(index.row(),0).data().toString().toInt();
//    ui->Nom_edit->setText(ui->tableView->model()->index(index.row(),1).data().toString());
//    ui->Prenom_edit->setText(ui->tableView->model()->index(index.row(),2).data().toString());
//    ui->Adr_edit->setText(ui->tableView->model()->index(index.row(),3).data().toString());
//    ui->Cin_edit->setText(ui->tableView->model()->index(index.row(),4).data().toString());
//    ui->Fct_edit->setText(ui->tableView->model()->index(index.row(),5).data().toString());
//    ui->dateEdit->setText(ui->tableView->model()->index(index.row(),7).data().toString());
//    ui->Salaire_edit_3->setText(ui->tableView->model()->index(index.row(),6).data().toString());

//    for (int var = 0; var < ui->depa->count(); ++var) {
//        ui->depa->setCurrentIndex(var);
//        if(ui->depa->currentText()==ui->tableView->model()->index(index.row(),7).data().toString()){
//            break;
//        }
//    }
}


void MainWindow::on_Supp_btn_clicked()
{
    if(selected!=0){
        mdb.conn();
        if(mdb.delPer(selected)){
            perRef();
        }
        mdb.disc();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/4.png);}");
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_3_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/5.png);}");
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_Ajouter_btn_5_clicked()
{
    mdb.conn();
    if(mdb.addDep(ui->libelle_edit->text(),ui->Adress_dep_edit->text())){
        depRef();
    }
    mdb.disc();
}


void MainWindow::on_Modifier_btn_5_clicked()
{
    mdb.conn();
    if(mdb.modDep(selecteddep,ui->libelle_edit->text(),ui->Adress_dep_edit->text())){
        depRef();
    }
    mdb.disc();
}


void MainWindow::on_tableView_5_clicked(const QModelIndex &index)
{
//    selecteddep = ui->tableView_5->model()->index(index.row(),0).data().toString().toInt();
//    ui->libelle_edit->setText(ui->tableView_5->model()->index(index.row(),1).data().toString());
//    ui->Adress_dep_edit->setText(ui->tableView_5->model()->index(index.row(),2).data().toString());
}


void MainWindow::on_Supp_btn_5_clicked()
{
    if(selecteddep!=0){
        mdb.conn();
        if(mdb.delDep(selecteddep)){
            depRef();
        }
        mdb.disc();
    }
}


void MainWindow::on_Ajouter_btn_2_clicked()
{
    mdb.conn();
    if(mdb.addAb(ui->start->text(),ui->end->text(),ui->Raison_edit->text(),ui->perso_edit->text().toInt())){
        abRef();
    }
    mdb.disc();
}


void MainWindow::on_back2_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/3.png);}");
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_back3_clicked()
{
    this->setStyleSheet("QMainWindow {background-image: url(./images/3.png);}");
    ui->stackedWidget->setCurrentIndex(1);
}


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


void MainWindow::on_Modifier_btn_2_clicked()
{
    mdb.conn();
    if(mdb.modAb(selectedAb,ui->start->text(),ui->end->text(),ui->Raison_edit->text(),ui->perso_edit->text().toInt())){
        abRef();
    }
    mdb.disc();
}


void MainWindow::on_Supp_btn_2_clicked()
{
    mdb.conn();
    if(mdb.delAb(selectedAb)){
        abRef();
    }
    mdb.disc();
}


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
        qDebug() << selected;
}

