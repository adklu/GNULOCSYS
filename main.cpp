
#include "mainwindow.h"

#include <QApplication>
#include <QLineEdit>



#include <QtGui>
#include <QtSql>
#include <QTableWidget>
#include <QMessageBox>
#include <QFile>
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);

    MainWindow w;
    w.show();



    return app.exec();
}
