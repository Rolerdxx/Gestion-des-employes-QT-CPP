#include "mainwindow.h"

#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile st("C:/Users/azbil/Desktop/Gestion-des-employes-QT-CPP/Gestion-des-employes-QT-CPP/styles/QSS/ElegantDark.qss");
    st.open(QFile::ReadOnly);
    QString style = QLatin1String(st.readAll());
    a.setStyleSheet(style);
    MainWindow w;
    w.show();
    return a.exec();
}
