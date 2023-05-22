#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Departement {
    int id;
    QString libelle;
    QString adresse;
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void perRef();
    void defRef();

    void depRef();

    void abRef();

private slots:
    void on_next_clicked();

    void on_login_clicked();

    void on_peromenu_clicked();

    void on_back1_btn_clicked();

    void on_Ajouter_btn_clicked();

    void on_Modifier_btn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Supp_btn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_Ajouter_btn_5_clicked();

    void on_Modifier_btn_5_clicked();

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_Supp_btn_5_clicked();

    void on_Ajouter_btn_2_clicked();

    void on_back2_clicked();

    void on_back3_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_Modifier_btn_2_clicked();

    void on_Supp_btn_2_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    dbmanager mdb;
    std::map<int, std::map<QString, QVariant>> personnelData;
    std::vector<Departement> departementData;
    int selected=0;
    int selecteddep=0;
    int selectedAb=0;
};

#endif // MAINWINDOW_H
