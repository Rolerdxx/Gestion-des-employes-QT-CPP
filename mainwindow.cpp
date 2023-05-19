#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(700,300);

        qDebug() << mdb.conn();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_next_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}





void MainWindow::on_login_clicked()
{
    mdb.conn();
    if(mdb.login(ui->username->text(), ui->password->text())){
        ui->stackedWidget->setCurrentIndex(1);
        setFixedSize(900,400);
    }
    mdb.disc();
}

