#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "gclist.h"
//#include "gc.h"
//#include "tabelslot.h"
//#include "gcmatchcase.h"
//#include "gcreduct.h"
//#include "showglossary.h"
//#include "redwbound.h"
//#include "fulltable.h"

#include "common.h"

#include <QMessageBox>
#include <QFileDialog>

#include <QDebug>
#include <QLineEdit>
#include <QFile>

#include <QApplication>
#include <QLineEdit>

#include <QtGui>
#include <QtSql>
#include <QTableWidget>
#include <QCompleter>
#include <QRegExp>


//extern QString datab;

//QString Common::datab;

QString datab;
QString globalchange;
//int nz=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{


    ui->setupUi(this);

    //ui->subwindow_2->setWindowIcon( QIcon(QPixmap(1,1)) );
     setWindowIcon( QIcon(QPixmap(1,1)) );

    //connect(ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadpressed()));
    //connect(ui->connectButton,SIGNAL(pressed()),this,SLOT(connectpressed()));
    //connect(ui->showtableButton,SIGNAL(pressed()),this,SLOT(showtable()));



}


 void MainWindow::slotfontsize()
 {


     ui->ref1TextEdit->zoomIn(2);
     ui->TextEdit->zoomIn(2);
     ui->RefTextEdit->zoomIn(2);
     ui->TextEditStat->zoomIn(2);
     ui->TextEditCom->zoomIn(2);
     ui->TextEditHis->zoomIn(2);

 }


 void MainWindow::slotfontsizeMin()
 {


     ui->ref1TextEdit->zoomOut(2);
     ui->TextEdit->zoomOut(2);
     ui->RefTextEdit->zoomOut(2);
     ui->TextEditStat->zoomOut(2);
     ui->TextEditCom->zoomOut(2);
     ui->TextEditHis->zoomOut(2);

 }




int ml = 0;
void MainWindow::loadpressed()
{


    //while (ml<1){
    //qDebug() << "load button works";


    QFile hfile("hfile.txt");
    if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&hfile);
    while (!in.atEnd()) {
        QString hostr = in.readLine();
        //qDebug() << hostr;
        if(~(hostr.isEmpty())){
        ui->hostqle->setText(hostr);}
                }


    QFile prtfile("prtfile.txt");
    if (!prtfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inprt(&prtfile);
    while (!inprt.atEnd()) {
        QString portr = inprt.readLine();
        //qDebug() << hostr;
        if(~(portr.isEmpty())){
        ui->portqle->setText(portr);}
                }



    QFile dfile("dfile.txt");
    if (!dfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inda(&dfile);
    while (!inda.atEnd()) {
        QString databr = inda.readLine();
        //qDebug() << databr;
        if(~(databr.isEmpty())){
        ui->databaseqle->setText(databr);}
                        }


    QFile ufile("ufile.txt");
    if (!ufile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inus(&ufile);
    while (!inus.atEnd()) {
        QString usernmr = inus.readLine();
        //qDebug() << usernmr;
        if(~(usernmr.isEmpty())){
        ui->userqle->setText(usernmr);}
                        }

    /*QFile pfile("pfile.txt");
    if (!pfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inpa(&pfile);
    while (!inpa.atEnd()) {
        QString passwr = inpa.readLine();
        //qDebug() << passwr;
        if(~(passwr.isEmpty())){
        ui->passwordqle->setText(passwr);}
                        }*/

       //ml++;    }

}


int n=0;


void MainWindow::connectpressed()
{


    QString usernm = ui->userqle->text();
    //qDebug() << usernm;

    QString passw = ui->passwordqle->text();
    //qDebug() << passw;

    QString host = ui->hostqle->text();
    //qDebug() << host;


    QString portvs = ui->portqle->text();
    int portv = portvs.toInt();


    datab = ui->databaseqle->text();
    //qDebug() << datab;




    if(((usernm.trimmed().isEmpty())) | (passw.trimmed().isEmpty()) | (host.trimmed().isEmpty()) | (portvs.trimmed().isEmpty()) | (datab.trimmed().isEmpty()))
        {

    ui->status->setText("Not connected to database");

    //while (n<1)                {
    QMessageBox msgBox;
    msgBox.setText("Please enter the connection data.");
    msgBox.exec();
            //n++;                }

           }

    else
        {


       QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
       //db.setHostName("127.0.0.1");
       db.setHostName(host);
       db.setPort(portv);
       //db.setPort(3306);
       db.setDatabaseName(datab);
       //db.setDatabaseName("StringDB");
       db.setUserName(usernm);
       //db.setUserName("root");
       //db.setPassword("");
       db.setPassword(passw);


       if (!db.open())
       {
         QMessageBox::critical(0, QObject::tr("Database Error"),
                   db.lastError().text());

        ui->status->setText("Not connected to database");

        QString refstat = ui->status->text();

        ui->statusBar->showMessage(refstat);



           }

       else
                {
       ui->status->setText("Connected to database");

       QString refstatt = ui->status->text();

       ui->statusBar->showMessage(refstatt);






       QFile hfile("hfile.txt");
        if (!hfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream outh(&hfile);
        outh << host;

        //out << host << "\n";


        QFile prtfile("prtfile.txt");
         if (!prtfile.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

         QTextStream outprt(&prtfile);
         outprt << portv;


        QFile dfile("dfile.txt");
         if (!dfile.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

         QTextStream outd(&dfile);
         outd << datab;


         QFile ufile("ufile.txt");
          if (!ufile.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outu(&ufile);
          outu << usernm;


          /*QFile pfile("pfile.txt");
           if (!pfile.open(QIODevice::WriteOnly | QIODevice::Text))
               return;

           QTextStream outp(&pfile);
           outp << passw;*/



           ui->userqle->setReadOnly(true);
           ui->passwordqle->setReadOnly(true);
           ui->hostqle->setReadOnly(true);
           ui->portqle->setReadOnly(true);
           ui->databaseqle->setReadOnly(true);




            }

        }

}


//++++++++++++++++++++++++++++++++
//++++++TAB TABLES++++++++++++++++
//++++++++++++++++++++++++++++++++

/*
    - show all tables of database, select table(s), assign tables as Glossary-Table or as String-Table,
    - show content of selected tables

 */

void MainWindow::synctablesslot()

{

    //select tables
    //++++++++++++



    QString keepselect = ui->comboBoxtables->currentText();
    ui->comboBoxtables->clear();

    QString keepselectrt = ui->comboBoxRenameT->currentText();
    ui->comboBoxRenameT->clear();

    //QString keepselectg = ui->comboBoxTableG->currentText();
    //ui->comboBoxTableG->clear();

    //QString keepselecti = ui->comboBoximpdb->currentText();
    //ui->comboBoximpdb->clear();





    QSqlQuery querytables("SHOW TABLES");



    QList<QString> tablsAr;
    //qDeleteAll(tablsAr.begin(), tablsAr.end());

   /* int index=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();

        if(tablsAr.contains(tabls))
                {
        tablsAr.removeAll(tabls);
        qDebug() << tablsAr;
                }



        //qDebug() << col;
      index++;

    }*/



    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);

        //qDebug() << tabls;

        //qDebug() << col;
      indexts++;

    }


    //qDebug() << tablsAr;

    //for admin db tab
    //ui->comboBoxRenameT->clear();
    ui->comboBoxRenameT->addItems(tablsAr);
    //ui->comboBoxRenameT->setCurrentIndex(0);
    int indexrt = ui->comboBoxRenameT->findText(keepselectrt);
    ui->comboBoxRenameT->setCurrentIndex(indexrt);

    ui->comboBoxtables->addItems(tablsAr);
    int index = ui->comboBoxtables->findText(keepselect);
    ui->comboBoxtables->setCurrentIndex(index);

    //ui->comboBoxTableG->addItems(tablsAr);
    //int indexg = ui->comboBoxTableG->findText(keepselectg);
    //ui->comboBoxTableG->setCurrentIndex(indexg);

   // ui->comboBoximpdb->addItems(tablsAr);
    //int indexi = ui->comboBoximpdb->findText(keepselecti);
   // ui->comboBoximpdb->setCurrentIndex(indexi);

    QCompleter *completer = new QCompleter(tablsAr, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setModel(new completionModel(completer));
    ui->comboBoxtables->setCompleter(completer);
    //ui->comboBoxtables->setDuplicatesEnabled(FALSE);
    ui->comboBoxRenameT->setCompleter(completer);
    //ui->comboBoxTableG->setCompleter(completer);
   // ui->comboBoximpdb->setCompleter(completer);



    QString cbt = ui->comboBoxtables->currentText();

    //qDebug() << cbt;



}

void MainWindow::synctableimpdb()

{


    QString keepselecti = ui->comboBoximpdb->currentText();
    ui->comboBoximpdb->clear();





    QSqlQuery querytables("SHOW TABLES");



    QList<QString> tablsAr;




    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);

        //qDebug() << tabls;

        //qDebug() << col;
      indexts++;

    }


    //qDebug() << tablsAr;




    ui->comboBoximpdb->addItems(tablsAr);
    int indexi = ui->comboBoximpdb->findText(keepselecti);
    ui->comboBoximpdb->setCurrentIndex(indexi);

    QCompleter *completer = new QCompleter(tablsAr, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setModel(new completionModel(completer));

    //ui->comboBoxTableG->setCompleter(completer);
    ui->comboBoximpdb->setCompleter(completer);





}


//sync for tableG
void MainWindow::synctableGslot()

{




    QString keepselectg = ui->comboBoxTableG->currentText();
    ui->comboBoxTableG->clear();






    QSqlQuery querytables("SHOW TABLES");



    QList<QString> tablsAr;



    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);

        //qDebug() << tabls;

        //qDebug() << col;
      indexts++;

    }


    //qDebug() << tablsAr;



    ui->comboBoxTableG->addItems(tablsAr);
    int indexg = ui->comboBoxTableG->findText(keepselectg);
    ui->comboBoxTableG->setCurrentIndex(indexg);



    QCompleter *completer = new QCompleter(tablsAr, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setModel(new completionModel(completer));

    ui->comboBoxTableG->setCompleter(completer);








}



void MainWindow::showtable()

{

    QTableWidget* tablelist = new QTableWidget();
    tablelist->setWindowTitle("List of all tables of the connected database");

    QSqlQuery querytables("SHOW TABLES");


    tablelist->setColumnCount(querytables.record().count());
    tablelist->setRowCount(querytables.size());


    //QList<QString> tablsAr;



    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
    tablelist->setItem(indexts,0,new QTableWidgetItem(querytables.value(0).toString()));


        /*QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);
        //qDebug() << col;*/


      indexts++;
    }


    tablelist->show();


   /* ui->comboBoxtables->addItems(tablsAr);

    QCompleter *completer = new QCompleter(tablsAr, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setModel(new completionModel(completer));
    ui->comboBoxtables->setCompleter(completer);
    //ui->comboBoxtables->setDuplicatesEnabled(FALSE);



    QString cbt = ui->comboBoxtables->currentText();

    qDebug() << cbt;*/


 }




void MainWindow::tableS()

{
    if (     (ui->checkBoxFilter->isChecked()))
       {
           (ui->checkBoxFilter->setChecked(false));
         }

    if (     (ui->checkBoxFilterG->isChecked()))
       {
           (ui->checkBoxFilterG->setChecked(false));
         }

    if (     (ui->checkBoxFilterkeepEQ->isChecked()))
       {
           (ui->checkBoxFilterkeepEQ->setChecked(false));
         }




    ui->tableAll->clearContents();

    // QString tablenameS = ui->tableSEdit->text();
    QString tablenameS = ui->comboBoxtables->currentText();



    if(tablenameS.trimmed().isEmpty())
                {
    QMessageBox msgBox;
    msgBox.setText("Please select a table.");
    msgBox.exec();
                 }

    else
        {

          //qDebug() << datab;
        QFile t1file("t1file.txt");
         if (!t1file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

         QTextStream outh(&t1file);
         outh << tablenameS;



   //+++++++++++++++    fulltable();

        ui->deft1->setText(tablenameS);

        //QTableWidget* tableAll = new QTableWidget();
        ui->tableAll->setWindowTitle(tablenameS);



        //QSqlQuery query("SELECT * FROM StringDB.StringsIII");
        //QSqlQuery query("SELECT * FROM StringsIII");

        QString strtable = "SELECT * FROM " + tablenameS;

        //qDebug() << strtable;

        QSqlQuery query(strtable);



        ui->tableAll->setColumnCount(query.record().count());
        ui->tableAll->setRowCount(query.size());


        QString colnames = "SHOW COLUMNS FROM " + tablenameS;
        //qDebug() << colnames;

        QSqlQuery querycol(colnames);

        QList<QString> colAr;

        int ncol=0;
        while (querycol.next())
            {
            QString col;
            col = querycol.value(0).toString();
            colAr.append(col);
            ncol++;
            //qDebug() << ncol;
              }

        //qDebug() << colAr;

        /*int colcount = 0;
        while (colcount < querycol.size())
                     {

                       QString colE;
                       colE=colAr[colcount];
                        qDebug() <<  colE;
                        colcount++;

                    }*/


        //QStringList TableHeader;
        //TableHeader<<"ID"<<"Source"<<"Current Translation";
        //tableAll->setHorizontalHeaderLabels(TableHeader);
        ui->tableAll->setHorizontalHeaderLabels(colAr);




        //QString textData;


        int index=0;
        while (query.next())
        {

            for (int coldisp = 0; coldisp < ncol; coldisp++)
            {
              //ui->tableAll->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
                //ui->tableAll->setItem(index,coldisp,new QTableWidgetItem(query.value(coldisp).toString()));

                QTableWidgetItem *item;

                //item = new QTableWidgetItem(query.value(coldisp).toString());

                QString foritem = query.value(coldisp).toString();
                QString su = foritem.left(500);
                //qDebug() <<  su;
                item = new QTableWidgetItem(su);

                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->tableAll->setItem(index,coldisp,item);

               }
        //s2.replace('"',"\"");
        //+++limit to |
        /*QString s;
        s = query.value(0).toString();
        textData+='|';
        textData+=s;
        textData+='|';
        textData += ",";
        textData += ",";*/

        //

        //ui->tableAll->setItem(index,1,new QTableWidgetItem(query.value(1).toString()));

        /*QTableWidgetItem *item;
        item = new QTableWidgetItem(query.value(1).toString());
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->tableAll->setItem(index,1,item);


        QString s1;
        s1 = query.value(1).toString();
        textData+='|';
        textData+=s1;
        textData+='|';
        textData += ",";
        textData += ",";*/

        //

        //ui->tableAll->setItem(index,2,new QTableWidgetItem(query.value(2).toString()));

        /*QTableWidgetItem *item2;
        item2 = new QTableWidgetItem(query.value(2).toString());
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        ui->tableAll->setItem(index,2,item2);
        */
        /*QString s2;
        s2 = query.value(2).toString();
        textData+='|';
        textData+=s2;
        textData+='|';
        textData += ",";
        textData += "\n";*/

        /*ui->tableAll->setItem(index,3,new QTableWidgetItem(query.value(3).toString()));

        QTableWidgetItem *item3;
        item3 = new QTableWidgetItem(query.value(3).toString());
        item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
        ui->tableAll->setItem(index,3,item3);
        */





        index++;
        }


        //


/*
         item = new QTableWidgetItem("non Selectable");
         item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
         ui->tableAll->setItem((0,1,item);*/


        //




        //show full table
        ui->tableAll->show();

        ui->tableAll->setUpdatesEnabled( true ) ;

        //use this
        //connect(ui->tableAll, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemChanged(const QModelIndex &)));


        connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));

         //connect(ui->tableAll, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemChanged(int,int)));




        //connect(ui->tableAll, SIGNAL(clicked(const QModelIndex &)), this, SLOT(itemRef(const QModelIndex &)));

        //connect(ui->tableAll, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(itemRef(const QPoint&)));

        //qDebug() << tableAll->item(0, 2)->text();


        //


        /*QFile csvFile(tablenameS + ".csv");
        if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
            QTextStream out(&csvFile);
            out << textData;
            csvFile.close();
             }*/


        //--------------------------------------------------
        //set col selection drop down menu for admin edit
        /*QString keepselect = ui->comboBoxCol->currentText();
        ui->comboBoxCol->clear();
        ui->comboBoxCol->addItems(colAr);
        int indexco = ui->comboBoxCol->findText(keepselect);
        ui->comboBoxCol->setCurrentIndex(indexco);

        QCompleter *completerc = new QCompleter(colAr, this);
        completerc->setCaseSensitivity(Qt::CaseInsensitive);
        ui->comboBoxCol->setCompleter(completerc);
        QString cbtcol = ui->comboBoxCol->currentText();
                qDebug() << cbtcol;*/




        //+++++++++++++++++++++++++++++end


        }

}
//+++++++++++++++++++++++++end of table S
//++++++++++++++++++++++++++++++++++++++++++++++

void MainWindow::historyslot()

{


    //popup for legal
    //QString cellTextID = ui->tableAll->item(nrow, 0)->text();
    //int indxid = ui->comboBoxHis->currentIndex();



    QString cellTextID = ui->idforedit->text();


    QString tablenameS = ui->comboBoxtables->currentText();
    //QString tsedit = "SELECT * FROM " + tablenameS + " WHERE SID = '" + cellTextID + "'";
    QString cbID = ui->comboBoxID->currentText();
    QString tsedit = "SELECT * FROM " + tablenameS + " WHERE " + cbID + " = '" + cellTextID + "'";

    //qDebug() << tsedit;

    //qDebug() << strtable;

    QSqlQuery querytse(tsedit);


    // qDebug() << tse = querytse.value.toString();


    int indexqu=0;
    while (querytse.next())
    {
    int indxhisp = ui->comboBoxES->currentIndex();
    int indxhis = indxhisp-1;

    QString hise;
    //ide = querytse.value(0).toString();
    hise = querytse.value(indxhis).toString();

    //ui->idforedit->setText(ide);

    QTextEdit* textEdit = new QTextEdit();
    textEdit->setText(hise);
    textEdit->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget( textEdit );

    QWidget *nw = new QWidget();
    nw->setLayout( layout );

    nw->show();





    indexqu++;
       }



}





//++++++++++++++edit settings
void MainWindow::idslot()

{
    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
          //colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



          ui->comboBoxID->clear();
          //colAr.append("-");
          ui->comboBoxID->addItems(colAr);
           ui->comboBoxID->setCurrentIndex(0);

          QFile hfile(tablenameS + "comboBoxID");
          if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
          QTextStream in(&hfile);
          while (!in.atEnd())

                              {
              QString keepselectID = in.readLine();
              //qDebug() << keepselectID;


              if(keepselectID=="")
              {
              ui->comboBoxID->setCurrentIndex(0);
              }
              else
              {
                  int indexID = ui->comboBoxID->findText(keepselectID);
                  ui->comboBoxID->setCurrentIndex(indexID);
              }

                               }

           //QString keepselectID = ui->comboBoxID->currentText();

          //QString cbID = ui->comboBoxID->currentText();
          //QString cbES = ui->comboBoxES->currentText();
          //QString cbTS = ui->comboBoxTS->currentText();
          //QString cbNTS = ui->comboBoxNTS->currentText();
          //QString cbStat = ui->comboBoxStat->currentText();
          //QString cbCom = ui->comboBoxIDCom->currentText();

           //qDebug() << cbID;

          //int indxid = ui->comboBoxID->currentIndex();
          //qDebug() << indxid;


}

void MainWindow::esslot()

{
    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
          colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }





    ui->comboBoxES->clear();
    //colAr.append("-");
    ui->comboBoxES->addItems(colAr);
      ui->comboBoxES->setCurrentIndex(2);


    QFile hesfile(tablenameS + "comboBoxES");
    if (!hesfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream ines(&hesfile);
    while (!ines.atEnd())
                        {
        QString keepselectES = ines.readLine();
        //qDebug() << keepselectID;
        if(~(keepselectES.isEmpty()))
        {
        int indexES = ui->comboBoxES->findText(keepselectES);
        ui->comboBoxES->setCurrentIndex(indexES);
        }
        else
        {
         ui->comboBoxES->setCurrentIndex(2);
        }
                         }




}



void MainWindow::tsslot()

{

    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
          colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



        ui->comboBoxTS->clear();
        //colAr.append("-");
        ui->comboBoxTS->addItems(colAr);
        ui->comboBoxTS->setCurrentIndex(3);



        QFile htsfile(tablenameS + "comboBoxTS");
        if (!htsfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream ints(&htsfile);
        while (!ints.atEnd())
                            {
            QString keepselectTS = ints.readLine();
            //qDebug() << keepselectID;
            if(~(keepselectTS.isEmpty()))
            {
                ui->comboBoxTS->clear();
                //colAr.append("-");
                ui->comboBoxTS->addItems(colAr);
            int indexTS = ui->comboBoxTS->findText(keepselectTS);
            ui->comboBoxTS->setCurrentIndex(indexTS);
            }

                             }

}


void MainWindow::ntsslot()

{

    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
          colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



        ui->comboBoxNTS->clear();
        //colAr.append("-");
        ui->comboBoxNTS->addItems(colAr);
        ui->comboBoxNTS->setCurrentIndex(0);



        QFile hNtsfile(tablenameS + "comboBoxNTS");
        if (!hNtsfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream inNts(&hNtsfile);
        while (!inNts.atEnd())
                            {
            QString keepselectNTS = inNts.readLine();
            //qDebug() << keepselectID;
            if(~(keepselectNTS.isEmpty()))
            {
                ui->comboBoxNTS->clear();
                //colAr.append("-");
                ui->comboBoxNTS->addItems(colAr);
            int indexNTS = ui->comboBoxNTS->findText(keepselectNTS);
            ui->comboBoxNTS->setCurrentIndex(indexNTS);
            }

                             }

}

//--------com and stat slot
void MainWindow::statboxslot()

{

    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
          colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



        ui->comboBoxStat->clear();
        //colAr.append("-");
        ui->comboBoxStat->addItems(colAr);
        ui->comboBoxStat->setCurrentIndex(0);



        QFile hstatfile(tablenameS + "comboBoxStat");
        if (!hstatfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream instat(&hstatfile);
        while (!instat.atEnd())
                            {
            QString keepselectstat = instat.readLine();
            //qDebug() << keepselectID;
            if(~(keepselectstat.isEmpty()))
            {
                ui->comboBoxStat->clear();
                //colAr.append("-");
                ui->comboBoxStat->addItems(colAr);
            int indexstat = ui->comboBoxStat->findText(keepselectstat);
            ui->comboBoxStat->setCurrentIndex(indexstat);
            }

                             }

}

//-----------------

void MainWindow::comboxslot()

{

    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
           colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



        ui->comboBoxCom->clear();
        //colAr.append("-");
        ui->comboBoxCom->addItems(colAr);
        ui->comboBoxCom->setCurrentIndex(0);



        QFile hcomfile(tablenameS + "comboBoxCom");
        if (!hcomfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream incom(&hcomfile);
        while (!incom.atEnd())
                            {
            QString keepselectcom = incom.readLine();
            //qDebug() << keepselectID;
            if(~(keepselectcom.isEmpty()))
            {
                ui->comboBoxCom->clear();
                //colAr.append("-");
                ui->comboBoxCom->addItems(colAr);
            int indexcom = ui->comboBoxCom->findText(keepselectcom);
            ui->comboBoxCom->setCurrentIndex(indexcom);
            }

                             }

}

//------end--com and stat slot

void MainWindow::hisboxslot()

//-------------------

{

    QString tablenameS = ui->comboBoxtables->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameS;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;
           colAr.append("-");

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }



        ui->comboBoxHis->clear();
        //colAr.append("-");
        ui->comboBoxHis->addItems(colAr);
        ui->comboBoxHis->setCurrentIndex(0);



        QFile hhisfile(tablenameS + "comboBoxHis");
        if (!hhisfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream inhis(&hhisfile);
        while (!inhis.atEnd())
                            {
            QString keepselecthis = inhis.readLine();
            //qDebug() << keepselectID;
            if(~(keepselecthis.isEmpty()))
            {
                ui->comboBoxHis->clear();
                //colAr.append("-");
                ui->comboBoxHis->addItems(colAr);
            int indexhis = ui->comboBoxHis->findText(keepselecthis);
            ui->comboBoxHis->setCurrentIndex(indexhis);
            }

                             }

}





//----------------------
//++++++++++++++++++++SAVESLOTS++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++

void MainWindow::savecolslot()

{


QString tablenameS = ui->comboBoxtables->currentText();

//save ID settings
QString cbID = ui->comboBoxID->currentText();
//qDebug() << cbID;
QFile cbIDfile(tablenameS + "comboBoxID");
       if (!cbIDfile.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

       QTextStream outg(&cbIDfile);
       outg << cbID;

          cbIDfile.close();


}

//ES
void MainWindow::saveesslot()

{
QString tablenameS = ui->comboBoxtables->currentText();

 QString cbES = ui->comboBoxES->currentText();
 //qDebug() << cbID;
 QFile cbESfile(tablenameS + "comboBoxES");
      if (!cbESfile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream outges(&cbESfile);
      outges << cbES;

         cbESfile.close();

}


//TS
void MainWindow::savetsslot()

{
QString tablenameS = ui->comboBoxtables->currentText();

 QString cbTS = ui->comboBoxTS->currentText();
 //qDebug() << cbID;
 QFile cbTSfile(tablenameS + "comboBoxTS");
      if (!cbTSfile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream outgNts(&cbTSfile);
      outgNts << cbTS;

         cbTSfile.close();
}


 //NTS
void MainWindow::saventsslot()

{
QString tablenameS = ui->comboBoxtables->currentText();

 QString cbNTS = ui->comboBoxNTS->currentText();
 //qDebug() << cbID;
 QFile cbNTSfile(tablenameS + "comboBoxNTS");
      if (!cbNTSfile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream outgNts(&cbNTSfile);
      outgNts << cbNTS;

         cbNTSfile.close();

}


void MainWindow::savehisslot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString cbhis = ui->comboBoxHis->currentText();
     //qDebug() << cbID;
     QFile cbhisfile(tablenameS + "comboBoxHis");
          if (!cbhisfile.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outghis(&cbhisfile);
          outghis << cbhis;

             cbhisfile.close();


}

void MainWindow::savestatslot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString cbstat = ui->comboBoxStat->currentText();
     //qDebug() << cbID;
     QFile cbstatfile(tablenameS + "comboBoxStat");
          if (!cbstatfile.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outgstat(&cbstatfile);
          outgstat << cbstat;

             cbstatfile.close();


}


void MainWindow::savecomslot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString cbcom = ui->comboBoxCom->currentText();
     //qDebug() << cbID;
     QFile cbcomfile(tablenameS + "comboBoxCom");
          if (!cbcomfile.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outgcom(&cbcomfile);
          outgcom << cbcom;

             cbcomfile.close();
}

//

void MainWindow::SaveC1slot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString cbc1= ui->comboBoxC1->currentText();
     //qDebug() << cbID;
     QFile cbc1file(tablenameS + "comboBoxC1");
          if (!cbc1file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outgc1(&cbc1file);
          outgc1 << cbc1;

             cbc1file.close();
}

void MainWindow::SaveC2slot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString cbc2 = ui->comboBoxC2->currentText();
     //qDebug() << cbID;
     QFile cbc2file(tablenameS + "comboBoxC2");
          if (!cbc2file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;

          QTextStream outgc2(&cbc2file);
          outgc2 << cbc2;

             cbc2file.close();
}

//+++++++++++++++Glossary save buttons


     void MainWindow::saveGIDslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGIDs = ui->comboBoxGID->currentText();
          //qDebug() << cbID;
          QFile cbGIDsfile(tablenameS + "comboBoxGID");
               if (!cbGIDsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGIDs(&cbGIDsfile);
               outgGIDs << cbGIDs;

                  cbGIDsfile.close();
     }

     void MainWindow::saveGESslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGESs = ui->comboBoxGES->currentText();
          //qDebug() << cbID;
          QFile cbGESsfile(tablenameS + "comboBoxGES");
               if (!cbGESsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGESs(&cbGESsfile);
               outgGESs << cbGESs;

                  cbGESsfile.close();
     }


     void MainWindow::saveGTSslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGTSs = ui->comboBoxGTS->currentText();
          //qDebug() << cbID;
          QFile cbGTSsfile(tablenameS + "comboBoxGTS");
               if (!cbGTSsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGTSs(&cbGTSsfile);
               outgGTSs << cbGTSs;

                  cbGTSsfile.close();
     }

     void MainWindow::saveGSIDslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGSIDs = ui->comboBoxGSID->currentText();
          //qDebug() << cbID;
          QFile cbGSIDsfile(tablenameS + "comboBoxGSID");
               if (!cbGSIDsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGSIDs(&cbGSIDsfile);
               outgGSIDs << cbGSIDs;

                  cbGSIDsfile.close();
     }

     void MainWindow::saveGSESslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGSESs = ui->comboBoxGSES->currentText();
          //qDebug() << cbID;
          QFile cbGSESsfile(tablenameS + "comboBoxGSES");
               if (!cbGSESsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGSESs(&cbGSESsfile);
               outgGSESs << cbGSESs;

                  cbGSESsfile.close();
     }

     void MainWindow::saveGSTSslot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbGSTSs = ui->comboBoxGSTS->currentText();
          //qDebug() << cbID;
          QFile cbGSTSsfile(tablenameS + "comboBoxGSTS");
               if (!cbGSTSsfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgGSTSs(&cbGSTSsfile);
               outgGSTSs << cbGSTSs;

                  cbGSTSsfile.close();
     }


     void MainWindow::SaveFilter2slot()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbFilter2 = ui->comboBoxFilter2->currentText();
          //qDebug() << cbID;
          QFile cbFilter2file(tablenameS + "comboBoxFilter2");
               if (!cbFilter2file.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgFilter2(&cbFilter2file);
               outgFilter2 << cbFilter2;

                  cbFilter2file.close();
     }


     //----------

     void MainWindow::saveslotFilterG2()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbFilterG2 = ui->comboBoxFilterG2->currentText();
          //qDebug() << cbID;
          QFile cbFilterG2file(tablenameS + "comboBoxFilterG2");
               if (!cbFilterG2file.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgFilterG2(&cbFilterG2file);
               outgFilterG2 << cbFilterG2;

                  cbFilterG2file.close();
     }






     void MainWindow::saveslotEQES()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbEQES = ui->comboBoxEQES->currentText();
          //qDebug() << cbID;
          QFile cbEQESfile(tablenameS + "comboBoxEQES");
               if (!cbEQESfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgEQES(&cbEQESfile);
               outgEQES << cbEQES;

                  cbEQESfile.close();
     }





     void MainWindow::saveslotEQTS()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbEQTS = ui->comboBoxEQTS->currentText();
          //qDebug() << cbID;
          QFile cbEQTSfile(tablenameS + "comboBoxEQTS");
               if (!cbEQTSfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgEQTS(&cbEQTSfile);
               outgEQTS << cbEQTS;

                  cbEQTSfile.close();
     }





     void MainWindow::saveslotFilterEQ()
     {
         QString tablenameS = ui->comboBoxtables->currentText();

          QString cbFilterEQ = ui->comboBoxFilterEQ->currentText();
          //qDebug() << cbID;
          QFile cbFilterEQfile(tablenameS + "comboBoxFilterEQ");
               if (!cbFilterEQfile.open(QIODevice::WriteOnly | QIODevice::Text))
                   return;

               QTextStream outgFilterEQ(&cbFilterEQfile);
               outgFilterEQ << cbFilterEQ;

                  cbFilterEQfile.close();
     }



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::itemChanged(int nrow, int ncol)
{
     //qDebug() << nrow;
     //qDebug() << ncol;

    //get name of col

     int nrowd=nrow+1;
     int ncold=ncol+1;

     ui->showrownr->setText( QString::number(nrowd));
     ui->showcolnr->setText( QString::number(ncold));

     QString colnrst = ui->showcolnr->text();
     //int nc = colnrst.toInt();
     //qDebug() << nc;

     QString rownrst = ui->showrownr->text();
     //int nr = rownrst.toInt();
     //qDebug() << nr;

        //get column name
     QString namecol = ui->tableAll->horizontalHeaderItem(ncol)->text();
     //qDebug() << "namecol";
                 //qDebug() << namecol;


     //ui->lshowrow->setText(nrow);
     ui->lshowcol->setText(namecol);

     QString cellText;

     cellText = ui->tableAll->model()->data(ui->tableAll->model()->index(nrow,ncol)).toString();



     QString ctshort = cellText.left(20);
     //qDebug() << cellText;

/*
     //+++++++++++++++
     QString activedb = ui->comboBoxtables->currentText();
     QString cbTS = ui->lshowcol->text();
     QString cbID = ui->comboBoxID->currentText();
     QString sidr = ui->idforedit2->text();



     //SELECT NTS FROM StringDB.StringsIII WHERE SID='SID00001';

     QString getTS = "SELECT " + cbTS + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
     //qDebug() << getTS;

     //
     QSqlQuery queryTS(getTS);
     queryTS.exec();

//QString cellText;

//QString cellText = index.data().toString();

     while (queryTS.next())
     {


cellText = queryTS.value(0).toString();

    }
     //+++++++++++++++
*/
     QString cbip = ui->comboBoxID->currentText();
     //qDebug() << "cbip";
     //qDebug() << cbip;
     if(cbip=="")
     {
         //QMessageBox msgBox;
         //msgBox.setText("Please select ID.");
         //msgBox.exec();

         ui->idforedit->setText("Please select ID.");
         ui->idforedit2->setText("Please select ID.");
         ui->idforeditMeta->setText("Please select ID.");
         ui->idforeditHis->setText("Please select ID.");
          ui->ref1TextEdit->setPlainText("");
           ui->TextEdit->setPlainText("");
            ui->TextEditStat->setPlainText("");
             ui->TextEditCom->setPlainText("");
              ui->TextEditHis->setPlainText("");
               ui->RefTextEdit->setPlainText("");
     }
     else
 {
        //locaction of ID column
         int indxidp = ui->comboBoxID->currentIndex();
         //qDebug() << "indxidp";
          //qDebug() << indxidp;

  //--------------------------------

   //int indxid = indxidp-1;
     int indxid = indxidp;
     //QString cellTextID = ui->tableAll->item(nrow, indxid)->text();
     QString cellTextID = ui->tableAll->model()->data(ui->tableAll->model()->index(nrow,indxid)).toString();
      //qDebug() << "cellTextID";
       //qDebug() << cellTextID;

   //---------------------------------

  if(cellTextID=="")
     {
         //QMessageBox msgBox;
         //msgBox.setText("Error: ID missing.");
        // msgBox.exec();

         ui->idforedit->setText("ID missing.");
         ui->idforedit2->setText("ID missing.");
         ui->idforeditMeta->setText("ID missing.");
         ui->idforeditHis->setText("ID missing.");
          ui->ref1TextEdit->setPlainText("");
           ui->TextEdit->setPlainText("");
            ui->TextEditStat->setPlainText("");
             ui->TextEditCom->setPlainText("");
              ui->TextEditHis->setPlainText("");
               ui->RefTextEdit->setPlainText("");

     }

    else
      {
     ui->idforedit->setText(cellTextID);
     ui->idforeditMeta->setText(cellTextID);
     ui->idforeditHis->setText(cellTextID);
     ui->idforedit2->setText(cellTextID);
     //ui->RefTextEdit->setPlainText(cellText);
     if(
       (ui->checkBoxClickCell->isChecked())
        )
           {
     ui->lineEditMark->setText(ctshort);
            }
     MainWindow::itemRefy();
        }

     QString tablenameS = ui->comboBoxtables->currentText();
     //QString tsedit = "SELECT * FROM " + tablenameS + " WHERE SID = '" + cellTextID + "'";
     QString cbID = ui->comboBoxID->currentText();
     QString cbES = ui->comboBoxES->currentText();
     //ui->viewES->setText(cbES);
     //ui->subwindow_2->setWindowTitle(cbES);
     //ui->subwindow_2->setWindowIcon(QIcon("Icon.png"));
     //ui->subwindow_2->setWindowIcon(QIcon(QString::fromUtf8(":Icon.png")));
     //ui->subwindow_2->setWindowIcon( QIcon(QPixmap(1,1)) );
     QString tsedit = "SELECT * FROM " + tablenameS + " WHERE " + cbID + " = '" + cellTextID + "'";

     //qDebug() << tsedit;

     //qDebug() << strtable;

     QSqlQuery querytse(tsedit);


     // qDebug() << tse = querytse.value.toString();


     int indexqu=0;
     while (querytse.next())
     {


     QString cbip = ui->comboBoxID->currentText();
     if((cbip!="")&&(cellTextID!=""))
     {
     int indxidp = ui->comboBoxID->currentIndex();
     int indxid = indxidp;
     QString ide;
     //ide = querytse.value(0).toString();
     ide = querytse.value(indxid).toString();
     ui->idforedit->setText(ide);
     ui->idforedit2->setText(ide);
     ui->idforeditMeta->setText(ide);
     ui->idforeditHis->setText(ide);
     }
     else
     {
         QMessageBox msgBox;
         msgBox.setText("Please select ID.");
         msgBox.exec();

     }


     QString cbes = ui->comboBoxES->currentText();
     if(cbes!="-")
     {
     int indxesep = ui->comboBoxES->currentIndex();
     int indxese = indxesep-1;
     QString ese;
     //ese = querytse.value(1).toString();
     ese = querytse.value(indxese).toString();
     ui->ref1TextEdit->setPlainText(ese);
     }
     else
     {
       ui->ref1TextEdit->setPlainText("");
     }

     QString cbts = ui->comboBoxTS->currentText();
     if(cbts!="-")
     {
     int indxtsep = ui->comboBoxTS->currentIndex();
     int indxtse = indxtsep-1;
     QString tse;

     tse = querytse.value(indxtse).toString();
     ui->TextEdit->setPlainText(tse);
     }
     else
     {
       ui->TextEdit->setPlainText("");
     }

     QString cbstat = ui->comboBoxStat->currentText();
     QString cbcom = ui->comboBoxCom->currentText();
     QString cbhis = ui->comboBoxHis->currentText();

     if(cbstat!="-")
     {
     int indxstatp = ui->comboBoxStat->currentIndex();
     int indxstat = indxstatp-1;
     QString stat;

     stat = querytse.value(indxstat).toString();
     ui->TextEditStat->setPlainText(stat);
     }
     else
     {
          ui->TextEditStat->setPlainText("");
     }

     if(cbcom!="-")
     {
     int indxcomp = ui->comboBoxCom->currentIndex();
     int indxcom = indxcomp-1;
     QString com;

     com = querytse.value(indxcom).toString();
     ui->TextEditCom->setPlainText(com);
     }
     else
     {
          ui->TextEditCom->setPlainText("");
     }

     if(cbhis!="-")
     {
     int indxhisp = ui->comboBoxHis->currentIndex();
     int indxhis = indxhisp-1;
     QString his;

     his = querytse.value(indxhis).toString();
     ui->TextEditHis->setPlainText(his);
     }
     else
     {
         ui->TextEditHis->setPlainText("");
     }


     indexqu++;
        }

   }

}





//+++++++++++++++++++Reference window


void MainWindow::statusslot()
{


    QString refstat = ui->status->text();

    ui->statusBar->showMessage(refstat);



}

void MainWindow::itemRef(const QModelIndex &index)
{




    if (index.isValid())
    {

                QString activedb = ui->comboBoxtables->currentText();
                QString cbTS = ui->lshowcol->text();
                QString cbID = ui->comboBoxID->currentText();
                QString sidr = ui->idforedit2->text();



                //SELECT NTS FROM StringDB.StringsIII WHERE SID='SID00001';

                QString getTS = "SELECT " + cbTS + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
                //qDebug() << getTS;

                //
                QSqlQuery queryTS(getTS);
                queryTS.exec();



        //QString cellText = index.data().toString();
QString cellText;
                while (queryTS.next())
                {
cellText = queryTS.value(0).toString();
                }
 //qDebug() << cellText;


        ui->RefTextEdit->setPlainText(cellText);
      }


}


void MainWindow::itemRefy()
{






                QString activedb = ui->comboBoxtables->currentText();
                QString cbTS = ui->lshowcol->text();
                QString cbID = ui->comboBoxID->currentText();
                QString sidr = ui->idforedit2->text();



                //SELECT NTS FROM StringDB.StringsIII WHERE SID='SID00001';

                QString getTS = "SELECT " + cbTS + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
                //qDebug() << getTS;

                //
                QSqlQuery queryTS(getTS);
                queryTS.exec();



        //QString cellText = index.data().toString();
QString cellText;
                while (queryTS.next())
                {
cellText = queryTS.value(0).toString();
                }
 //qDebug() << cellText;


        ui->RefTextEdit->setPlainText(cellText);



}


//+++++++++++++++send to database++++++++++++++++
void MainWindow::updateSslot()

{

    QString activedb;
    activedb = ui->comboBoxtables->currentText();
   // activedb = ui->tableSEdit->text();

    //qDebug() << activedb;

    QString ntsr;
    ntsr = ui->TextEdit->toPlainText();
    QString ntsre;
    ntsre = ntsr.replace("'", "\\'");
    //qDebug() << "\\'";
    //qDebug() << ntsre;

    QString sidr;
    sidr = ui->idforedit->text();
    //qDebug() << sidr;

    /*if(sidr == "Please click on the ID of the string you want to edit.")

    {
      ui->idforedit->setText("Please click on the ID of the string you want to edit.");

    }

    else*/
    //{

    QString cbNTS = ui->comboBoxNTS->currentText();
    QString cbID = ui->comboBoxID->currentText();
    QString cbHis = ui->comboBoxHis->currentText();

    //QString updatedit = "UPDATE `" + activedb + "` SET `NTS`= '" + ntsre + "' WHERE `SID`='" + sidr + "'";
    //qDebug() << updatedit;


    if (
          ((ui->checkBoxHis->isChecked())&&(~(cbHis=="-")))
       )
       {

        //qDebug() << "History";


        QString cbHis = ui->comboBoxHis->currentText();
        QString cbTS = ui->comboBoxTS->currentText();
        QString cbID = ui->comboBoxID->currentText();
        QString sidr = ui->idforedit->text();



        //SELECT NTS FROM StringDB.StringsIII WHERE SID='SID00001';

        QString getTS = "SELECT " + cbTS + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
        //qDebug() << getTS;

        //
        QSqlQuery queryTS(getTS);
        //queryTS.exec();

        int indexnthts=0;
        while (queryTS.next())
            {
        QString oldTSo = queryTS.value(0).toString();
        QString oldTS = oldTSo.replace("'", "\\'");

          //qDebug() << oldTS;

          //backlog

          QString getpreHis = "SELECT " + cbHis + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
          //qDebug() << getpreHis;

          //
          QSqlQuery querypre(getpreHis);
          //queryTS.exec();

           QList<QString> hisAr;

          int indexph=0;
          while (querypre.next())
              {
          QString oldHis = querypre.value(0).toString();



          hisAr.append(oldHis);

            indexph++;
            }

          QString hisEo;
          hisEo=hisAr[0];
          QString hisE = hisEo.replace("'", "\\'");
          //qDebug() <<  "oldTS: " + oldTS;
          //qDebug() <<  "box capture: " + ntsr;

          if(ntsr!=oldTS)
    {
          //qDebug() << "old his:" + hisE;

          QString sdate = QDate::currentDate().toString();
          QString stime = QTime::currentTime().toString();
          QString usernmo = ui->userqle->text();
          QString usernm = usernmo.replace("'", "\\'");
          QString cbTSo = ui->comboBoxTS->currentText();
          QString cbTS = cbTSo.replace("'", "\\'");
          QString hisintro = "\r\n<<" + cbTS +  + "-Edit by user " + usernm + ": " + sdate + " at " + stime + ". Previous version:>> ";
          //QString hisintro = "<<Edit by user " + usernm + ": " + sdate + " at " + stime + ". Previous version of " + cbTS + ":>> ";
          //qDebug() << hisintro;

           //
        QString his = hisintro + "\r\n" + oldTS + "\r\n" + hisE;
        //QString his = hisintro +  oldTS +  hisE;
        //QString updatehis = "UPDATE `" + activedb + "` SET `" + cbHis + "`= '" + oldTS + "' WHERE `" + cbID + "`='" + sidr + "'";
        //QString updatehis = "UPDATE `" + activedb + "` SET `" + cbHis + "`= '" + hisintro + "\r\n" + oldTS + "\r\n" + hisE + "' WHERE `" + cbID + "`='" + sidr + "'";
        QString updatehis = "UPDATE `" + activedb + "` SET `" + cbHis + "`= '" + his + "' WHERE `" + cbID + "`='" + sidr + "'";
        //qDebug() << updatehis;


        QSqlQuery queryupdatehis(updatehis);
        queryupdatehis.exec();

        //get updated his

        QString getnewHis = "SELECT " + cbHis + " FROM " + activedb + " WHERE " + cbID + "=" + "'" + sidr + "'";
        //qDebug() << getpreHis;

        //
        QSqlQuery querynew(getnewHis);
        //queryTS.exec();

         QList<QString> newAr;

        int indexphn=0;
        while (querynew.next())
            {
        QString newHis = querynew.value(0).toString();



        newAr.append(newHis);

          indexphn++;
          }

        QString newEo;
        newEo=newAr[0];


        ui->TextEditHis->setPlainText(newEo);


        indexnthts++;
            }

      }
        }
     //history end



    QString updatedit = "UPDATE `" + activedb + "` SET `" + cbNTS + "`= '" + ntsre + "' WHERE `" + cbID + "`='" + sidr + "'";


   // UPDATE `StringDB`.`StringsIII` SET `NTS`='Num\'merch' WHERE `SID`='SID00001';


    QSqlQuery queryupdate(updatedit);
    queryupdate.exec();

    //ui->tableAll->update();



    //connect(tableAll, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(itemChanged(const QModelIndex &)));

    //MainWindow::tableS();


    if (     (ui->checkBoxFilter->isChecked()))
       {
        ui->filterbuttonS->animateClick();
        }

    else if (     (ui->checkBoxFilterG->isChecked()))
       {
        ui->GCButton->animateClick();
        }

    else if (     (ui->checkBoxFilterkeepEQ->isChecked()))
       {
        ui->EQButton->animateClick();
        }



    else
    {
    ui->TableButtonS->animateClick();
    }
    //connect(ui->updateSbutton,SIGNAL(pressed()),this,SLOT(tableS()));


    //ui->tableAll->viewport().update();

//update table view
 /*
    //QString ntsupd = "SELECT NTS FROM `" + activedb + "`";
    QString ntsupd = "SELECT " + cbNTS + " FROM `" + activedb + "`";

    //qDebug() << ntsupd;


    QSqlQuery querynts(ntsupd);


    //tse = querytse.value.toString();


    int indexnt=0;
    while (querynts.next())
    {
    //QString tse;
    //tse = querytse.value(3).toString();


    //qDebug() << "tse: " + tse;

        int indxidp = ui->comboBoxNTS->currentIndex();
         int indxid =   indxidp-1;

        //qDebug() << indxid;


    //ui->tableAll->setItem(indexnt,3,new QTableWidgetItem(querynts.value(0).toString()));
    ui->tableAll->setItem(indexnt,indxid,new QTableWidgetItem(querynts.value(0).toString()));

    indexnt++;
}

//update history


    //QString ntsupd = "SELECT NTS FROM `" + activedb + "`";
    QString hisupd = "SELECT " + cbHis + " FROM `" + activedb + "`";

    //qDebug() << ntsupd;


    QSqlQuery queryhis(hisupd);


    //tse = querytse.value.toString();


    int indexnth=0;
    while (queryhis.next())
    {
    //QString tse;
    //tse = querytse.value(3).toString();


    //qDebug() << "tse: " + tse;

        int indxidph = ui->comboBoxHis->currentIndex();
         int indxidh =   indxidph-1;

        //qDebug() << indxid;


    //ui->tableAll->setItem(indexnt,3,new QTableWidgetItem(querynts.value(0).toString()));
    ui->tableAll->setItem(indexnth,indxidh,new QTableWidgetItem(queryhis.value(0).toString()));

    indexnth++;
}

*/




    //ui->tableAll->setItem(index,3,new QTableWidgetItem(ntsr));

//else end }

}


//+++++++++++++++++++++end of normal edit strings






//---------update stat

void MainWindow::updateSslotStat()
{
    QString activedb;
    activedb = ui->comboBoxtables->currentText();
    //qDebug() << activedb;
    QString cbID = ui->comboBoxID->currentText();

    QString sidr;
    sidr = ui->idforedit->text();

    QString statr;
    statr = ui->TextEditStat->toPlainText();

    if(statr!="")
    {
    QString statre;
    statre = statr.replace("'", "\\'");

    QString cbstat = ui->comboBoxStat->currentText();

    if(cbstat!="-")
        {
    QString updatedit = "UPDATE `" + activedb + "` SET `" + cbstat + "`= '" + statre + "' WHERE `" + cbID + "`='" + sidr + "'";

    QSqlQuery queryupdate(updatedit);
    queryupdate.exec();
        }
    }
    //Com


    QString comr;
    comr = ui->TextEditCom->toPlainText();

    if(comr!="")
    {
        QString comre;
        comre = comr.replace("'", "\\'");

        QString cbCom = ui->comboBoxCom->currentText();

        QString updatedit = "UPDATE `" + activedb + "` SET `" + cbCom + "`= '" + comre + "' WHERE `" + cbID + "`='" + sidr + "'";

        QSqlQuery queryupdate(updatedit);
        queryupdate.exec();


    }

    if (     (ui->checkBoxFilter->isChecked()))
        {
         ui->filterbuttonS->animateClick();
         }

     else if (     (ui->checkBoxFilterG->isChecked()))
        {
         ui->GCButton->animateClick();
         }

     else if (     (ui->checkBoxFilterkeepEQ->isChecked()))
        {
         ui->EQButton->animateClick();
         }

     else
     {
     ui->TableButtonS->animateClick();
     }





}


/*
//------end---update stat

void MainWindow::updateSslotCom()
{
    QString activedb;
    activedb = ui->comboBoxtables->currentText();
    QString comr;
    comr = ui->TextEditCom->toPlainText();
    QString comre;
    comre = comr.replace("'", "\\'");
    QString sidr;
    sidr = ui->idforedit->text();
    QString cbCom = ui->comboBoxCom->currentText();
    QString cbID = ui->comboBoxID->currentText();
    QString updatedit = "UPDATE `" + activedb + "` SET `" + cbCom + "`= '" + comre + "' WHERE `" + cbID + "`='" + sidr + "'";
    QSqlQuery queryupdate(updatedit);
    queryupdate.exec();
    //ui->tableAll->update();
    QString comupd = "SELECT " + cbCom + " FROM `" + activedb + "`";
    QSqlQuery querycom(comupd);
    int indexnt=0;
    while (querycom.next())
    {
        int indxidp = ui->comboBoxCom->currentIndex();
        int indxid = indxidp-1;
    ui->tableAll->setItem(indexnt,indxid,new QTableWidgetItem(querycom.value(0).toString()));
    indexnt++;
    }
}
*/


//+++++++start+++++++++advanced edit


void MainWindow::updateAdslot()


{

    QString colname;
    colname = ui->lshowcol->text();

    QString activedb;
    activedb = ui->comboBoxtables->currentText();
   // activedb = ui->tableSEdit->text();

    //qDebug() << activedb;

    QString newr;
    newr = ui->RefTextEdit->toPlainText();
    QString newre;
    newre = newr.replace("'", "\\'");
    //qDebug() << "\\'";
    //qDebug() << ntsre;

    QString sidr;
    sidr = ui->idforedit2->text();


    QString cbID = ui->comboBoxID->currentText();

    //QString updatedita = "UPDATE `" + activedb + "` SET " + "`" + colname + "`= '" + newre + "' WHERE `SID`='" + sidr + "'";
    QString updatedita = "UPDATE `" + activedb + "` SET " + "`" + colname + "`= '" + newre + "' WHERE `" + cbID + "`='" + sidr + "'";
    //qDebug() << updatedita;


   // UPDATE `StringDB`.`StringsIII` SET `NTS`='Num\'merch' WHERE `SID`='SID00001';


    QSqlQuery queryupdatea(updatedita);
    queryupdatea.exec();

    //ui->tableAll->update();



    //connect(tableAll, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(itemChanged(const QModelIndex &)));

    //connect(ui->updateSbutton,SIGNAL(pressed()),this,SLOT(tableS()));


    //ui->tableAll->viewport().update();


    //QString ntsupd = "SELECT NTS FROM `" + activedb + "`";

    //QString nadupd = "SELECT " + colname + " FROM `" + activedb + "` WHERE SID='" + sidr + "'";
    QString nadupd = "SELECT " + colname + " FROM `" + activedb + "` WHERE " + cbID + " ='" + sidr + "'";

    //qDebug() << nadupd;


    //SELECT NTS FROM StringDB.StringsIII WHERE SID='SID00001';

    //qDebug() << ntsupd;


    QSqlQuery querynad(nadupd);


    //tse = querytse.value.toString();




    int indexnt=0;
    while (querynad.next())
    {
    //QString tse;
    //tse = querytse.value(3).toString();


    //qDebug() << "tse: " + tse;


        QString colnrst = ui->showcolnr->text();
        int nc = colnrst.toInt();
        nc=nc-1;
        //qDebug() << nc;
        QString rownrst = ui->showrownr->text();
        int nr = rownrst.toInt();
        nr=nr-1;
    //ui->tableAll->setItem(indexnt,3,new QTableWidgetItem(querynad.value(0).toString()));
    ui->tableAll->setItem(nr,nc,new QTableWidgetItem(querynad.value(0).toString()));

    indexnt++;
}


    if (     (ui->checkBoxFilter->isChecked()))
        {
         ui->filterbuttonS->animateClick();
         }

    else if (     (ui->checkBoxFilterG->isChecked()))
        {
         ui->GCButton->animateClick();
         }

     else if (     (ui->checkBoxFilterkeepEQ->isChecked()))
        {
         ui->EQButton->animateClick();
         }
    else
    {
    ui->TableButtonS->animateClick();
    }

}



//++++++++++end ++++++++++++++advanced edit

void MainWindow::FilterCboxslot()
{

    QString tablenameS = ui->comboBoxtables->currentText();

     QString colnames = "SHOW COLUMNS FROM " + tablenameS;
           //qDebug() << colnames;

           QSqlQuery querycol(colnames);

           QList<QString> colAr;

           int ncol=0;
           while (querycol.next())
               {
               QString col;
               col = querycol.value(0).toString();
               colAr.append(col);
               ncol++;
               //qDebug() << ncol;
                 }


          ui->comboBoxC1->clear();
          ui->comboBoxC1->addItems(colAr);
          ui->comboBoxC1->setCurrentIndex(0);

          //qDebug() << querycol.size();
          ui->comboBoxC2->clear();
          ui->comboBoxC2->addItems(colAr);
           //ui->comboBoxC2->setCurrentIndex(querycol.size()-1);
          ui->comboBoxC2->setCurrentIndex(1);




   QFile hc1file(tablenameS + "comboBoxC1");
          if (!hc1file.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
          QTextStream inc1(&hc1file);
          while (!inc1.atEnd())
                              {
              QString keepselectc1 = inc1.readLine();
              //qDebug() << keepselectID;
              if(~(keepselectc1.isEmpty()))
              {
                  ui->comboBoxC1->clear();
                  //colAr.append("-");
                  ui->comboBoxC1->addItems(colAr);
              int indexc1 = ui->comboBoxC1->findText(keepselectc1);
              ui->comboBoxC1->setCurrentIndex(indexc1);
              }

                               }


          QFile hc2file(tablenameS + "comboBoxC2");
          if (!hc2file.open(QIODevice::ReadOnly | QIODevice::Text))
              return;
          QTextStream inc2(&hc2file);
          while (!inc2.atEnd())
                              {
              QString keepselectc2 = inc2.readLine();
              //qDebug() << keepselectID;
              if(~(keepselectc2.isEmpty()))
              {
                  ui->comboBoxC2->clear();
                  //colAr.append("-");
                  ui->comboBoxC2->addItems(colAr);
              int indexc2 = ui->comboBoxC2->findText(keepselectc2);
              ui->comboBoxC2->setCurrentIndex(indexc2);
              }

                               }





}

void MainWindow::Glossaryboxslot()
{

    QString tablenameS = ui->comboBoxtables->currentText();
    QString tablenameG  = ui->comboBoxTableG->currentText();

    QString colnames = "SHOW COLUMNS FROM " + tablenameG;
          //qDebug() << colnames;

          QSqlQuery querycol(colnames);

          QList<QString> colAr;

          int ncol=0;
          while (querycol.next())
              {
              QString col;
              col = querycol.value(0).toString();
              colAr.append(col);
              ncol++;
              //qDebug() << ncol;
                }


   ui->comboBoxGID->clear();
   ui->comboBoxGID->addItems(colAr);
   ui->comboBoxGID->setCurrentIndex(0);

   ui->comboBoxGES->clear();
   ui->comboBoxGES->addItems(colAr);
   ui->comboBoxGES->setCurrentIndex(1);

   ui->comboBoxGTS->clear();
   ui->comboBoxGTS->addItems(colAr);
   ui->comboBoxGTS->setCurrentIndex(2);



   QFile hGSIDfile(tablenameS + "comboBoxGID");
   if (!hGSIDfile.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
   QTextStream inGSID(&hGSIDfile);
   while (!inGSID.atEnd())
                       {
       QString keepselectGSID = inGSID.readLine();
       //qDebug() << keepselectID;
       if(~(keepselectGSID.isEmpty()))
       {
           ui->comboBoxGID->clear();
           //colAr.append("-");
           ui->comboBoxGID->addItems(colAr);
       int indexGSID = ui->comboBoxGID->findText(keepselectGSID);
       ui->comboBoxGID->setCurrentIndex(indexGSID);
       }

                        }




   QFile hGSESfile(tablenameS + "comboBoxGES");
   if (!hGSESfile.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
   QTextStream inGSES(&hGSESfile);
   while (!inGSES.atEnd())
                       {
       QString keepselectGSES = inGSES.readLine();
       //qDebug() << keepselectID;
       if(~(keepselectGSES.isEmpty()))
       {
           ui->comboBoxGES->clear();
           //colAr.append("-");
           ui->comboBoxGES->addItems(colAr);
       int indexGSES = ui->comboBoxGES->findText(keepselectGSES);
       ui->comboBoxGES->setCurrentIndex(indexGSES);
       }

                        }





   QFile hGSTSfile(tablenameS + "comboBoxGTS");
   if (!hGSTSfile.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
   QTextStream inGSTS(&hGSTSfile);
   while (!inGSTS.atEnd())
                       {
       QString keepselectGSTS = inGSTS.readLine();
       //qDebug() << keepselectID;
       if(~(keepselectGSTS.isEmpty()))
       {
           ui->comboBoxGTS->clear();
           //colAr.append("-");
           ui->comboBoxGTS->addItems(colAr);
       int indexGSTS = ui->comboBoxGTS->findText(keepselectGSTS);
       ui->comboBoxGTS->setCurrentIndex(indexGSTS);
       }

                        }

   //+++++end+++++filter save buttons
}

//+++++++++++++GE+++++++++++++++++++++++


void MainWindow::synconlyslot()
{
    ui->tableGE->clearContents();
     ui->TableButtonG->animateClick();


}


void MainWindow::gesyncslot()
{




               int sid = ui->comboBoxGID->currentIndex();
               QString sidstr = ui->comboBoxGID->currentText();
               QString zielkol1 = ui->comboBoxGES->currentText();
               QString zielkol2 = ui->comboBoxGTS->currentText();
               int zielkol1int = ui->comboBoxGES->currentIndex();
               int zielkol2int = ui->comboBoxGTS->currentIndex();

               QString activedb = ui->comboBoxTableG->currentText();



               int KolZahl = ui->tableGE->columnCount();
               int ReiZahl = ui->tableGE->rowCount();





               //ID
               QList<QString> IDsAr;
               QString strtable = "SELECT * FROM " + activedb;

               //qDebug() << strtable;

               QSqlQuery queryid(strtable);



                        int indexts=0;
                            while (queryid.next())
                            {
                            //qDebug() << querytables;

                                QString getid = queryid.value(sid).toString();
                                IDsAr.append(getid);

                                //qDebug() << getid;

                                //qDebug() << col;
                              indexts++;

                            }





                            for (int row = 0 ; row < ReiZahl ; ++row)                                
                            {

                                QString idtext;
                              if(sidstr!="")
                              {
                              //qDebug() << row;
                              QTableWidgetItem *zellid = ui->tableGE->item(row, sid);

                              if (!zellid  || zellid ->text().isEmpty())
                              {
                                  //qDebug() << row;
                              }
                              else
                              {

                              idtext = zellid->text();
                               //qDebug() << zelltext1;
                              }

                              }

                                //
                                  QString zelltext1;
                                if(zielkol1!="")
                                {
                                //qDebug() << row;
                                QTableWidgetItem *zelle1 = ui->tableGE->item(row, zielkol1int);

                                if (!zelle1  || zelle1 ->text().isEmpty())
                                {
                                    //qDebug() << row;
                                }
                                else
                                {

                                zelltext1 = zelle1->text();
                                 //qDebug() << zelltext1;
                                }

                                }

                                 QString zelltext2;
                                if(zielkol2!="")
                                {
                                QTableWidgetItem *zelle2 = ui->tableGE->item(row, zielkol2int);

                                if (!zelle2  || zelle2 ->text().isEmpty())
                                {
                                    //qDebug() << row;
                                }
                                else
                                {
                                zelltext2 = zelle2->text();
                                //qDebug() << zelltext2;
                                }
                                }




                                QCheckBox *mcb = qobject_cast<QCheckBox*>(ui->tableGE->cellWidget(row, KolZahl-1));
                                if(mcb->isChecked())
                                {

                                    //QString IDNumber = IDsAr[row];
                                    QString IDNumber = idtext;
                                    //qDebug() << IDNumber ;


                                    //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                                    QString strup1 = "UPDATE `" + activedb + "` SET `" + zielkol1  + "`='" + zelltext1 + "' WHERE `" + sidstr   + "`= '" + IDNumber  + "'";
                                   //qDebug() << strup;
                                    QSqlQuery queryup1(strup1);
                                    queryup1.exec();

                                    QString strup2 = "UPDATE `" + activedb + "` SET `" + zielkol2  + "`='" + zelltext2 + "' WHERE `" + sidstr   + "`= '" + IDNumber  + "'";
                                   //qDebug() << strup;
                                    QSqlQuery queryup2(strup2);
                                    queryup2.exec();





                                }





                            }










           ui->TableButtonG->animateClick();




}



void MainWindow::gefilterslot()
{


      ui->tableGE->clearContents();
    //ui->GCButton->animateClick();
    QString findin = ui->filterinputGE->text();



    if(findin=="")
    {
     return;
    }


    //ui->tableAll->setColumnCount(KolZahl);


    //



                //+++++++++Glossary tab filters


                 QString tablenameG  = ui->comboBoxTableG->currentText();
                  ui->lineEditGEname->setText(tablenameG);


                if(tablenameG.trimmed().isEmpty())
                            {
                QMessageBox msgBox;
                msgBox.setText("Please select the glossary table.");
                msgBox.exec();
                             }

                else
                    {





                    QString gtable = "SELECT * FROM " + tablenameG;

                    //qDebug() << strtable;

                    QSqlQuery queryg(gtable);


                       int rows = 0;

                       ui->tableGE->setColumnCount(queryg.record().count()+1);
;
                       ui->tableGE->setRowCount(0);


                     QString colnames = "SHOW COLUMNS FROM " + tablenameG;
                     //qDebug() << colnames;

                     QSqlQuery querycol(colnames);

                     QList<QString> colAr;

                     int ncol=0;
                     while (querycol.next())
                         {
                         QString col;
                         col = querycol.value(0).toString();
                         colAr.append(col);
                         ncol++;
                         //qDebug() << ncol;
                           }


                      ui->tableGE->setHorizontalHeaderLabels(colAr << "Update");



                     int index=0;
                     while (queryg.next())
                     {


                         for (int col = 0; col < ncol; col++)
                         {

                             QString colFilter = queryg.value(col).toString();
                             //qDebug() << colFilter ;




                         if (
                                 (colFilter.contains(findin, Qt::CaseInsensitive))
                              )

                              {

                              //qDebug() << colFilter;


                              ui->tableGE->setRowCount(rows+1);


                                 for (int coldisp = 0; coldisp < ncol; coldisp++)
                                 {
                                   //ui->tableAll->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
                                     //ui->tableAll->setItem(index,coldisp,new QTableWidgetItem(query.value(coldisp).toString()));



                                     QTableWidgetItem *item;
                                     item = new QTableWidgetItem(queryg.value(coldisp).toString());
                                     item->setFlags(item->flags() & ~Qt::ItemIsEditable);



                                     ui->tableGE->setItem(rows,coldisp,new QTableWidgetItem(queryg.value(coldisp).toString()));





                                    }

                         QCheckBox *cb= new QCheckBox();
                                              ui->tableGE->setCellWidget(rows, ncol, cb);
                                              cb->setCheckState(Qt::Unchecked);


                                      rows++;

                                }

                         }
                          index++;

                     }





                    }







      //



}



//+++++++++start++++++++++++++++++++++++++table G
//++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::tableG()

{

    //+++++++++Glossary tab filters


     QString tablenameG  = ui->comboBoxTableG->currentText();
      ui->lineEditGEname->setText(tablenameG);




    //QString tablenameG = ui->tableGEdit->text();




    if(tablenameG.trimmed().isEmpty())
                {
    QMessageBox msgBox;
    msgBox.setText("Please select the glossary table.");
    msgBox.exec();
                 }

    else
        {


        QFile t2file("t2file.txt");
         if (!t2file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

         QTextStream outg(&t2file);
         outg << tablenameG;



   //+++++++++++++++    fulltable();

        ui->deft2->setText(tablenameG);


        QString gtable = "SELECT * FROM " + tablenameG;

        //qDebug() << strtable;

        QSqlQuery queryg(gtable);



         ui->tableG->setColumnCount(queryg.record().count());
           ui->tableGE->setColumnCount(queryg.record().count()+1);
         ui->tableG->setRowCount(queryg.size());
           ui->tableGE->setRowCount(queryg.size());


         QString colnames = "SHOW COLUMNS FROM " + tablenameG;
         //qDebug() << colnames;

         QSqlQuery querycol(colnames);

         QList<QString> colAr;

         int ncol=0;
         while (querycol.next())
             {
             QString col;
             col = querycol.value(0).toString();
             colAr.append(col);
             ncol++;
             //qDebug() << ncol;
               }

         ui->tableG->setHorizontalHeaderLabels(colAr);
          ui->tableGE->setHorizontalHeaderLabels(colAr << "Update");



         int index=0;
         while (queryg.next())
         {

             for (int coldisp = 0; coldisp < ncol; coldisp++)
             {
               //ui->tableAll->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
                 //ui->tableAll->setItem(index,coldisp,new QTableWidgetItem(query.value(coldisp).toString()));

                 QTableWidgetItem *item;
                 item = new QTableWidgetItem(queryg.value(coldisp).toString());
                 item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                 ui->tableG->setItem(index,coldisp,item);


                 ui->tableGE->setItem(index,coldisp,new QTableWidgetItem(queryg.value(coldisp).toString()));


                }

             QCheckBox *cb= new QCheckBox();
                                  ui->tableGE->setCellWidget(index, ncol, cb);
                                  cb->setCheckState(Qt::Unchecked);



         index++;
         }


         ui->tableG->show();


        }

}




//to remove
void MainWindow::gcmatchslot()
{


}




void MainWindow::gcselectionslot()
{


    if (
            (ui->radioButtonGC->isChecked())
        )
    {
      MainWindow::GCslot();

    }


    if (
            (ui->radioButtonList->isChecked())
        )
    {
      MainWindow::gclistslot();

    }





}







//++++++++++++++++++++++++GC++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::GCslot()

{
     ui->tableAll->clearContents();

     int indxGF2 = ui->comboBoxFilterG2->currentIndex();

     QString filterinG2 = ui->filterinputG2->text();


     QString tablenameS = ui->comboBoxtables->currentText();

     //qDebug() << tablenameS;

     QString strtable = "SELECT * FROM " + tablenameS;

     //qDebug() << strtable;

     QSqlQuery queryS(strtable);




     QString tablenameG = ui->comboBoxTableG->currentText();


    QString gtable = "SELECT * FROM " + tablenameG;

    //qDebug() << gtable;

    QSqlQuery queryG(gtable);

    //int KolZahl = queryg.record().count() + queryS.record().count();

    QString colnamesG = "SHOW COLUMNS FROM " + tablenameG;
    QString colnamesS = "SHOW COLUMNS FROM " + tablenameS;
            //qDebug() << colnames;

            QSqlQuery querycolS(colnamesS);
            QSqlQuery querycolG(colnamesG);

            int KolZahl = querycolS.size()+querycolG.size();

            //int RowZahlS = queryS.size();

            int KolZahlS = querycolS.size();



            ui->tableAll->setColumnCount(KolZahl+1);





            QList<QString> colAr;



            int ncolS=0;
            while (querycolS.next())
                {
                QString colS;
                colS = querycolS.value(0).toString();
                colAr.append(colS);
                ncolS++;
                //qDebug() << ncol;
                  }


            int ncolG=0;
            while (querycolG.next())
                {
                QString colG;
                colG = querycolG.value(0).toString();
                colAr.append(colG);
                ncolG++;
                //qDebug() << ncol;
                  }


            ui->tableAll->setHorizontalHeaderLabels(colAr << "Count");




    //tableGC->setColumnCount(queryS.record().count()+8);
    //tableGC->setRowCount(queryS.size()+queryG.size()+500);





           //ui->tableAll->setColumnCount(queryS.record().count()+8);

           //ui->tableAll->setRowCount(queryS.size()+queryG.size()+500);


 int GIDint = ui->comboBoxGID->currentIndex();
  int GESint = ui->comboBoxGES->currentIndex();
   int GTSint = ui->comboBoxGTS->currentIndex();

   int GSIDint = ui->comboBoxGSID->currentIndex();
    int GSESint = ui->comboBoxGSES->currentIndex();
     int GSTSint = ui->comboBoxGSTS->currentIndex();
      QString GTSt = ui->comboBoxGTS->currentText();


      if(GTSt=="")
      {
          QMessageBox msgBox;
          msgBox.setText("Please select the glossary target column.");
          msgBox.exec();
      }



    QList<QString> gidAr;
    QList<QString> egAr;
    QList<QString> tgAr;

    QList<QString> sidAr;
    QList<QString> esAr;
    QList<QString> tsAr;


    /*while (queryG.next())
    {

        QString gid;
        gid = queryG.value(GIDint).toString();

        //gidAr[index] = gid;
        gidAr.append(gid);
        //qDebug() << gid;

        //trimmed removes leading and trailing spaces

        QString eg;
        eg = queryG.value(GESint).toString();
        eg = eg.trimmed();

        //egAr[index] = eg;
        egAr.append(eg);


        QString tg;
        tg = queryG.value(GTSint).toString();
        tg = tg.trimmed();

        //tgAr[index] = tg;
        tgAr.append(tg);
    }*/

    //new
    int gzeilen =0;
    while (queryG.next())
    {

    //for (int index = 1; index =10000; index ++)

        QString eg;
        eg = queryG.value(GESint).toString();
        eg = eg.trimmed();

        if(eg!="")
        {

                //egAr[index] = eg;
                egAr.append(eg);


                QString gid;
                gid = queryG.value(GIDint).toString();

                //gidAr[index] = gid;
                gidAr.append(gid);
                //qDebug() << gid;

                //trimmed removes leading and trailing spaces
                gzeilen++;




                        QString tg;
                        tg = queryG.value(GTSint).toString();
                        tg = tg.trimmed();

                        if(tg!="")
                        {
                        //tgAr[index] = tg;
                        tgAr.append(tg);
                        }

                        if(tg=="")
                        {
                            tgAr.append("[Missing Glossary Term]");
                        }


        }



    }

    //new end

//+++++++++++++vector+++++++++++++++++++++++++++++

    QVector<QStringList> colArV(KolZahlS);

         //qDebug() << indxC1;
         //qDebug() << indxC2;

               //int index=0;
               while (queryS.next())
                   //for(int index=0;index < RowZahlS; index++)
               {

                   for (int coldisp = 0; coldisp < KolZahlS; coldisp++)
                   //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                   {

                       QString boxAll = queryS.value(coldisp).toString();
                       colArV[coldisp].append(boxAll);
                       //qDebug() << "index";
                       //qDebug() <<  index;
                       //qDebug() << "coldisp";
                       //qDebug() << coldisp;
                          //qDebug() << boxAll;

                      }

               //index++;
               }


    //+++++++++++++++++++++++++++++++++++++++

        /*while (queryS.next())
    {


            QString sid;
            sid = queryS.value(GSIDint).toString();
            sidAr.append(sid);


            QString es;
            es = queryS.value(GSESint).toString();
            esAr.append(es);
            //qDebug() << es;




            QString ts;
            ts = queryS.value(GSTSint).toString();
            tsAr.append(ts);



        }*/



//+++++++++++++++++++++++++++++call string array

   if (
           (ui->checkBoxFilterGL2->isChecked())
           & ~(ui->checkBoxFilterG3->isChecked())
            & ~(ui->checkBoxFilterEmpty->isChecked())

           )



   {

       if(filterinG2=="")
       {

           QMessageBox msgBox;
           msgBox.setText("Error: Search term missing.");
           msgBox.exec();

       }
   else

   {

        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterE2=colArV[indxGF2][sna];
                //qDebug() << colFilterE2;


    //filterG2
                if (

                        (colFilterE2.contains(filterinG2, Qt::CaseInsensitive))
                    )
              {




                //QString esE;
                //esE=esAr[sna];

                QString esE=colArV[GSESint][sna];

                 QString esEr;

                 //QString tsE;
                 //tsE=tsAr[sna];

                 QString tsE=colArV[GSTSint][sna];


                 QString tsEr;




                //remove line breaks                
                if(
                        (ui->checkBoxGILB->isChecked())
                   )
                {
                    QString esEw= esE;
                    QString tsEw= tsE;
                    esEr = esEw.replace(QString("\\n"), QString(" "));
                    esEr = esEw.replace(QString("\\r"), QString(""));
                    tsEr = tsEw.replace(QString("\\n"), QString(" "));
                    tsEr = tsEw.replace(QString("\\r"), QString(""));
                    //qDebug() << colFilter;
                }
                else
                {
                     esEr = esE;
                     tsEr = tsE;
                }



                //qDebug() << sidAr[sna];



                int gna = 0;

                while (gna < gzeilen)

                //for (int na = 0; na = 10; na ++)

                      {
                        QString gidE;
                        gidE=gidAr[gna];

                        QString egE;
                        egE=egAr[gna];

                        QString tgE;
                        tgE=tgAr[gna];
                        //qDebug() << tgE;


                        //reg ex word boundaries
                        QString boundind;
                        if(
                              (ui->checkBoxGMEWO->isChecked())
                          )
                      {
                      QRegExp rxsid("\\b(" + egE + ")\\b");
                      rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                      rxsid.indexIn(esEr);
                      boundind = rxsid.cap(0);
                      //qDebug() <<  boundind;
                       }


                        //compare number of glossary terms in string



                        int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                        int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                        //qDebug() << "EG";
                        //qDebug() << anzahlEG;
                        //qDebug() << "TG";
                        //qDebug() << anzahlTG;

                        //qDebug() << gidAr[gna];


                        //if(esE.contains(egE, Qt::CaseInsensitive))

                        //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                            //---------
                             if (
                                    (

                                         ~(ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseInsensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                            )
                                        )|
                                    (

                                        (ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseSensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                             )
                                        )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & ~(ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseInsensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                         )
                                     )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & (ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseSensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                         )
                                     )|
                                     (
                                      (ui->checkBoxGMEWO->isChecked())
                                      & (boundind != "")
                                      & (anzahlEG!=anzahlTG)
                                      )|
                                     (
                                      ~(ui->checkBoxGMEWO->isChecked())
                                      & (anzahlEG!=anzahlTG)
                                      )



                                )

//----------------------for List:-------------------
                                 //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                            {


                          //qDebug() <<       filterinG2;


                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }



                        //qDebug() << gidE;


                        QString strAnzEG = QString::number(anzahlEG);
                        QString strAnzTG = QString::number(anzahlTG);


                        //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                        ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));
                        //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                          ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));






                        //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                        //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                        //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


                        gna++;



                }


 //FilterG end

                        }




                      sna++;



                }

}
   }

//+++++not empty filter
   //(ui->checkBoxFilterGL2->isChecked())
  // & ~(ui->checkBoxFilterEmpty->isChecked())


  else if (

          (ui->checkBoxFilterG3->isChecked())

           )

   {

        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterE2=colArV[indxGF2][sna];
                //qDebug() << colFilterE2;


    //filterG2
                if (

                         (colFilterE2 != "")
                    )
              {




                //QString esE;
                //esE=esAr[sna];

                QString esE=colArV[GSESint][sna];

                 QString esEr;

                 //QString tsE;
                 //tsE=tsAr[sna];

                 QString tsE=colArV[GSTSint][sna];


                 QString tsEr;




                //remove line breaks
                if(
                        (ui->checkBoxGILB->isChecked())
                   )
                {
                    QString esEw= esE;
                    QString tsEw= tsE;
                    esEr = esEw.replace(QString("\\n"), QString(" "));
                    esEr = esEw.replace(QString("\\r"), QString(""));
                    tsEr = tsEw.replace(QString("\\n"), QString(" "));
                    tsEr = tsEw.replace(QString("\\r"), QString(""));
                    //qDebug() << colFilter;
                }
                else
                {
                     esEr = esE;
                     tsEr = tsE;
                }



                //qDebug() << sidAr[sna];



                int gna = 0;

                while (gna < gzeilen)

                //for (int na = 0; na = 10; na ++)

                      {
                        QString gidE;
                        gidE=gidAr[gna];

                        QString egE;
                        egE=egAr[gna];

                        QString tgE;
                        tgE=tgAr[gna];
                        //qDebug() << tgE;


                        //reg ex word boundaries
                        QString boundind;
                        if(
                              (ui->checkBoxGMEWO->isChecked())
                          )
                      {
                      QRegExp rxsid("\\b(" + egE + ")\\b");
                      rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                      rxsid.indexIn(esEr);
                      boundind = rxsid.cap(0);
                      //qDebug() <<  boundind;
                       }


                        //compare number of glossary terms in string



                        int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                        int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                        //qDebug() << "EG";
                        //qDebug() << anzahlEG;
                        //qDebug() << "TG";
                        //qDebug() << anzahlTG;

                        //qDebug() << gidAr[gna];


                        //if(esE.contains(egE, Qt::CaseInsensitive))

                        //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                            //---------
                             if (
                                    (

                                         ~(ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseInsensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                            )
                                        )|
                                    (

                                        (ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseSensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                             )
                                        )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & ~(ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseInsensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                         )
                                     )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & (ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseSensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                         )
                                     )|
                                     (
                                      (ui->checkBoxGMEWO->isChecked())
                                      & (boundind != "")
                                      & (anzahlEG!=anzahlTG)
                                      )|
                                     (
                                      ~(ui->checkBoxGMEWO->isChecked())
                                      & (anzahlEG!=anzahlTG)
                                      )



                                )

//----------------------for List:-------------------
                                 //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                            {


                          //qDebug() <<       filterinG2;


                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }



                        //qDebug() << gidE;


                        QString strAnzEG = QString::number(anzahlEG);
                        QString strAnzTG = QString::number(anzahlTG);


                        //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                        ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));
                        //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                          ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));






                        //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                        //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                        //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


                        gna++;



                }


 //FilterG end

                        }




                      sna++;



                }

}
   //+++++++++end not empty filter

  //---------empty
  // (ui->checkBoxFilterGL2->isChecked())
   //& ~(ui->checkBoxFilterG3->isChecked())

  else if (

           (ui->checkBoxFilterEmpty->isChecked())

           )

   {

        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterE2=colArV[indxGF2][sna];
                //qDebug() << colFilterE2;


    //filterG2
                if (

                         (colFilterE2 == "")
                    )
              {




                //QString esE;
                //esE=esAr[sna];

                QString esE=colArV[GSESint][sna];

                 QString esEr;

                 //QString tsE;
                 //tsE=tsAr[sna];

                 QString tsE=colArV[GSTSint][sna];


                 QString tsEr;




                //remove line breaks
                if(
                        (ui->checkBoxGILB->isChecked())
                   )
                {
                    QString esEw= esE;
                    QString tsEw= tsE;
                    esEr = esEw.replace(QString("\\n"), QString(" "));
                    esEr = esEw.replace(QString("\\r"), QString(""));
                    tsEr = tsEw.replace(QString("\\n"), QString(" "));
                    tsEr = tsEw.replace(QString("\\r"), QString(""));
                    //qDebug() << colFilter;
                }
                else
                {
                     esEr = esE;
                     tsEr = tsE;
                }



                //qDebug() << sidAr[sna];



                int gna = 0;

                while (gna < gzeilen)

                //for (int na = 0; na = 10; na ++)

                      {
                        QString gidE;
                        gidE=gidAr[gna];

                        QString egE;
                        egE=egAr[gna];

                        QString tgE;
                        tgE=tgAr[gna];
                        //qDebug() << tgE;


                        //reg ex word boundaries
                        QString boundind;
                        if(
                              (ui->checkBoxGMEWO->isChecked())
                          )
                      {
                      QRegExp rxsid("\\b(" + egE + ")\\b");
                      rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                      rxsid.indexIn(esEr);
                      boundind = rxsid.cap(0);
                      //qDebug() <<  boundind;
                       }


                        //compare number of glossary terms in string



                        int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                        int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                        //qDebug() << "EG";
                        //qDebug() << anzahlEG;
                        //qDebug() << "TG";
                        //qDebug() << anzahlTG;

                        //qDebug() << gidAr[gna];


                        //if(esE.contains(egE, Qt::CaseInsensitive))

                        //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                            //---------
                             if (
                                    (

                                         ~(ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseInsensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                            )
                                        )|
                                    (

                                        (ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseSensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                             )
                                        )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & ~(ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseInsensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                         )
                                     )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & (ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseSensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                         )
                                     )|
                                     (
                                      (ui->checkBoxGMEWO->isChecked())
                                      & (boundind != "")
                                      & (anzahlEG!=anzahlTG)
                                      )|
                                     (
                                      ~(ui->checkBoxGMEWO->isChecked())
                                      & (anzahlEG!=anzahlTG)
                                      )



                                )

//----------------------for List:-------------------
                                 //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                            {


                          //qDebug() <<       filterinG2;


                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }



                        //qDebug() << gidE;


                        QString strAnzEG = QString::number(anzahlEG);
                        QString strAnzTG = QString::number(anzahlTG);


                        //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                        ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));
                        //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);


                          ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));






                        //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                        //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                        //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


                        gna++;



                }


 //FilterG end

                        }




                      sna++;



                }

}

   //-----------empty end



   else if (
           ~(ui->checkBoxFilterGL2->isChecked())
           & ~(ui->checkBoxFilterEmpty->isChecked())
           & ~(ui->checkBoxFilterG3->isChecked())

           )
 {
   //qDebug() << "else";


        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                QString sidE=colArV[GSIDint][sna];


                //if()

                //qDebug() << colFilterE2;


    //filterG2






                //QString esE;
                //esE=esAr[sna];

                QString esE=colArV[GSESint][sna];

                 QString esEr;

                 //QString tsE;
                 //tsE=tsAr[sna];

                 QString tsE=colArV[GSTSint][sna];


                 QString tsEr;




                //remove line breaks
                if(
                        (ui->checkBoxGILB->isChecked())
                   )
                {
                    QString esEw= esE;
                    QString tsEw= tsE;
                    esEr = esEw.replace(QString("\\n"), QString(" "));
                    esEr = esEw.replace(QString("\\r"), QString(""));
                    tsEr = tsEw.replace(QString("\\n"), QString(" "));
                    tsEr = tsEw.replace(QString("\\r"), QString(""));
                    //qDebug() << colFilter;
                }
                else
                {
                     esEr = esE;
                     tsEr = tsE;
                }



                //qDebug() << sidAr[sna];



                int gna = 0;

                while (gna < gzeilen)

                //for (int na = 0; na = 10; na ++)

                      {
                        QString gidE;
                        gidE=gidAr[gna];

                        QString egE;
                        egE=egAr[gna];

                        QString tgE;
                        tgE=tgAr[gna];
                        //qDebug() << tgE;


                        //reg ex word boundaries
                        QString boundind;
                        if(
                              (ui->checkBoxGMEWO->isChecked())
                          )
                      {
                      QRegExp rxsid("\\b(" + egE + ")\\b");
                      rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                      rxsid.indexIn(esEr);
                      boundind = rxsid.cap(0);
                      //qDebug() <<  boundind;
                       }


                        //compare number of glossary terms in string



                        int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                        int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                        //qDebug() << "EG";
                        //qDebug() << anzahlEG;
                        //qDebug() << "TG";
                        //qDebug() << anzahlTG;

                        //qDebug() << gidAr[gna];


                        //if(esE.contains(egE, Qt::CaseInsensitive))

                        //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                            //---------
                             if (
                                    (

                                         ~(ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseInsensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                            )
                                        )|
                                    (

                                        (ui->checkBoxGMC->isChecked())&
                                        ~(ui->checkBoxGMEWO->isChecked())&
                                            (
                                         (esEr.contains(egE, Qt::CaseSensitive)) &
                                         ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                             )
                                        )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & ~(ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseInsensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseInsensitive))
                                         )
                                     )|
                                    (

                                    (ui->checkBoxGMEWO->isChecked())
                                    & (ui->checkBoxGMC->isChecked())
                                    & (boundind != "")
                                     &    (
                                      (esEr.contains(egE, Qt::CaseSensitive)) &
                                      ~(tsEr.contains(tgE, Qt::CaseSensitive))
                                         )
                                     )|
                                     (
                                      (ui->checkBoxGMEWO->isChecked())
                                      & (boundind != "")
                                      & (anzahlEG!=anzahlTG)
                                      )|
                                     (
                                      ~(ui->checkBoxGMEWO->isChecked())
                                      & (anzahlEG!=anzahlTG)
                                      )



                                )

//----------------------for List:-------------------
                                 //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                            {


                          //qDebug() <<       filterinG2;


                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }



                        //qDebug() << gidE;


                        QString strAnzEG = QString::number(anzahlEG);
                        QString strAnzTG = QString::number(anzahlTG);


                        //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                        ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                        ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                        //ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE + " (" + strAnzEG + ")"));


                        ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));



                        //ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE  + " (" + strAnzTG + ")"));


                          ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));



                           ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));







                        //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                        //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                        //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


                        gna++;



                }


 //FilterG end






                      sna++;



                }




//else end
   }

  connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));

}




void MainWindow::gclistslot()
{

    {
         ui->tableAll->clearContents();

         int indxGF2 = ui->comboBoxFilterG2->currentIndex();

         QString filterinG2 = ui->filterinputG2->text();


         QString tablenameS = ui->comboBoxtables->currentText();

         //qDebug() << tablenameS;

         QString strtable = "SELECT * FROM " + tablenameS;

         //qDebug() << strtable;

         QSqlQuery queryS(strtable);




         QString tablenameG = ui->comboBoxTableG->currentText();


        QString gtable = "SELECT * FROM " + tablenameG;

        //qDebug() << gtable;

        QSqlQuery queryG(gtable);

        //int KolZahl = queryg.record().count() + queryS.record().count();

        QString colnamesG = "SHOW COLUMNS FROM " + tablenameG;
        QString colnamesS = "SHOW COLUMNS FROM " + tablenameS;
                //qDebug() << colnames;

                QSqlQuery querycolS(colnamesS);
                QSqlQuery querycolG(colnamesG);

                int KolZahl = querycolS.size()+querycolG.size();

                //int RowZahlS = queryS.size();

                int KolZahlS = querycolS.size();



                ui->tableAll->setColumnCount(KolZahl+1);





                QList<QString> colAr;



                int ncolS=0;
                while (querycolS.next())
                    {
                    QString colS;
                    colS = querycolS.value(0).toString();
                    colAr.append(colS);
                    ncolS++;
                    //qDebug() << ncol;
                      }


                int ncolG=0;
                while (querycolG.next())
                    {
                    QString colG;
                    colG = querycolG.value(0).toString();
                    colAr.append(colG);
                    ncolG++;
                    //qDebug() << ncol;
                      }


                //ui->tableAll->setHorizontalHeaderLabels(colAr);

                 ui->tableAll->setHorizontalHeaderLabels(colAr << "Count");




        //tableGC->setColumnCount(queryS.record().count()+8);
        //tableGC->setRowCount(queryS.size()+queryG.size()+500);





               //ui->tableAll->setColumnCount(queryS.record().count()+8);

               //ui->tableAll->setRowCount(queryS.size()+queryG.size()+500);


     int GIDint = ui->comboBoxGID->currentIndex();
      int GESint = ui->comboBoxGES->currentIndex();
       int GTSint = ui->comboBoxGTS->currentIndex();

       QString GTSt = ui->comboBoxGTS->currentText();



       int GSIDint = ui->comboBoxGSID->currentIndex();
        int GSESint = ui->comboBoxGSES->currentIndex();
         int GSTSint = ui->comboBoxGSTS->currentIndex();


        QList<QString> gidAr;
        QList<QString> egAr;
        QList<QString> tgAr;

        QList<QString> sidAr;
        QList<QString> esAr;
        QList<QString> tsAr;

        int gzeilen =0;
        while (queryG.next())
        {

        //for (int index = 1; index =10000; index ++)

            QString eg;
            eg = queryG.value(GESint).toString();
            eg = eg.trimmed();

            if(eg!="")
            {

                    //egAr[index] = eg;
                    egAr.append(eg);


                    QString gid;
                    gid = queryG.value(GIDint).toString();

                    //gidAr[index] = gid;
                    gidAr.append(gid);
                    //qDebug() << gid;

                    //trimmed removes leading and trailing spaces
                    gzeilen++;


                    if(GTSt!="")
                    {

                            QString tg;
                            tg = queryG.value(GTSint).toString();
                            tg = tg.trimmed();

                            if(tg!="")
                            {
                            //tgAr[index] = tg;
                            tgAr.append(tg);
                            }

                            if(tg=="")
                            {
                                tgAr.append("[Missing Glossary Term]");
                            }

                     }
            }



        }

    //+++++++++++++vector+++++++++++++++++++++++++++++

        QVector<QStringList> colArV(KolZahlS);

        //qDebug() << "gzeilen";
        //qDebug() << gzeilen;
        //qDebug() << gidAr;
         //qDebug() << egAr;

             //qDebug() << indxC1;
             //qDebug() << indxC2;

                   //int index=0;
                   while (queryS.next())
                       //for(int index=0;index < RowZahlS; index++)
                   {

                       for (int coldisp = 0; coldisp < KolZahlS; coldisp++)
                       //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                       {

                           QString boxAll = queryS.value(coldisp).toString();
                           colArV[coldisp].append(boxAll);
                           //qDebug() << "index";
                           //qDebug() <<  index;
                           //qDebug() << "coldisp";
                           //qDebug() << coldisp;
                              //qDebug() << boxAll;

                          }

                   //index++;
                   }


        //+++++++++++++++++++++++++++++++++++++++

            /*while (queryS.next())
        {


                QString sid;
                sid = queryS.value(GSIDint).toString();
                sidAr.append(sid);


                QString es;
                es = queryS.value(GSESint).toString();
                esAr.append(es);
                //qDebug() << es;




                QString ts;
                ts = queryS.value(GSTSint).toString();
                tsAr.append(ts);



            }*/



    //+++++++++++++++++++++++++++++call string array

       if (
               (ui->checkBoxFilterGL2->isChecked())
               & ~(ui->checkBoxFilterG3->isChecked())
                & ~(ui->checkBoxFilterEmpty->isChecked())
          )

           if(filterinG2=="")
           {

               QMessageBox msgBox;
               msgBox.setText("Error: Search term missing.");
               msgBox.exec();

           }
       else

       {

            int zeilecount = 0;
            int sna = 0;
            while (sna < queryS.size())

            //for (int na = 0; na = 10; na ++)

                  {
                    //QString sidE;
                    //sidE=sidAr[sna];

                    QString sidE=colArV[GSIDint][sna];


                    //if()
                    QString colFilterE2=colArV[indxGF2][sna];
                    //qDebug() << "colFilterE2";
                      //qDebug() << colFilterE2;




        //filterG2
                    if (

                            (colFilterE2.contains(filterinG2, Qt::CaseInsensitive))
                        )
                  {




                    //QString esE;
                    //esE=esAr[sna];

                    QString esE=colArV[GSESint][sna];

                     QString esEr;

                     //QString tsE;
                     //tsE=tsAr[sna];

                     QString tsE=colArV[GSTSint][sna];


                     QString tsEr;




                    //remove line breaks
                    if(
                            (ui->checkBoxGILB->isChecked())
                       )
                    {
                        QString esEw= esE;
                        QString tsEw= tsE;
                        esEr = esEw.replace(QString("\\n"), QString(" "));
                        esEr = esEw.replace(QString("\\r"), QString(""));
                        tsEr = tsEw.replace(QString("\\n"), QString(" "));
                        tsEr = tsEw.replace(QString("\\r"), QString(""));
                        //qDebug() << colFilter;
                    }
                    else
                    {
                         esEr = esE;
                         tsEr = tsE;
                    }



                    //qDebug() << sidAr[sna];



                    int gna = 0;

                    while (gna < gzeilen)

                    //for (int na = 0; na = 10; na ++)

                          {
                            QString gidE;
                            gidE=gidAr[gna];

                            QString egE;
                            egE=egAr[gna];


     //glossary cell should not be empty

                            QString tgE;
                            if(GTSt!="")
                            {
                                        tgE=tgAr[gna];
                                        //qDebug() << tgE;
                             }

                            if(GTSt=="")
                            {
                               tgE="";
                            }


                            //reg ex word boundaries
                            QString boundind;
                            if(
                                  (ui->checkBoxGMEWO->isChecked())
                              )
                          {
                          QRegExp rxsid("\\b(" + egE + ")\\b");
                          rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                          rxsid.indexIn(esEr);
                          boundind = rxsid.cap(0);
                          //qDebug() <<  boundind;
                           }


                            //compare number of glossary terms in string



                            int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));

                            int anzahlTG;
                            if(tgE!="")
                            {
                            anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));
                            }
                            else
                                 anzahlTG =0;


                            //qDebug() << "EG";
                            //qDebug() << anzahlEG;
                            //qDebug() << "TG";
                            //qDebug() << anzahlTG;

                            //qDebug() << gidAr[gna];


                            //if(esE.contains(egE, Qt::CaseInsensitive))

                            //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                                //---------
                                 if (
                                        (

                                             ~(ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseInsensitive))


                                                )
                                            )|
                                        (

                                            (ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseSensitive))
                                                 )
                                            )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & ~(ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseInsensitive))
                                             )
                                         )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & (ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseSensitive))
                                             )
                                         )|
                                         (
                                          (ui->checkBoxGMEWO->isChecked())
                                          & (boundind != "")
                                          & (anzahlEG!=anzahlTG)
                                          )|
                                         (
                                          ~(ui->checkBoxGMEWO->isChecked())
                                          & (anzahlEG!=anzahlTG)
                                          )



                                    )

    //----------------------for List:-------------------
                                     //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                                {


                              //qDebug() <<       filterinG2;


                             ui->tableAll->setRowCount(zeilecount+1);

                            //while (callcol < KolZahl)
                            for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                            {
                            //QString gid;
                            //gid = queryG.value(GIDint).toString();

                                QString colEp=colArV[callcol][sna];

                                 QString su = colEp.left(500);

                                ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                            }



                            //qDebug() << gidE;


                            QString strAnzEG = QString::number(anzahlEG);
                            QString strAnzTG = QString::number(anzahlTG);


                            //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                            ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));
                            //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);

                                if(tgE!="")
                                {
                            ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                            //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                             ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                                }


                                if(tgE=="")
                                {

                             ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                                }









                            //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                            //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                            //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                            zeilecount++;
                            //qDebug() <<  zeilecount;

                              }


                            gna++;



                    }


     //FilterG end

                            }




                          sna++;



                    }

    }

    //+++++not empty filter
       //(ui->checkBoxFilterGL2->isChecked())
       //& ~(ui->checkBoxFilterEmpty->isChecked())

      else if (
                (ui->checkBoxFilterG3->isChecked())

               )

       {

            int zeilecount = 0;
            int sna = 0;
            while (sna < queryS.size())

            //for (int na = 0; na = 10; na ++)

                  {
                    //QString sidE;
                    //sidE=sidAr[sna];

                    QString sidE=colArV[GSIDint][sna];


                    //if()
                    QString colFilterE2=colArV[indxGF2][sna];
                    //qDebug() << colFilterE2;


        //filterG2
                    if (

                             (colFilterE2 != "")
                        )
                  {




                    //QString esE;
                    //esE=esAr[sna];

                    QString esE=colArV[GSESint][sna];

                     QString esEr;

                     //QString tsE;
                     //tsE=tsAr[sna];

                     QString tsE=colArV[GSTSint][sna];


                     QString tsEr;




                    //remove line breaks
                    if(
                            (ui->checkBoxGILB->isChecked())
                       )
                    {
                        QString esEw= esE;
                        QString tsEw= tsE;
                        esEr = esEw.replace(QString("\\n"), QString(" "));
                        esEr = esEw.replace(QString("\\r"), QString(""));
                        tsEr = tsEw.replace(QString("\\n"), QString(" "));
                        tsEr = tsEw.replace(QString("\\r"), QString(""));
                        //qDebug() << colFilter;
                    }
                    else
                    {
                         esEr = esE;
                         tsEr = tsE;
                    }



                    //qDebug() << sidAr[sna];



                    int gna = 0;

                    while (gna < gzeilen)

                    //for (int na = 0; na = 10; na ++)

                          {
                            QString gidE;
                            gidE=gidAr[gna];

                            QString egE;
                            egE=egAr[gna];

                            QString tgE;
                            if(GTSt!="")
                            {
                                        tgE=tgAr[gna];
                                        //qDebug() << tgE;
                             }

                            if(GTSt=="")
                            {
                               tgE="";
                            }



                            //reg ex word boundaries
                            QString boundind;
                            if(
                                  (ui->checkBoxGMEWO->isChecked())
                              )
                          {
                          QRegExp rxsid("\\b(" + egE + ")\\b");
                          rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                          rxsid.indexIn(esEr);
                          boundind = rxsid.cap(0);
                          //qDebug() <<  boundind;
                           }


                            //compare number of glossary terms in string



                            int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                            int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                            //qDebug() << "EG";
                            //qDebug() << anzahlEG;
                            //qDebug() << "TG";
                            //qDebug() << anzahlTG;

                            //qDebug() << gidAr[gna];


                            //if(esE.contains(egE, Qt::CaseInsensitive))

                            //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                                //---------
                                 if (
                                        (

                                             ~(ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseInsensitive))
                                                )
                                            )|
                                        (

                                            (ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseSensitive))
                                                 )
                                            )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & ~(ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseInsensitive))
                                             )
                                         )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & (ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseSensitive))
                                             )
                                         )|
                                         (
                                          (ui->checkBoxGMEWO->isChecked())
                                          & (boundind != "")
                                          & (anzahlEG!=anzahlTG)
                                          )|
                                         (
                                          ~(ui->checkBoxGMEWO->isChecked())
                                          & (anzahlEG!=anzahlTG)
                                          )



                                    )

    //----------------------for List:-------------------
                                     //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                                {


                              //qDebug() <<       filterinG2;


                             ui->tableAll->setRowCount(zeilecount+1);

                            //while (callcol < KolZahl)
                            for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                            {
                            //QString gid;
                            //gid = queryG.value(GIDint).toString();

                                QString colEp=colArV[callcol][sna];

                                 QString su = colEp.left(500);

                                ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                            }



                            //qDebug() << gidE;


                            QString strAnzEG = QString::number(anzahlEG);
                            QString strAnzTG = QString::number(anzahlTG);


                            //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                            ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                            //ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE + " (" + strAnzEG + ")"));
                            //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);
                             ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));

                            //ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE  + " (" + strAnzTG + ")"));
                            //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                            //
                            if(tgE!="")
                            {
                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                         ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }


                            if(tgE=="")
                            {

                         ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }



                            //






                            //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                            //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                            //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                            zeilecount++;
                            //qDebug() <<  zeilecount;

                              }


                            gna++;



                    }


     //FilterG end

                            }




                          sna++;



                    }

    }
       //+++++++++end not empty filter

      //---------empty
       //(ui->checkBoxFilterGL2->isChecked())
       //& ~(ui->checkBoxFilterG3->isChecked())


      else if (               
              (ui->checkBoxFilterEmpty->isChecked())

               )

       {

            int zeilecount = 0;
            int sna = 0;
            while (sna < queryS.size())

            //for (int na = 0; na = 10; na ++)

                  {
                    //QString sidE;
                    //sidE=sidAr[sna];

                    QString sidE=colArV[GSIDint][sna];


                    //if()
                    QString colFilterE2=colArV[indxGF2][sna];
                    //qDebug() << colFilterE2;


        //filterG2
                    if (

                             (colFilterE2 == "")
                        )
                  {




                    //QString esE;
                    //esE=esAr[sna];

                    QString esE=colArV[GSESint][sna];

                     QString esEr;

                     //QString tsE;
                     //tsE=tsAr[sna];

                     QString tsE=colArV[GSTSint][sna];


                     QString tsEr;




                    //remove line breaks
                    if(
                            (ui->checkBoxGILB->isChecked())
                       )
                    {
                        QString esEw= esE;
                        QString tsEw= tsE;
                        esEr = esEw.replace(QString("\\n"), QString(" "));
                        esEr = esEw.replace(QString("\\r"), QString(""));
                        tsEr = tsEw.replace(QString("\\n"), QString(" "));
                        tsEr = tsEw.replace(QString("\\r"), QString(""));
                        //qDebug() << colFilter;
                    }
                    else
                    {
                         esEr = esE;
                         tsEr = tsE;
                    }



                    //qDebug() << sidAr[sna];



                    int gna = 0;

                    while (gna < gzeilen)

                    //for (int na = 0; na = 10; na ++)

                          {
                            QString gidE;
                            gidE=gidAr[gna];

                            QString egE;
                            egE=egAr[gna];



                             QString tgE;
                            if(GTSt!="")
                        {


                                tgE=tgAr[gna];
                             //qDebug() << tgE;
                       }


                            //reg ex word boundaries
                            QString boundind;
                            if(
                                  (ui->checkBoxGMEWO->isChecked())
                              )
                          {
                          QRegExp rxsid("\\b(" + egE + ")\\b");
                          rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                          rxsid.indexIn(esEr);
                          boundind = rxsid.cap(0);
                          //qDebug() <<  boundind;
                           }


                            //compare number of glossary terms in string



                            int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                            int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));

                            //qDebug() << "EG";
                            //qDebug() << anzahlEG;
                            //qDebug() << "TG";
                            //qDebug() << anzahlTG;

                            //qDebug() << gidAr[gna];


                            //if(esE.contains(egE, Qt::CaseInsensitive))

                            //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                                //---------
                                 if (
                                        (

                                             ~(ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseInsensitive))
                                                )
                                            )|
                                        (

                                            (ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseSensitive))
                                                 )
                                            )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & ~(ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseInsensitive))
                                             )
                                         )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & (ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseSensitive))
                                             )
                                         )|
                                         (
                                          (ui->checkBoxGMEWO->isChecked())
                                          & (boundind != "")
                                          & (anzahlEG!=anzahlTG)
                                          )|
                                         (
                                          ~(ui->checkBoxGMEWO->isChecked())
                                          & (anzahlEG!=anzahlTG)
                                          )



                                    )

    //----------------------for List:-------------------
                                     //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                                {


                              //qDebug() <<       filterinG2;


                             ui->tableAll->setRowCount(zeilecount+1);

                            //while (callcol < KolZahl)
                            for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                            {
                            //QString gid;
                            //gid = queryG.value(GIDint).toString();

                                QString colEp=colArV[callcol][sna];

                                 QString su = colEp.left(500);

                                ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                            }



                            //qDebug() << gidE;


                            QString strAnzEG = QString::number(anzahlEG);
                            QString strAnzTG = QString::number(anzahlTG);


                            //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                            ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                            //ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE + " (" + strAnzEG + ")"));
                            //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);
                             ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));

                            //ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE  + " (" + strAnzTG + ")"));
                            //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);


                            //
                            if(tgE!="")
                            {
                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                         ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }


                            if(tgE=="")
                            {

                         ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }


                            //






                            //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                            //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                            //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                            zeilecount++;
                            //qDebug() <<  zeilecount;

                              }


                            gna++;



                    }


     //FilterG end

                            }




                          sna++;



                    }

    }

       //-----------empty end



       else if (
               ~(ui->checkBoxFilterGL2->isChecked())
               & ~(ui->checkBoxFilterEmpty->isChecked())
               & ~(ui->checkBoxFilterG3->isChecked())
               )
     {
       //qDebug() << "else";


            int zeilecount = 0;
            int sna = 0;
            while (sna < queryS.size())

            //for (int na = 0; na = 10; na ++)

                  {
                    //QString sidE;
                    //sidE=sidAr[sna];

                    QString sidE=colArV[GSIDint][sna];


                     QString esE=colArV[GSESint][sna];

                     QString esEr;

                     QString tsE=colArV[GSTSint][sna];

                     QString tsEr;




                    //remove line breaks
                    if(
                            (ui->checkBoxGILB->isChecked())
                       )
                    {
                        QString esEw= esE;
                        QString tsEw= tsE;
                        esEr = esEw.replace(QString("\\n"), QString(" "));
                        esEr = esEw.replace(QString("\\r"), QString(""));
                        tsEr = tsEw.replace(QString("\\n"), QString(" "));
                        tsEr = tsEw.replace(QString("\\r"), QString(""));
                        //qDebug() << colFilter;
                    }
                    else
                    {
                         esEr = esE;
                         tsEr = tsE;
                    }




                    int gna = 0;

                    //while (gna < queryG.size())
                        while (gna < gzeilen)

                    //for (int na = 0; na = 10; na ++)

                          {
                            QString gidE;
                            gidE=gidAr[gna];


                            QString egE;
                            QString egEcheck;
                            egEcheck=egAr[gna];
                            if(egEcheck!="")
                            {
                              egE=egAr[gna];
                            }
                            if(egEcheck=="")
                            {
                              egE="[Error: Source Term Missing]";
                            }

                            //qDebug() << egE;



                            //
                            QString tgE;
                            if(GTSt!="")
                            {
                                        tgE=tgAr[gna];
                                        //qDebug() << tgE;
                             }

                            if(GTSt=="")
                            {
                               tgE="";
                            }





                            //reg ex word boundaries
                            QString boundind;
                            if(
                                  (ui->checkBoxGMEWO->isChecked())
                              )
                          {
                          QRegExp rxsid("\\b(" + egE + ")\\b");
                          rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                          rxsid.indexIn(esEr);
                          boundind = rxsid.cap(0);
                          //qDebug() <<  boundind;
                           }


                            //compare number of glossary terms in string



                            int anzahlEG = (esEr.count(egE, Qt::CaseInsensitive));
                            //int anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));
                            int anzahlTG;
                            if(tgE!="")
                            {
                            anzahlTG = (tsEr.count(tgE, Qt::CaseInsensitive));
                            }
                            else
                                 anzahlTG =0;

                            //qDebug() << "EG";
                            //qDebug() << anzahlEG;
                            //qDebug() << "TG";
                            //qDebug() << anzahlTG;

                            //qDebug() << gidAr[gna];


                            //if(esE.contains(egE, Qt::CaseInsensitive))

                            //if((esEr.contains(egE, Qt::CaseInsensitive)) & ~(tsEr.contains(tgE, Qt::CaseInsensitive)))



                                //---------
                                 if (
                                        (

                                             ~(ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseInsensitive))
                                                )
                                            )|
                                        (

                                            (ui->checkBoxGMC->isChecked())&
                                            ~(ui->checkBoxGMEWO->isChecked())&
                                                (
                                             (esEr.contains(egE, Qt::CaseSensitive))
                                                 )
                                            )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & ~(ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseInsensitive))
                                             )
                                         )|
                                        (

                                        (ui->checkBoxGMEWO->isChecked())
                                        & (ui->checkBoxGMC->isChecked())
                                        & (boundind != "")
                                         &    (
                                          (esEr.contains(egE, Qt::CaseSensitive))
                                             )
                                         )|
                                         (
                                          (ui->checkBoxGMEWO->isChecked())
                                          & (boundind != "")
                                          & (anzahlEG!=anzahlTG)
                                          )|
                                         (
                                          ~(ui->checkBoxGMEWO->isChecked())
                                          & (anzahlEG!=anzahlTG)
                                          )



                                    )

    //----------------------for List:-------------------
                                     //if((boundeg != "") && (esEr.contains(egE, Qt::CaseInsensitive)))
                                {


                              //qDebug() <<       filterinG2;


                             ui->tableAll->setRowCount(zeilecount+1);

                            //while (callcol < KolZahl)
                            for (int callcol = 0; (callcol < KolZahlS); callcol ++)
                                            {
                            //QString gid;
                            //gid = queryG.value(GIDint).toString();

                                QString colEp=colArV[callcol][sna];

                                QString su = colEp.left(500);

                                ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));
                                /* QTableWidgetItem *item;
                                item = new QTableWidgetItem(su);
                                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                                ui->tableAll->setItem(zeilecount,callcol,item);*/


                                            }

                              //QString xy=colArV[1][sna];

                                //qDebug() << xy;

                          //qDebug() << gidE;
                           //qDebug() << egE;



                            QString strAnzEG = QString::number(anzahlEG);
                            QString strAnzTG = QString::number(anzahlTG);


                            //ui->tableAll->item(zeilecount,0)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+0,new QTableWidgetItem(gidE));
                            ui->tableAll->item(zeilecount,KolZahlS+0)->setBackground(Qt::red);

                            //ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE + " (" + strAnzEG + ")"));
                            //ui->tableAll->item(zeilecount,KolZahlS+2)->setBackground(Qt::red);

                            ui->tableAll->setItem(zeilecount,KolZahlS+1,new QTableWidgetItem(egE));




                            if(tgE!="")
                            {
                        ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(tgE));
                        //ui->tableAll->item(zeilecount,KolZahlS+3)->setBackground(Qt::red);

                         ui->tableAll->setItem(zeilecount,KolZahlS+3,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }


                            if(tgE=="")
                            {

                         ui->tableAll->setItem(zeilecount,KolZahlS+2,new QTableWidgetItem(strAnzEG  + " : " + strAnzTG));

                            }






                            //ui->tableAll->setItem(zeilecount,3,new QTableWidgetItem(sidE));

                            //ui->tableAll->setItem(zeilecount,4,new QTableWidgetItem(esE));

                            //ui->tableAll->setItem(zeilecount,5,new QTableWidgetItem(tsE));

                            zeilecount++;
                            //qDebug() <<  zeilecount;

                              }


                            gna++;


                    }


     //FilterG end






                          sna++;



                    }




    //else end
       }

      connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));

    }



}

//++++++++++++++++++++++GCSlot end+++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++Filterboxlogic
//GlossaryFilter
void MainWindow::FilterGL2slot()
{
    if (     (ui->checkBoxFilterGL2->isChecked()))
    {
        (ui->checkBoxFilterG3->setChecked(false));
        (ui->checkBoxFilterEmpty->setChecked(false));

    }
}


void MainWindow::FilterG3slot()
{
    if (     (ui->checkBoxFilterG3->isChecked()))
    {
        (ui->checkBoxFilterGL2->setChecked(false));
        (ui->checkBoxFilterEmpty->setChecked(false));

    }
}


void MainWindow::FilterEmptyslot()
{
    if (     (ui->checkBoxFilterEmpty->isChecked()))
    {
        (ui->checkBoxFilterGL2->setChecked(false));
        (ui->checkBoxFilterG3->setChecked(false));

    }
}

//EQFilter

void MainWindow::FilterEQslot()
{
    if (     (ui->checkBoxFilterEQ->isChecked()))
    {
        (ui->checkBoxFilterEQNE->setChecked(false));
        (ui->checkBoxFilterEmptyEQ->setChecked(false));

    }
}


void MainWindow::FilterEQNEslot()
{
    if (     (ui->checkBoxFilterEQNE->isChecked()))
    {
        (ui->checkBoxFilterEQ->setChecked(false));
        (ui->checkBoxFilterEmptyEQ->setChecked(false));

    }
}


void MainWindow::FilterEmptyEQslot()
{
    if (     (ui->checkBoxFilterEmptyEQ->isChecked()))
    {
        (ui->checkBoxFilterEQ->setChecked(false));
        (ui->checkBoxFilterEQNE->setChecked(false));

    }
}
//2nd filter of main filter



void MainWindow::Filter2slot()
{
    if (     (ui->checkBoxFilter2->isChecked()))
    {
        (ui->checkBoxFilter3->setChecked(false));


    }
}


void MainWindow::Filter3slot()
{
    if (     (ui->checkBoxFilter3->isChecked()))
    {
        (ui->checkBoxFilter2->setChecked(false));


    }
}





//FiterSettings
void MainWindow::Wildcardslot()
{
    if (     (ui->checkBoxWild->isChecked()))
    {
        (ui->checkBoxMEWO->setChecked(false));
        (ui->checkBoxMESO->setChecked(false));

    }
}

void MainWindow::MEWOslot()
    {
        if (     (ui->checkBoxMEWO->isChecked()))
        {
            (ui->checkBoxMESO->setChecked(false));
            (ui->checkBoxWild->setChecked(false));

        }
    }


void MainWindow::MESOslot()
    {
        if (     (ui->checkBoxMESO->isChecked()))
        {
            (ui->checkBoxMEWO->setChecked(false));
            (ui->checkBoxWild->setChecked(false));

        }
    }
//same for SearchDB

void MainWindow::WildcardslotSDB()
{
    if (     (ui->checkBoxWildSDB->isChecked()))
    {
        (ui->checkBoxMEWOSDB->setChecked(false));
        (ui->checkBoxMESOSDB->setChecked(false));

    }
}

void MainWindow::MEWOslotSDB()
    {
        if (     (ui->checkBoxMEWOSDB->isChecked()))
        {
            (ui->checkBoxMESOSDB->setChecked(false));
            (ui->checkBoxWildSDB->setChecked(false));

        }
    }


void MainWindow::MESOslotSDB()
    {
        if (     (ui->checkBoxMESOSDB->isChecked()))
        {
            (ui->checkBoxMEWOSDB->setChecked(false));
            (ui->checkBoxWildSDB->setChecked(false));

        }
    }




//save drop down selection
void MainWindow::RangeBoxslot()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString colnames = "SHOW COLUMNS FROM " + tablenameS;
           //qDebug() << colnames;

           QSqlQuery querycol(colnames);

           QList<QString> colAr;

           int ncol=0;
           while (querycol.next())
               {
               QString col;
               col = querycol.value(0).toString();
               colAr.append(col);
               ncol++;
               //qDebug() << ncol;
                 }

           //for admin db tab
         ui->comboBoxRenameC->clear();
         ui->comboBoxRenameC->addItems(colAr);
         ui->comboBoxRenameC->setCurrentIndex(0);

         ui->comboBoxAddC->clear();
         ui->comboBoxAddC->addItems(colAr);
         ui->comboBoxAddC->setCurrentIndex(0);

         ui->comboBoxAddRows->clear();
         ui->comboBoxAddRows->addItems(colAr);
         ui->comboBoxAddRows->setCurrentIndex(0);

         ui->comboBoxMoveC->clear();
         ui->comboBoxMoveC->addItems(colAr);
         ui->comboBoxMoveC->setCurrentIndex(0);

         ui->comboBoxMoveCRef->clear();
         ui->comboBoxMoveCRef->addItems(colAr);
         ui->comboBoxMoveCRef->setCurrentIndex(0);

         ui->comboBoxCopyC->clear();
         ui->comboBoxCopyC->addItems(colAr);
         ui->comboBoxCopyC->setCurrentIndex(0);

         ui->comboBoxCopyCRef->clear();
         ui->comboBoxCopyCRef->addItems(colAr);
         ui->comboBoxCopyCRef->setCurrentIndex(0);

         ui->comboBoxFrequ->clear();
         ui->comboBoxFrequ->addItems(colAr);
         ui->comboBoxFrequ->setCurrentIndex(1);


         ui->comboBoxCSVziel->clear();
         ui->comboBoxCSVziel->addItems(colAr);
         ui->comboBoxCSVziel->setCurrentIndex(0);

         ui->comboBoxCSVsid->clear();
         ui->comboBoxCSVsid->addItems(colAr);
         ui->comboBoxCSVsid->setCurrentIndex(0);

         ui->comboBoximpdbziel->clear();
         ui->comboBoximpdbziel->addItems(colAr);
         ui->comboBoximpdbziel->setCurrentIndex(0);

         ui->comboBoxtxtExport->clear();
         ui->comboBoxtxtExport->addItems(colAr);
         ui->comboBoxtxtExport->setCurrentIndex(0);

         ui->comboBoxtxtsid->clear();
         ui->comboBoxtxtsid->addItems(colAr);
         ui->comboBoxtxtsid->setCurrentIndex(0);

         ui-> comboBoxtxtziel->clear();
         ui-> comboBoxtxtziel->addItems(colAr);
         ui-> comboBoxtxtziel->setCurrentIndex(0);

         ui->comboBoxGCziel->clear();
         ui->comboBoxGCziel->addItems(colAr);
         ui->comboBoxGCziel->setCurrentIndex(0);

         ui->comboBoxCreateID->clear();
         ui->comboBoxCreateID->addItems(colAr);
         ui->comboBoxCreateID->setCurrentIndex(0);



         ui->comboBoxGSID->clear();
         ui->comboBoxGSID->addItems(colAr);
         ui->comboBoxGSID->setCurrentIndex(0);

         ui->comboBoxGSES->clear();
         ui->comboBoxGSES->addItems(colAr);
         ui->comboBoxGSES->setCurrentIndex(1);

         ui->comboBoxGSTS->clear();
         ui->comboBoxGSTS->addItems(colAr);
         ui->comboBoxGSTS->setCurrentIndex(2);

         ui->comboBoxFilter2->clear();
         ui->comboBoxFilter2->addItems(colAr);
         ui->comboBoxFilter2->setCurrentIndex(0);


         ui->comboBoxFilterG2->clear();
         ui->comboBoxFilterG2->addItems(colAr);
         ui->comboBoxFilterG2->setCurrentIndex(0);

         ui->comboBoxEQES->clear();
         ui->comboBoxEQES->addItems(colAr);
         ui->comboBoxEQES->setCurrentIndex(1);

         ui->comboBoxEQTS->clear();
         ui->comboBoxEQTS->addItems(colAr);
         ui->comboBoxEQTS->setCurrentIndex(2);





         QFile Filter2file(tablenameS + "comboBoxFilter2");
                 if (!Filter2file.open(QIODevice::ReadOnly | QIODevice::Text))
                     return;
                 QTextStream inFilter2(&Filter2file);
                 while (!inFilter2.atEnd())
                                     {
                     QString keepselectFilter2 = inFilter2.readLine();
                     //qDebug() << keepselectFilter2;
                     if(~(keepselectFilter2.isEmpty()))
                     {
                         ui->comboBoxFilter2->clear();
                         //colAr.append("-");
                         ui->comboBoxFilter2->addItems(colAr);
                     int indexFilter2 = ui->comboBoxFilter2->findText(keepselectFilter2);
                     ui->comboBoxFilter2->setCurrentIndex(indexFilter2);
                     }

                                      }


                 QFile FilterG2file(tablenameS + "comboBoxFilterG2");
                         if (!FilterG2file.open(QIODevice::ReadOnly | QIODevice::Text))
                             return;
                         QTextStream inFilterG2(&FilterG2file);
                         while (!inFilterG2.atEnd())
                                             {
                             QString keepselectFilterG2 = inFilterG2.readLine();
                             //qDebug() << keepselectFilter2;
                             if(~(keepselectFilterG2.isEmpty()))
                             {
                                 ui->comboBoxFilterG2->clear();
                                 //colAr.append("-");
                                 ui->comboBoxFilterG2->addItems(colAr);
                             int indexFilterG2 = ui->comboBoxFilterG2->findText(keepselectFilterG2);
                             ui->comboBoxFilterG2->setCurrentIndex(indexFilterG2);
                             }

                                              }







//+++++++++++++++++++EQ




         QFile hEQESfile(tablenameS + "comboBoxEQES");
                 if (!hEQESfile.open(QIODevice::ReadOnly | QIODevice::Text))
                     return;
                 QTextStream inEQES(&hEQESfile);
                 while (!inEQES.atEnd())
                                     {
                     QString keepselectEQES = inEQES.readLine();
                     //qDebug() << keepselectID;
                     if(~(keepselectEQES.isEmpty()))
                     {
                         ui->comboBoxEQES->clear();
                         //colAr.append("-");
                         ui->comboBoxEQES->addItems(colAr);
                     int indexEQES = ui->comboBoxEQES->findText(keepselectEQES);
                     ui->comboBoxEQES->setCurrentIndex(indexEQES);
                     }

                                      }


                 QFile EQTSfile(tablenameS + "comboBoxEQTS");
                         if (!EQTSfile.open(QIODevice::ReadOnly | QIODevice::Text))
                             return;
                         QTextStream inEQTS(&EQTSfile);
                         while (!inEQTS.atEnd())
                                             {
                             QString keepselectEQTS = inEQTS.readLine();
                             //qDebug() << keepselectID;
                             if(~(keepselectEQTS.isEmpty()))
                             {
                                 ui->comboBoxEQTS->clear();
                                 //colAr.append("-");
                                 ui->comboBoxEQTS->addItems(colAr);
                             int indexEQTS = ui->comboBoxEQTS->findText(keepselectEQTS);
                             ui->comboBoxEQTS->setCurrentIndex(indexEQTS);
                             }

                                              }











//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
         //+++++++++Glossary tab filters (PUT ALL OTHER STUFF ABOVE THIS, will not work if below, if no Glossary table is selected)



         QFile hGSIDfile(tablenameS + "comboBoxGSID");
                 if (!hGSIDfile.open(QIODevice::ReadOnly | QIODevice::Text))
                     return;
                 QTextStream inGSID(&hGSIDfile);
                 while (!inGSID.atEnd())
                                     {
                     QString keepselectGSID = inGSID.readLine();
                     //qDebug() << keepselectID;
                     if(~(keepselectGSID.isEmpty()))
                     {
                         ui->comboBoxGSID->clear();
                         //colAr.append("-");
                         ui->comboBoxGSID->addItems(colAr);
                     int indexGSID = ui->comboBoxGSID->findText(keepselectGSID);
                     ui->comboBoxGSID->setCurrentIndex(indexGSID);
                     }

                                      }




                 //++++++++++++++++++++++++++++++


                  QFile hGSESfile(tablenameS + "comboBoxGSES");
                          if (!hGSESfile.open(QIODevice::ReadOnly | QIODevice::Text))
                              return;
                          QTextStream inGSES(&hGSESfile);
                          while (!inGSES.atEnd())
                                              {
                              QString keepselectGSES = inGSES.readLine();
                              //qDebug() << keepselectID;
                              if(~(keepselectGSES.isEmpty()))
                              {
                                  ui->comboBoxGSES->clear();
                                  //colAr.append("-");
                                  ui->comboBoxGSES->addItems(colAr);
                              int indexGSES = ui->comboBoxGSES->findText(keepselectGSES);
                              ui->comboBoxGSES->setCurrentIndex(indexGSES);
                              }

                                               }



                 //++++++++++++++++++++++++++++++++++++++++



                  QFile hGSTSfile(tablenameS + "comboBoxGSTS");
                          if (!hGSTSfile.open(QIODevice::ReadOnly | QIODevice::Text))
                              return;
                          QTextStream inGSTS(&hGSTSfile);
                          while (!inGSTS.atEnd())
                                              {
                              QString keepselectGSTS = inGSTS.readLine();
                              //qDebug() << keepselectID;
                              if(~(keepselectGSTS.isEmpty()))
                              {
                                  ui->comboBoxGSTS->clear();
                                  //colAr.append("-");
                                  ui->comboBoxGSTS->addItems(colAr);
                              int indexGSTS = ui->comboBoxGSTS->findText(keepselectGSTS);
                              ui->comboBoxGSTS->setCurrentIndex(indexGSTS);
                              }

                                               }

//---------------------------


}



void MainWindow::morecombosaveslots()
{
    QString tablenameS = ui->comboBoxtables->currentText();

     QString colnames = "SHOW COLUMNS FROM " + tablenameS;
           //qDebug() << colnames;

           QSqlQuery querycol(colnames);

           QList<QString> colAr;

           int ncol=0;
           while (querycol.next())
               {
               QString col;
               col = querycol.value(0).toString();
               colAr.append(col);
               ncol++;
               //qDebug() << ncol;
                 }

    ui->comboBoxFilterEQ->clear();
    ui->comboBoxFilterEQ->addItems(colAr);
    ui->comboBoxFilterEQ->setCurrentIndex(0);

QFile FilterEQfile(tablenameS + "comboBoxFilterEQ");
        if (!FilterEQfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QTextStream inFilterEQ(&FilterEQfile);
        while (!inFilterEQ.atEnd())
                            {
            QString keepselectFilterEQ = inFilterEQ.readLine();
            //qDebug() << keepselectID;
            if(~(keepselectFilterEQ.isEmpty()))
            {
                ui->comboBoxFilterEQ->clear();
                //colAr.append("-");
                ui->comboBoxFilterEQ->addItems(colAr);
            int indexFilterEQ = ui->comboBoxFilterEQ->findText(keepselectFilterEQ);
            ui->comboBoxFilterEQ->setCurrentIndex(indexFilterEQ);
            }

                             }
}



void MainWindow::filterslotS()
{
     ui->tableAll->clearContents();  


    QString c1text = ui->comboBoxC1->currentText();
    QString c2text = ui->comboBoxC2->currentText();



    int indxC1 = ui->comboBoxC1->currentIndex();
    int indxC2 = ui->comboBoxC2->currentIndex();

    int indxF2 = ui->comboBoxFilter2->currentIndex();



    if(indxC1 > indxC2)
    {
        QMessageBox msgBox;
        msgBox.setText("Error: Negative Range.");
        msgBox.exec();
    }

    if(
            (indxC1<0)||(indxC2<0)
       )
    {
        QMessageBox msgBox;
        msgBox.setText("Error: Range-Limit missing.");
        msgBox.exec();
        return;
    }

    QString filterin = ui->filterinput->text();
     QString filterin2 = ui->filterinput2->text();



      ui->lineEditMark->setText(filterin);

    //qDebug() << filterin;

    QString tablenameS = ui->comboBoxtables->currentText();

        QString strtable = "SELECT * FROM " + tablenameS;

        //qDebug() << strtable;

        QSqlQuery queryS(strtable);
        // QSqlQuery querytables("SHOW TABLES");

         QString colnames = "SHOW COLUMNS FROM " + tablenameS;
         //qDebug() << colnames;

         QSqlQuery querycol(colnames);

       int KolZahl = querycol.size();


       //tableSfilter->setColumnCount(queryS.record().count()+8);
       //tableSfilter->setRowCount(queryS.size()+500);

       ui->tableAll->setColumnCount(KolZahl);
       //ui->tableAll->setRowCount(queryS.size()+50000);

       //qDebug() << KolZahl;
       QVector<QStringList> colArV(KolZahl);

       //qDebug() << indxC1;
       //qDebug() << indxC2;

             int index=0;
             while (queryS.next())
             {

                 for (int coldisp = 0; coldisp < querycol.size(); coldisp++)
                 //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                 {

                     QString boxAll = queryS.value(coldisp).toString();
                     colArV[coldisp].append(boxAll);
                     /*qDebug() << "index";
                     qDebug() <<  index;
                     qDebug() << "coldisp";
                     qDebug() << coldisp;
                        qDebug() << boxAll;*/

                    }

             index++;
             }

   //+++++++++++++++++++++++++++++call string array

   int kolnummer=indxC1;

   //while (querycol.next())
   while (kolnummer < indxC2+1)

   {

       int zeilecountS = 0;
       int itemnummer = 0;
       while (itemnummer < queryS.size())

           //for (int na = 0; na = 10; na ++)

        {
                   QString colFilterE=colArV[kolnummer][itemnummer];
                   QString colFilterE2=colArV[indxF2][itemnummer];

                   QString colFilter;
                   int mesoInS;
                   int mesoSens;
                   QString boundind;
                   QRegExp rxtswvCI(filterin);
                   QRegExp rxtswvCS(filterin);
                   //QString colE1=colArV[2][itemnummer];

                                 //qDebug() << colFilter;

                                 //remove line breaks
                                if(                                     
                                        (ui->checkBoxILB->isChecked())

                                   )
                                {

                                    colFilter = colFilterE.replace(QString("\\n"), QString(" "));
                                    colFilter = colFilterE.replace(QString("\\r"), QString(""));
                                    //qDebug() << colFilter;
                                }

                                else
                                {
                                    colFilter=colFilterE;
                                }










                                  //match entire string
                                if(
                                       (ui->checkBoxMESO->isChecked())
                                   )
                                {
                                mesoInS = QString::compare(colFilter, filterin, Qt::CaseInsensitive);
                                mesoSens = QString::compare(colFilter, filterin, Qt::CaseSensitive);
                                }


                                    //MATCH ENTIRE WORD ONLY
                                if(
                                        (ui->checkBoxMEWO->isChecked())
                                    )
                                {

                                QRegExp rxsid("\\b(" + filterin + ")\\b");
                                rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                                rxsid.indexIn(colFilter);
                                boundind = rxsid.cap(0);
                                //qDebug() <<  boundind;
                                 }

                                //Wildcard
                                if(
                                        (ui->checkBoxWild->isChecked())
                                    )
                                {
                                    rxtswvCI.setCaseSensitivity(Qt::CaseInsensitive);
                                    rxtswvCI.setPatternSyntax(QRegExp::Wildcard);
                                    rxtswvCS.setCaseSensitivity(Qt::CaseSensitive);
                                    rxtswvCS.setPatternSyntax(QRegExp::Wildcard);
                                 }


                                 if (
                                         (
                                               ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                             ~(ui->checkBoxMC->isChecked())&
                                              ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseInsensitive))
                                             )|

                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                             (ui->checkBoxMC->isChecked())&
                                            ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseSensitive))
                                             )|

                                            (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                             (ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMC->isChecked())&                                            
                                             (mesoInS==0)
                                             )|
                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                          (ui->checkBoxMESO->isChecked())&
                                          (ui->checkBoxMC->isChecked())&                                          
                                          (mesoSens==0)
                                          )|
                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                         (ui->checkBoxMEWO->isChecked())
                                         & ~(ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseInsensitive))
                                          )|
                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                         (ui->checkBoxMEWO->isChecked())
                                         & (ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseSensitive))
                                          )|
                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                         ~(ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCI.exactMatch(colFilter))
                                          )|
                                         (
                                              ~(ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxFilter3->isChecked())&
                                         (ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCS.exactMatch(colFilter))
                                          )|

                                    //checkBoxFilter2
                                         (
                                              ~(ui->checkBoxFilter3->isChecked())&
                                             (ui->checkBoxFilter2->isChecked())&
                                             ~(ui->checkBoxMC->isChecked())&
                                              ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseInsensitive))&
                                             (colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                             )|

                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                             (ui->checkBoxMC->isChecked())&
                                            ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseSensitive))
                                               &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                             )|

                                            (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                             (ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMC->isChecked())&
                                             (mesoInS==0)
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                             )|
                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                          (ui->checkBoxMESO->isChecked())&
                                          (ui->checkBoxMC->isChecked())&
                                          (mesoSens==0)
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                          )|
                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                         (ui->checkBoxMEWO->isChecked())
                                         & ~(ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseInsensitive))
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                          )|
                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                         (ui->checkBoxMEWO->isChecked())
                                         & (ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseSensitive))
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                          )|
                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                         ~(ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCI.exactMatch(colFilter))
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                          )|
                                         (
                                               ~(ui->checkBoxFilter3->isChecked())&
                                              (ui->checkBoxFilter2->isChecked())&
                                         (ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCS.exactMatch(colFilter))
                                             &(colFilterE2.contains(filterin2, Qt::CaseInsensitive))
                                          )|

                                         //checkBoxFilter3

                                         (
                                              (ui->checkBoxFilter3->isChecked())&                                            
                                             ~(ui->checkBoxMC->isChecked())&
                                              ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseInsensitive))&
                                             (colFilterE2 != "")

                                             )|

                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                            
                                             (ui->checkBoxMC->isChecked())&
                                            ~(ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMEWO->isChecked())&
                                         (colFilter.contains(filterin, Qt::CaseSensitive))
                                               &   (colFilterE2 != "")
                                             )|

                                            (
                                             (ui->checkBoxFilter3->isChecked())&                                             
                                             (ui->checkBoxMESO->isChecked())&
                                             ~(ui->checkBoxMC->isChecked())&
                                             (mesoInS==0)
                                             &   (colFilterE2 != "")
                                             )|
                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                            
                                          (ui->checkBoxMESO->isChecked())&
                                          (ui->checkBoxMC->isChecked())&
                                          (mesoSens==0)
                                             &   (colFilterE2 != "")
                                          )|
                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                             
                                         (ui->checkBoxMEWO->isChecked())
                                         & ~(ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseInsensitive))
                                             &   (colFilterE2 != "")
                                          )|
                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                             
                                         (ui->checkBoxMEWO->isChecked())
                                         & (ui->checkBoxMC->isChecked())
                                         & (boundind != "")
                                         & (colFilter.contains(filterin, Qt::CaseSensitive))
                                             &   (colFilterE2 != "")
                                          )|
                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                             
                                         ~(ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCI.exactMatch(colFilter))
                                             &   (colFilterE2 != "")
                                          )|
                                         (
                                             (ui->checkBoxFilter3->isChecked())&                                              
                                         (ui->checkBoxMC->isChecked())
                                         &(ui->checkBoxWild->isChecked())
                                         & (rxtswvCS.exactMatch(colFilter))
                                             &   (colFilterE2 != "")
                                          )





                                     )
                                           {
                                                 //qDebug() << "yes";
                                                 //qDebug() << itemnummer;
                                                 //qDebug() << KolZahl;
                                                 //QString colEp=colArV[spalte][itemnummer];

                                                 //zeilecountS++;
                                            //size of filter output
                                                  ui->tableAll->setRowCount(zeilecountS+1);

                                                 for (int spalte=0; spalte<KolZahl; spalte++)

                                                       {
                                                       //QString colEp=colArV[spalte][itemnummer];
                                                     //qDebug() << "spalte";
                                                         //qDebug() << spalte;
                                                          QString colEp=colArV[spalte][itemnummer];

                                                           QString su = colEp.left(500);

                                                           ui->tableAll->setItem(zeilecountS,spalte,new QTableWidgetItem(su));
                                                           //QString colEp=colArV[0][0];
                                                          //qDebug() << colEp;
                                                         //qDebug() << "item";
                                                         //qDebug() << itemnummer;
                                                         //qDebug() << "kolzahl";
                                                         //qDebug() << KolZahl;


                                                        }
                                            zeilecountS++;
                                              }



                   itemnummer++;


        }


kolnummer++;
}

  connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));
}




//+++++++++++++++++++++++
//---------Admin DB tab
//+++++++++++++++++++++++


void MainWindow::RenameCslot()
{
 QString activedb = ui->comboBoxtables->currentText();
 QString cnewname = ui->lineEditRenameC->text();
 QString cbRenameC = ui-> comboBoxRenameC->currentText();

 //
 if (cnewname=="")
            {

              QMessageBox msgBox;
              msgBox.setText("Name missing.");
              msgBox.exec();

            }

 QString colnamesS = "SHOW COLUMNS FROM " + activedb;
           //qDebug() << colnames;

           QSqlQuery querycolS(colnamesS);




           QList<QString> colAr;



           int ncolS=0;
           while (querycolS.next())
               {
               QString colS;
               colS = querycolS.value(0).toString();
               colAr.append(colS);
               ncolS++;
               //qDebug() << ncol;
                 }

           int i = colAr.indexOf(cnewname);
                       if (i != -1)
                          {

                            QMessageBox msgBox;
                            msgBox.setText("Name already in use.");
                            msgBox.exec();

                          }

                   else
                   {



 //

 QString strrenamec = "ALTER TABLE `" + activedb + "` CHANGE COLUMN `" + cbRenameC + "` `" + cnewname + "` LONGTEXT";
 //qDebug() << strrenamec;

 QSqlQuery queryrenamec(strrenamec);
 queryrenamec.exec();

 ui->TableButtonS->animateClick();
}
}

//++++++++++++++++++++++++++++++++++++++++

void MainWindow::MoveCslot()
{
QString cbMoveC = ui->comboBoxMoveC->currentText();
QString cbMoveCRef = ui->comboBoxMoveCRef->currentText();
QString activedb = ui->comboBoxtables->currentText();

QString strmovec = "ALTER TABLE " + activedb + " CHANGE COLUMN " + cbMoveC + " " + cbMoveC + " LONGTEXT AFTER " + cbMoveCRef;
//qDebug() << strmovec;

QSqlQuery querymovec(strmovec);
querymovec.exec();

ui->TableButtonS->animateClick();
}

void MainWindow::copycslot()
{
    QString cbtoCopy = ui->comboBoxCopyC->currentText();
    QString cbCTarget = ui->comboBoxCopyCRef->currentText();
    QString activedb = ui->comboBoxtables->currentText();
    int idcol = ui->comboBoxCopyCRef->currentIndex();


    if(idcol==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error: Please select a non ID column as target.");
        msgBox.exec();

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Warning: This will overwrite all data of the target column.");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        //msgBox.exec();
        int ret = msgBox.exec();

        switch (ret)
        {
          case QMessageBox::Ok:
        {
            QString strmovec = "UPDATE " + activedb + " SET " + cbCTarget + "=" + cbtoCopy + ";";
            //qDebug() << strmovec;

            QSqlQuery querymovec(strmovec);
            querymovec.exec();

          }

              break;

          case QMessageBox::Cancel:

              break;

        }






    }

    ui->TableButtonS->animateClick();

}



//+++++++++++++++++++++++++++++++++++++++++

void MainWindow::AddCslot()
{

    QString activedb = ui->comboBoxtables->currentText();
    QString newname = ui->lineEditAddC->text();
    QString cbRefC = ui-> comboBoxAddC->currentText();

  //
    if (newname=="")
               {

                 QMessageBox msgBox;
                 msgBox.setText("Name missing.");
                 msgBox.exec();

               }

    QString colnamesS = "SHOW COLUMNS FROM " + activedb;
              //qDebug() << colnames;

              QSqlQuery querycolS(colnamesS);




              QList<QString> colAr;



              int ncolS=0;
              while (querycolS.next())
                  {
                  QString colS;
                  colS = querycolS.value(0).toString();
                  colAr.append(colS);
                  ncolS++;
                  //qDebug() << ncol;
                    }

              int i = colAr.indexOf(newname);
                          if (i != -1)
                             {

                               QMessageBox msgBox;
                               msgBox.setText("Name already in use.");
                               msgBox.exec();

                             }

                      else
                      {




//
    QString strnewc = "ALTER TABLE " + activedb + " ADD COLUMN `" + newname + "` LONGTEXT AFTER `" + cbRefC + "`";
    //qDebug() << strnewc;

    QSqlQuery querynewc(strnewc);
    querynewc.exec();

    ui->TableButtonS->animateClick();

}

}

//++++++++++++++++++++++++++++++++++++++++++

void MainWindow::RenameTslot()
{

    QString tnewname = ui->lineEditRenameT->text();
    QString cbRefT = ui-> comboBoxRenameT->currentText();
    //
    if (tnewname=="")
       {

         QMessageBox msgBox;
         msgBox.setText("Name missing.");
         msgBox.exec();

       }


    if (cbRefT=="")
       {

         QMessageBox msgBox;
         msgBox.setText("Table missing.");
         msgBox.exec();

       }




    QSqlQuery querytables("SHOW TABLES");



    QList<QString> tablsAr;



    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);

        //qDebug() << tabls;

        //qDebug() << col;
      indexts++;

    }



                               //qDebug() << tablsAr;




         int i = tablsAr.indexOf(tnewname);
         if (i != -1)
            {

              QMessageBox msgBox;
              msgBox.setText("Name already in use.");
              msgBox.exec();

            }

     else
     {


    //



    QString strnewt = "ALTER TABLE " + cbRefT + " RENAME TO " + tnewname;
    //qDebug() << strnewt;

    QSqlQuery querynewt(strnewt);
    querynewt.exec();

     ui->synctablesButton->animateClick();

    //ALTER TABLE tablename1 RENAME TO tablename2;

}
}

//++++++++++++++++++++++++++++++++++++++++++

void MainWindow::AddTslot()
{
     if(ui->radioButtonAddTAuto->isChecked())
            {

         ui->synctablesButton->animateClick();
        QString tname = ui->lineEditAddTName->text();
        QString idcname = ui->lineEditAddTID->text();

        if (tname=="")
           {

             QMessageBox msgBox;
             msgBox.setText("Name missing.");
             msgBox.exec();

           }


        if (idcname=="")
           {

             QMessageBox msgBox;
             msgBox.setText("ID Name missing.");
             msgBox.exec();

           }




        QSqlQuery querytables("SHOW TABLES");



        QList<QString> tablsAr;



        int indexts=0;
        while (querytables.next())
        {
        //qDebug() << querytables;
            QString tabls;
            tabls = querytables.value(0).toString();
            tablsAr.append(tabls);

            //qDebug() << tabls;

            //qDebug() << col;
          indexts++;

        }



                                   //qDebug() << tablsAr;




             int i = tablsAr.indexOf(tname);
             if (i != -1)
                {

                  QMessageBox msgBox;
                  msgBox.setText("Name already in use.");
                  msgBox.exec();

                }

         else
         {


         QString tauto = "CREATE TABLE " + tname + " (" + idcname + " INT NOT NULL AUTO_INCREMENT, PRIMARY KEY (" + idcname + "))";
           //qDebug() << tauto;

           QSqlQuery querytauto(tauto);
           querytauto.exec();

            ui->synctablesButton->animateClick();

            }



     }


       if(ui->radioButtonAddTReg->isChecked())
            {

           QMessageBox msgBox;
           msgBox.setText("Function not supported.");
           msgBox.exec();

            }

        ui->synctablesButton->animateClick();

}


void MainWindow::copytableslot()
{
    QString tnewname = ui->lineEditCopyTable->text();
    QString cbRefT = ui->comboBoxtables->currentText();
    //
    if (tnewname=="")
       {

         QMessageBox msgBox;
         msgBox.setText("Name missing.");
         msgBox.exec();

       }


    if (cbRefT=="")
       {

         QMessageBox msgBox;
         msgBox.setText("Table missing.");
         msgBox.exec();

       }




    QSqlQuery querytables("SHOW TABLES");



    QList<QString> tablsAr;



    int indexts=0;
    while (querytables.next())
    {
    //qDebug() << querytables;
        QString tabls;
        tabls = querytables.value(0).toString();
        tablsAr.append(tabls);

        //qDebug() << tabls;

        //qDebug() << col;
      indexts++;

    }



                               //qDebug() << tablsAr;




         int i = tablsAr.indexOf(tnewname);
         if (i != -1)
            {

              QMessageBox msgBox;
              msgBox.setText("Name already in use.");
              msgBox.exec();

            }

     else
     {


    //



    QString strnewt = "CREATE TABLE IF NOT EXISTS " + tnewname + " LIKE " + cbRefT +"; INSERT " + tnewname + " SELECT * FROM " + cbRefT + ";";


    //qDebug() << strnewt;

    QSqlQuery querynewt(strnewt);
    querynewt.exec();

     ui->synctablesButton->animateClick();

    //ALTER TABLE tablename1 RENAME TO tablename2;

}


}


void MainWindow::addrowsslot()
{

         int rowsnum = ui->spinBoxAddRows->value();
         QString activedb = ui->comboBoxtables->currentText();

        int rowscol = ui->comboBoxAddRows->currentIndex();

       QString zielkol = ui->comboBoxAddRows->currentText();


       if(rowscol==0)
       {

           QMessageBox msgBox;
           msgBox.setText("Error: Please select a non ID column.");
           msgBox.exec();
       }
       else
       {


    for (int callzeile = 0; callzeile < rowsnum/2; callzeile++)

    {


      QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
      //qDebug() << strupd;
      QSqlQuery queryupd(strupd);
      queryupd.exec();
     }

ui->TableButtonS->animateClick();
}


}




//+++++++++++++++EQ slot+++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MainWindow::EQslot()

{



if(ui->checkBoxEQMT->isChecked())
{
    MainWindow::EQMTslot();
}

if(ui->checkBoxEQNR->isChecked())
{
    MainWindow::EQNRslot();
}


}



void MainWindow::EQMTslot()

{
     ui->tableAll->clearContents();

     int indxEQES = ui->comboBoxEQES->currentIndex();
     int indxEQTS = ui->comboBoxEQTS->currentIndex();

     int indxEQFilter = ui->comboBoxFilterEQ->currentIndex();



     QString filterinEQ = ui->filterinputEQ->text();


     QString tablenameS = ui->comboBoxtables->currentText();

     //qDebug() << tablenameS;

     QString strtable = "SELECT * FROM " + tablenameS;

     //qDebug() << strtable;

     QSqlQuery queryS(strtable);



    QString colnamesS = "SHOW COLUMNS FROM " + tablenameS;
            //qDebug() << colnames;

            QSqlQuery querycolS(colnamesS);


            int KolZahl = querycolS.size();



            ui->tableAll->setColumnCount(KolZahl);


            QList<QString> colAr;



            int ncolS=0;
            while (querycolS.next())
                {
                QString colS;
                colS = querycolS.value(0).toString();
                colAr.append(colS);
                ncolS++;
                //qDebug() << ncol;
                  }




            ui->tableAll->setHorizontalHeaderLabels(colAr);







    //QList<QString> sidAr;
    //QList<QString> esAr;
    //QList<QString> tsAr;




//+++++++++++++vector+++++++++++++++++++++++++++++

    QVector<QStringList> colArV(KolZahl);

         //qDebug() << indxC1;
         //qDebug() << indxC2;

               //int index=0;
               while (queryS.next())
                   //for(int index=0;index < RowZahlS; index++)
               {

                   for (int coldisp = 0; coldisp < KolZahl; coldisp++)
                   //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                   {

                       QString boxAll = queryS.value(coldisp).toString();
                       colArV[coldisp].append(boxAll);
                       //qDebug() << "index";
                       //qDebug() <<  index;
                       //qDebug() << "coldisp";
                       //qDebug() << coldisp;
                          //qDebug() << boxAll;

                      }

               //index++;
               }


    //+++++++++++++++++++++++++++++++++++++++

        /*while (queryS.next())
    {


            QString sid;
            sid = queryS.value(GSIDint).toString();
            sidAr.append(sid);


            QString es;
            es = queryS.value(GSESint).toString();
            esAr.append(es);
            //qDebug() << es;




            QString ts;
            ts = queryS.value(GSTSint).toString();
            tsAr.append(ts);



        }*/



//+++++++++++++++++++++++++++++call string array

   if (
           ~(ui->checkBoxFilterEQ->isChecked())
           & ~(ui->checkBoxFilterEQNE->isChecked())
            & ~(ui->checkBoxFilterEmptyEQ->isChecked())



           )

   {

        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                //qDebug() << colFilterEQTS;


    //filterG2
                if (
                        (colFilterEQES==colFilterEQTS)
                       &(colFilterEQES!="")
                    )
              {


                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }









                        zeilecount++;
                        //qDebug() <<  zeilecount;

                }



                sna++;


          }







                }





//+++++not empty filter
   //~(ui->checkBoxFilterEQ->isChecked())
    //& ~(ui->checkBoxFilterEmptyEQ->isChecked())

 if (
         (ui->checkBoxFilterEQNE->isChecked())

      )

   {

         //qDebug() << "110";
       int zeilecount = 0;
       int sna = 0;
       while (sna < queryS.size())

       //for (int na = 0; na = 10; na ++)

             {
               //QString sidE;
               //sidE=sidAr[sna];

               //QString sidE=colArV[GSIDint][sna];


               //if()
               QString colFilterEQES=colArV[indxEQES][sna];
               QString colFilterEQTS=colArV[indxEQTS][sna];

                  QString colFilterE2=colArV[indxEQFilter][sna];


               //qDebug() << colFilterEQES;


   //filterG2
               if (
                       (colFilterEQES==colFilterEQTS)
                      &(colFilterEQES!="")
                       &  (colFilterE2 != "")



                   )
             {









                        ui->tableAll->setRowCount(zeilecount+1);

                       //while (callcol < KolZahl)
                       for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                       {
                       //QString gid;
                       //gid = queryG.value(GIDint).toString();

                           QString colEp=colArV[callcol][sna];

                            QString su = colEp.left(500);

                           ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                       }









                       zeilecount++;
                       //qDebug() <<  zeilecount;

                         }



   sna++;


                       }








               }








   //+++++++++end not empty filter

  //---------empty
 //~(ui->checkBoxFilterEQ->isChecked())
 //& ~(ui->checkBoxFilterEQNE->isChecked())


  if (
           (ui->checkBoxFilterEmptyEQ->isChecked())

            )

    {
 //qDebug() << "101";
        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                   QString colFilterE2=colArV[indxEQFilter][sna];


                //qDebug() << colFilterE2;


    //filterG2
                if (
                        (colFilterEQES==colFilterEQTS)
                       &(colFilterEQES!="")
                        &  (colFilterE2 == "")



                    )
              {









                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }









                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


 sna++;



                        }








                }






   //-----------empty end
  if (
            (ui->checkBoxFilterEQ->isChecked())
            & ~(ui->checkBoxFilterEQNE->isChecked())
             & ~(ui->checkBoxFilterEmptyEQ->isChecked())

            )

    {
 //qDebug() << "100";
        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                   QString colFilterE2=colArV[indxEQFilter][sna];


                //qDebug() << colFilterE2;


    //filterG2
                if (
                        (colFilterEQES==colFilterEQTS)
                       &(colFilterEQES!="")
                        &  (colFilterE2.contains(filterinEQ, Qt::CaseInsensitive))



                    )
              {



                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));
                                        }

                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }

                sna++;


                        }


                }

  connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));

}




//-----------------------number check-----------------------------------------------------------


void MainWindow::EQNRslot()

{
     ui->tableAll->clearContents();

     int indxEQES = ui->comboBoxEQES->currentIndex();
     int indxEQTS = ui->comboBoxEQTS->currentIndex();

     int indxEQFilter = ui->comboBoxFilterEQ->currentIndex();



     QString filterinEQ = ui->filterinputEQ->text();


     QString tablenameS = ui->comboBoxtables->currentText();

     //qDebug() << tablenameS;

     QString strtable = "SELECT * FROM " + tablenameS;

     //qDebug() << strtable;

     QSqlQuery queryS(strtable);



    QString colnamesS = "SHOW COLUMNS FROM " + tablenameS;
            //qDebug() << colnames;

            QSqlQuery querycolS(colnamesS);


            int KolZahl = querycolS.size();



            ui->tableAll->setColumnCount(KolZahl);


            QList<QString> colAr;



            int ncolS=0;
            while (querycolS.next())
                {
                QString colS;
                colS = querycolS.value(0).toString();
                colAr.append(colS);
                ncolS++;
                //qDebug() << ncol;
                  }




            ui->tableAll->setHorizontalHeaderLabels(colAr);







    //QList<QString> sidAr;
    //QList<QString> esAr;
    //QList<QString> tsAr;




//+++++++++++++vector+++++++++++++++++++++++++++++

    QVector<QStringList> colArV(KolZahl);

         //qDebug() << indxC1;
         //qDebug() << indxC2;

               //int index=0;
               while (queryS.next())
                   //for(int index=0;index < RowZahlS; index++)
               {

                   for (int coldisp = 0; coldisp < KolZahl; coldisp++)
                   //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                   {

                       QString boxAll = queryS.value(coldisp).toString();
                       colArV[coldisp].append(boxAll);
                       //qDebug() << "index";
                       //qDebug() <<  index;
                       //qDebug() << "coldisp";
                       //qDebug() << coldisp;
                          //qDebug() << boxAll;

                      }

               //index++;
               }


    //+++++++++++++++++++++++++++++++++++++++

        /*while (queryS.next())
    {


            QString sid;
            sid = queryS.value(GSIDint).toString();
            sidAr.append(sid);


            QString es;
            es = queryS.value(GSESint).toString();
            esAr.append(es);
            //qDebug() << es;




            QString ts;
            ts = queryS.value(GSTSint).toString();
            tsAr.append(ts);



        }*/



//+++++++++++++++++++++++++++++call string array

   if (
           ~(ui->checkBoxFilterEQ->isChecked())
           & ~(ui->checkBoxFilterEQNE->isChecked())
            & ~(ui->checkBoxFilterEmptyEQ->isChecked())



           )

   {

        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                //qDebug() << colFilterEQTS;


    //NumberfilterG+++

                QStringList ESInt;
                QRegExp rxES("(\\d+)");


                int posNR = 0;
                while ((posNR = rxES.indexIn(colFilterEQES,posNR)) != -1)
                {
                ESInt << rxES.cap(1);
                posNR += rxES.matchedLength();

                }
             //qDebug() << ESInt;





             QStringList TSInt;
             QRegExp rxTS("(\\d+)");


             int posNRts = 0;
             while ((posNRts = rxTS.indexIn(colFilterEQTS,posNRts)) != -1)
             {
             TSInt << rxTS.cap(1);
             posNRts += rxTS.matchedLength();

             }
            //qDebug() << TSInt;

            if(ESInt!=TSInt)
            {
                //qDebug() << "numbers are not the same";



//++

                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }









                        zeilecount++;
                        //qDebug() <<  zeilecount;

                }



                sna++;


          }







                }





//+++++not empty filter
   //(ui->checkBoxFilterEQ->isChecked())
    //& ~(ui->checkBoxFilterEmptyEQ->isChecked())

 if (

          (ui->checkBoxFilterEQNE->isChecked())


           )

   {

         //qDebug() << "110";
       int zeilecount = 0;
       int sna = 0;
       while (sna < queryS.size())

       //for (int na = 0; na = 10; na ++)

             {
               //QString sidE;
               //sidE=sidAr[sna];

               //QString sidE=colArV[GSIDint][sna];


               //if()
               QString colFilterEQES=colArV[indxEQES][sna];
               QString colFilterEQTS=colArV[indxEQTS][sna];

                  QString colFilterE2=colArV[indxEQFilter][sna];


               //qDebug() << colFilterEQES;



                  //NumberfilterG+++

                              QStringList ESInt;
                              QRegExp rxES("(\\d+)");


                              int posNR = 0;
                              while ((posNR = rxES.indexIn(colFilterEQES,posNR)) != -1)
                              {
                              ESInt << rxES.cap(1);
                              posNR += rxES.matchedLength();

                              }
                           //qDebug() << ESInt;


                           QStringList TSInt;
                           QRegExp rxTS("(\\d+)");


                           int posNRts = 0;
                           while ((posNRts = rxTS.indexIn(colFilterEQTS,posNRts)) != -1)
                           {
                           TSInt << rxTS.cap(1);
                           posNRts += rxTS.matchedLength();

                           }
                          //qDebug() << TSInt;




               if (
                       (ESInt!=TSInt)
                       &  (colFilterE2 != "")

                   )
             {









                        ui->tableAll->setRowCount(zeilecount+1);

                       //while (callcol < KolZahl)
                       for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                       {
                       //QString gid;
                       //gid = queryG.value(GIDint).toString();

                           QString colEp=colArV[callcol][sna];

                            QString su = colEp.left(500);

                           ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                       }









                       zeilecount++;
                       //qDebug() <<  zeilecount;

                         }



   sna++;


                       }








               }








   //+++++++++end not empty filter

  //---------empty
 //(ui->checkBoxFilterEQ->isChecked())
 //& ~(ui->checkBoxFilterEQNE->isChecked())


  if (
            (ui->checkBoxFilterEmptyEQ->isChecked())

            )

    {
 //qDebug() << "101";
        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                   QString colFilterE2=colArV[indxEQFilter][sna];


                //qDebug() << colFilterE2;


                   //NumberfilterG+++

                               QStringList ESInt;
                               QRegExp rxES("(\\d+)");


                               int posNR = 0;
                               while ((posNR = rxES.indexIn(colFilterEQES,posNR)) != -1)
                               {
                               ESInt << rxES.cap(1);
                               posNR += rxES.matchedLength();

                               }
                            //qDebug() << ESInt;


                            QStringList TSInt;
                            QRegExp rxTS("(\\d+)");


                            int posNRts = 0;
                            while ((posNRts = rxTS.indexIn(colFilterEQTS,posNRts)) != -1)
                            {
                            TSInt << rxTS.cap(1);
                            posNRts += rxTS.matchedLength();

                            }
                           //qDebug() << TSInt;




                if (
                        (ESInt!=TSInt)
                        &  (colFilterE2 == "")


                    )
              {





                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }









                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }


 sna++;



                        }








                }






   //-----------empty end
  if (
            (ui->checkBoxFilterEQ->isChecked())
            & ~(ui->checkBoxFilterEQNE->isChecked())
             & ~(ui->checkBoxFilterEmptyEQ->isChecked())

            )

    {
 //qDebug() << "100";
        int zeilecount = 0;
        int sna = 0;
        while (sna < queryS.size())

        //for (int na = 0; na = 10; na ++)

              {
                //QString sidE;
                //sidE=sidAr[sna];

                //QString sidE=colArV[GSIDint][sna];


                //if()
                QString colFilterEQES=colArV[indxEQES][sna];
                QString colFilterEQTS=colArV[indxEQTS][sna];

                   QString colFilterE2=colArV[indxEQFilter][sna];


                //qDebug() << colFilterE2;


                   //NumberfilterG+++

                               QStringList ESInt;
                               QRegExp rxES("(\\d+)");


                               int posNR = 0;
                               while ((posNR = rxES.indexIn(colFilterEQES,posNR)) != -1)
                               {
                               ESInt << rxES.cap(1);
                               posNR += rxES.matchedLength();

                               }
                            //qDebug() << ESInt;


                            QStringList TSInt;
                            QRegExp rxTS("(\\d+)");


                            int posNRts = 0;
                            while ((posNRts = rxTS.indexIn(colFilterEQTS,posNRts)) != -1)
                            {
                            TSInt << rxTS.cap(1);
                            posNRts += rxTS.matchedLength();

                            }
                           //qDebug() << TSInt;




                if (
                        (ESInt!=TSInt)
                        &  (colFilterE2.contains(filterinEQ, Qt::CaseInsensitive))



                    )
              {




                         ui->tableAll->setRowCount(zeilecount+1);

                        //while (callcol < KolZahl)
                        for (int callcol = 0; (callcol < KolZahl); callcol ++)
                                        {
                        //QString gid;
                        //gid = queryG.value(GIDint).toString();

                            QString colEp=colArV[callcol][sna];

                             QString su = colEp.left(500);

                            ui->tableAll->setItem(zeilecount,callcol,new QTableWidgetItem(su));



                                        }









                        zeilecount++;
                        //qDebug() <<  zeilecount;

                          }



 sna++;


                        }








                }







//else end


  connect(ui->tableAll, SIGNAL(cellClicked(int,int)), this, SLOT(itemChanged(int,int)));

}


//----END-------------------number check-----------------------------------------------------------


//++++++++++++++END of EQ slot++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//csv++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MainWindow::savecsvslot()
{
    QMessageBox msgBox;
    msgBox.setText("Only the GNULOCSYS CSV format is supported: The separator is a comma (,), the delimiter is a single quote (') and every cell is delimited by single quotes. Empty cells are allowed.");
    msgBox.exec();

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    //QString csvname = ui->filenamesave->text();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/stallman/untitled.csv",
                               tr("CSV (*.csv)"));

   /* QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();*/


    QString tablenameS = ui->comboBoxtables->currentText();

    if(tablenameS.trimmed().isEmpty())
                {
    QMessageBox msgBox;
    msgBox.setText("Please select a table.");
    msgBox.exec();
                 }

    else
        {

        QString strtable = "SELECT * FROM " + tablenameS;

        //qDebug() << strtable;

        QSqlQuery query(strtable);

        //QString textData;

        QFile csvFile(fileName);
        csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate);


           int index=0;
           while (query.next())
           {
            //qDebug() <<index;
             QString textData;
               for (int coldisp = 0; coldisp < query.record().count(); coldisp++)
               {



                   QString s;
                   QString sp = query.value(coldisp).toString();

                   /*s = sp.replace('"', '\""');
                   textData+='"';
                   textData+=s;
                   textData+='"';
                   textData += ",";*/

                   s = sp.replace("'", "''");
                   textData+="'";
                   textData+=s;
                   textData+="'";
                   textData += ",";

                  }
                 textData += "\n\r";
                 index++;

                 QTextStream out(&csvFile);
                 out << textData;

                }

    csvFile.close();


    /*QFile csvFile(fileName);
           if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
               {
               QTextStream out(&csvFile);
               out << textData;
               csvFile.close();
                }*/

    }


}

//WIP
void MainWindow::savehtmlslot()
{


        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
       // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
        dialog.setViewMode(QFileDialog::Detail);
        //QString csvname = ui->filenamesave->text();

        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "/home/stallman/untitled.csv",
                                   tr("HTML (*.html)"));

       /* QStringList fileNames;
        if (dialog.exec())
            fileNames = dialog.selectedFiles();*/


        QString tablenameS = ui->comboBoxtables->currentText();

        if(tablenameS.trimmed().isEmpty())
                    {
        QMessageBox msgBox;
        msgBox.setText("Please select a table.");
        msgBox.exec();
                     }

        else
            {

            QString strtable = "SELECT * FROM " + tablenameS;

            //qDebug() << strtable;

            QSqlQuery query(strtable);

            QString textData;


            QFile csvFile(fileName);
            csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate);

            textData+='<table style="width:100%">';


               int index=0;
               while (query.next())
               {
                //qDebug() <<index;
                 //QString textData;

                   textData+="<tr>";

                   for (int coldisp = 0; coldisp < query.record().count(); coldisp++)
                   {



                       QString s;
                       QString sp = query.value(coldisp).toString();

                       /*s = sp.replace('"', '\""');
                       textData+='"';
                       textData+=s;
                       textData+='"';
                       textData += ",";*/

                       if (
                           (sp.contains("\n\r", Qt::CaseInsensitive))
                           )
                             {
                       s = sp.replace("\n\r", "<br>");
                              }

                       else
                               {
                         s = sp.replace("\n", "<br>");
                                }



                       textData+="<td>" + s + "</td>";
                       textData += "\n\r";


                      }
                     textData += " </tr>";
                     index++;

                     QTextStream out(&csvFile);
                     out << textData;

                    }

        csvFile.close();


        /*QFile csvFile(fileName);
               if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
                   {
                   QTextStream out(&csvFile);
                   out << textData;
                   csvFile.close();
                    }*/

        }


    }







void MainWindow::importcsvslot()
{    



    QMessageBox msgBox;
    msgBox.setText("Only the GNULOCSYS CSV format is supported: The separator is a comma (,), the delimiter is a single quote (') and every cell is delimited by single quotes. Empty cells are allowed, therefore please make sure that no cell of the CSV spread sheet contains the following code: ',' (comma between single quotes). Please replace this combination with e.g. comma between double quotes (not double single quotes) or include spaces. All other combinations of commas and single quotes are allowed. ");
    msgBox.exec();

    ui->tableinput->clearContents();

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    //QString csvname = ui->filenamesave->text();


    //QStringList fileNames;
     QString fileName;
    //if (dialog.exec())
        //fileNames = dialog.selectedFiles();
    fileName = dialog.getOpenFileName() ;
    //qDebug() << fileName;
    ui->lineEditCSV->setText(fileName);





    QFile file(fileName);
      if (!file.open(QIODevice::ReadOnly))
      {
          qDebug() << "error";
          return;
      }

      QStringList wordList;
      QString ganz;
      int totalines=0;
      while (!file.atEnd())
      {
          QString line = file.readLine();
          //wordList.append(line.split(',').first());
          //wordList.append(line.split(',').at(1));
          ganz += line;
          totalines++;




       }


      //qDebug() << ganz;

      //QRegExp rxtrenn("'(?!\')");
      //QRegExp rxtrenn("'(?!\')");
      //QRegExp("'(?!\')");

      //QRegExp rxtrenn('"' + squote + '(?!\'  +    squote +       ')'

      QString escapequote = "[]{es3a4d00pel}[]";
      //QString scomma = "[]{s3p4rc}[]";
      //QString squote = "[]{s3p4rq}[]";
      QString separ = "[]{s3p4r}[]";
      //ganz.replace("',\n\r'",separ + "\n\r");

      /*int anzahlrowWin = (ganz.count("',\n\r'", Qt::CaseInsensitive));
      int anzahlrowWinKor = anzahlrowWin+1;
      //qDebug() << "anzahlrowWin";
      //qDebug() << anzahlrowWin;
      ganz.replace("',\n\r'",separ);

      int anzahlrowLinux = (ganz.count("',\n'", Qt::CaseInsensitive));
      int anzahlrowLinKor = anzahlrowLinux+1;
      //qDebug() << "anzahlrowLinux";
      //qDebug() << anzahlrowLinux;
      //ganz.replace("',\n'",separ + "\n\r");
      ganz.replace("',\n'",separ);*/

      //----------------------------
             /*int wincount = 0;
             int pos = 0;

             while ((pos = rx_win.indexIn(ganz, pos)) != -1)
             {
                 QStringList capturedTexts(rx_win.capturedTexts());
                    qDebug() << capturedTexts;
                 pos += rx_win.matchedLength();
                 ++wincount;
             }
             if(wincount == 0)
                 qDebug() << "\tNo matches found.";

          qDebug() <<  wincount;
          int anzahlrowWinKor = wincount+1;
              qDebug() << anzahlrowWinKor;
              ganz.replace(rx_win,separ);*/
      //----------------------------

              QRegExp rx_win;
              rx_win.setPattern("(',\n\r')(?!')");

              QRegExp rx_winOO;
              rx_winOO.setPattern("('\n\r')(?!')");

              QRegExp rx_lin;
              rx_lin.setPattern("(',\n')(?!')");

              QRegExp rx_linOO;
              rx_linOO.setPattern("('\n')(?!')");

            //int anzahlrowWin = (ganz.count("',\n\r'", Qt::CaseInsensitive));
            int anzahlrowWin = (ganz.count(rx_win));
            int anzahlrowWinKor = anzahlrowWin+1;
            //qDebug() << "anzahlrowWin";
            //qDebug() << anzahlrowWinKor;
            //ganz.replace("',\n\r'",separ);
            ganz.replace(rx_win,separ);

            //int anzahlrowWinOO = (ganz.count("'\n\r'", Qt::CaseInsensitive));
              int anzahlrowWinOO = (ganz.count(rx_winOO));
            int anzahlrowWinOOKor = anzahlrowWinOO+1;
            //qDebug() << "anzahlrowWinOO";
            //qDebug() << anzahlrowWinOOKor;
            //ganz.replace("'\n\r'",separ);
             ganz.replace(rx_winOO,separ);

            //int anzahlrowLinux = (ganz.count("',\n'", Qt::CaseInsensitive));
              int anzahlrowLinux = (ganz.count(rx_lin));
            int anzahlrowLinKor = anzahlrowLinux+1;
            //qDebug() << "anzahlrowLinux";
            //qDebug() << anzahlrowLinKor;
            //ganz.replace("',\n'",separ);
             ganz.replace(rx_lin,separ);

            //int anzahlrowLinuxOO = (ganz.count("'\n'", Qt::CaseInsensitive));
            int anzahlrowLinuxOO = (ganz.count(rx_linOO));
            int anzahlrowLinOOKor = anzahlrowLinuxOO+1;
            //qDebug() << "anzahlrowLinuxOO";
            //qDebug() << anzahlrowLinOOKor;
            //ganz.replace("'\n'",separ);
              ganz.replace(rx_linOO,separ);

      //

      ganz.replace("','','','",(separ + separ + separ));
      ganz.replace("','','",(separ + separ));

      ganz.replace("','",(separ));
      /*QRegExp rx_sep;
      rx_sep.setPattern("(',')(?!')");
      ganz.replace(rx_sep,(separ));*/


      ganz.replace("''",(escapequote));

      QRegExp rx_singsep;
      rx_singsep.setPattern("(')(?!')");
      //ganz.replace("'",(separ));
      ganz.replace(rx_singsep,(separ));

      ganz.replace((escapequote),"'");

      int anzahlsep = (ganz.count(separ, Qt::CaseInsensitive));


       //int  kol=7;
      int anzkor = anzahlsep-1;
      int anzkolauto;

      /*if(anzahlrowLinux==0)
      {
      anzkolauto = anzkor/anzahlrowWinKor;
      }

      if(anzahlrowWin==0)
      {
      anzkolauto = anzkor/anzahlrowLinKor;
      }*/



      int anzdiff = anzahlrowLinKor + anzahlrowLinOOKor + anzahlrowWinKor + anzahlrowWinOOKor -3;
       anzkolauto = anzkor/anzdiff;

        //qDebug() << anzdiff;

                     //qDebug() << anzahlrowWinKor;




       /* if(anzahlrowLinux==0)
            {
                if(anzahlrowWinOO==0)
                      {
                anzkolauto = anzkor/anzahlrowWinKor;
                     }

                if(anzahlrowWin==0)
                      {
                anzkolauto = anzkor/anzahlrowWinOOKor;
                      }

            }

            if(anzahlrowWin==0)
            {

                if(anzahlrowLinuxOO==0)
                      {
                anzkolauto = anzkor/anzahlrowLinKor;
                     }

                if(anzahlrowLinux==0)
                      {
                anzkolauto = anzkor/anzahlrowLinOOKor;
                      }

            }*/


      //qDebug() << anzkolauto;


      //int kol = ui->spinBoxCSVtotal->value();
      int kol = anzkolauto;
      ui->spinBoxCSVCol->setMaximum(kol);
      ui->tableinput->setColumnCount(kol);



      int anzrows = anzkor/kol;
       //qDebug() << anzrows;

      //ganz.replace("'",squote);
      //ganz.replace(",",scomma);

      //wordList << ganz.split(separ).at(0);
        wordList << ganz.split(separ);



      //qDebug() << wordList;
       //qDebug() << ganz;


      //QString listcall=wordList[1];

       //qDebug() << listcall;

       int elemente = wordList.count();
       //qDebug() << elemente;


          QVector<QStringList> colArC(kol);

      int zeilecountS = 0;
      int n=0;
      for (int elemNR = 1; (elemNR <= anzrows); elemNR ++)
      {


          //elemNR+(kol+1)

            int z = n*(kol-1);

            //qDebug() << z;
              //qDebug() << "enr";
                //qDebug() << elemNR;



          //QString listcall=wordList[elemNR+(z)+coldisp];

                  ui->tableinput->setRowCount(zeilecountS+1);

                  for (int coldisp = 0; coldisp < kol; coldisp++)
                  //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                  {

                      QString listcall=wordList[elemNR+(z)+coldisp];
                      colArC[coldisp].append(listcall);
                      QString listcallsu = listcall.left(500);

                      //ui->tableinput->setItem(zeilecountS,coldisp,new QTableWidgetItem(listcall));

                      QTableWidgetItem *item;
                      item = new QTableWidgetItem(listcallsu);
                      item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                      ui->tableinput->setItem(zeilecountS,coldisp,item);
                      /*qDebug() << "index";
                      qDebug() <<  index;
                      qDebug() << "coldisp";
                      qDebug() << coldisp;
                      */

                    }
                  zeilecountS++;


            if(z<=anzkor)
            {
          n++;
            }

       //qDebug() << listcall;

       }


//Call array

          int koldisp1 = ui->spinBoxCSVCol->value();
          int KolZahl = koldisp1 -1;

      //QString colFilter=colArC[0][elemNR];

  }

    //END+++++++++++++++csv++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++CSV to SQL++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void MainWindow::csvtosqlslot()
{
    int csvsid = ui->comboBoxCSVsid->currentIndex();
    QString csvsidstr = ui->comboBoxCSVsid->currentText();
    QString zielkol = ui->comboBoxCSVziel->currentText();
    QString activedb = ui->comboBoxtables->currentText();
    QString setstartcheck = ui->lineEditFirstID->text();
    int setstart;

    if(
            (ui->checkBoxSetID->isChecked())
            &(setstartcheck=="")
            )
   {


       QMessageBox msgBox;
       msgBox.setText("Error: Number for first row missing.");
       msgBox.exec();
       return;


   }

    if(csvsidstr==zielkol)
    {
        QMessageBox msgBox;
        msgBox.setText("Error: ID column cannot be overwritten.");
        msgBox.exec();

    }
    else
    {



          QMessageBox msgBox;
                 msgBox.setText("Warning: This will overwrite all data of the target column.");
                 msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                 msgBox.setDefaultButton(QMessageBox::Ok);
                 //msgBox.exec();
                 int ret = msgBox.exec();

                 switch (ret)
                 {
                   case QMessageBox::Ok:
                 {

                     QString fileName = ui->lineEditCSV->text();
                     QFile file(fileName);
                       if (!file.open(QIODevice::ReadOnly))
                       {
                           qDebug() << "error";
                           return;
                       }

                       QStringList wordList;
                       QString ganz;
                       int totalines=0;
                       while (!file.atEnd())
                       {
                           QString line = file.readLine();
                           ganz += line;
                           totalines++;

                        }


                       QString escapequote = "[]{es3a4d00pel}[]";

                       QString separ = "[]{s3p4r}[]";

                               QRegExp rx_win;
                               rx_win.setPattern("(',\n\r')(?!')");

                               QRegExp rx_winOO;
                               rx_winOO.setPattern("('\n\r')(?!')");

                               QRegExp rx_lin;
                               rx_lin.setPattern("(',\n')(?!')");

                               QRegExp rx_linOO;
                               rx_linOO.setPattern("('\n')(?!')");

                             //int anzahlrowWin = (ganz.count("',\n\r'", Qt::CaseInsensitive));
                             int anzahlrowWin = (ganz.count(rx_win));
                             int anzahlrowWinKor = anzahlrowWin+1;
                             //qDebug() << "anzahlrowWin";
                             //qDebug() << anzahlrowWinKor;
                             //ganz.replace("',\n\r'",separ);
                             ganz.replace(rx_win,separ);

                             //int anzahlrowWinOO = (ganz.count("'\n\r'", Qt::CaseInsensitive));
                               int anzahlrowWinOO = (ganz.count(rx_winOO));
                             int anzahlrowWinOOKor = anzahlrowWinOO+1;
                             //qDebug() << "anzahlrowWinOO";
                             //qDebug() << anzahlrowWinOOKor;
                             //ganz.replace("'\n\r'",separ);
                              ganz.replace(rx_winOO,separ);

                             //int anzahlrowLinux = (ganz.count("',\n'", Qt::CaseInsensitive));
                               int anzahlrowLinux = (ganz.count(rx_lin));
                             int anzahlrowLinKor = anzahlrowLinux+1;
                             //qDebug() << "anzahlrowLinux";
                             //qDebug() << anzahlrowLinKor;
                             //ganz.replace("',\n'",separ);
                              ganz.replace(rx_lin,separ);

                             //int anzahlrowLinuxOO = (ganz.count("'\n'", Qt::CaseInsensitive));
                             int anzahlrowLinuxOO = (ganz.count(rx_linOO));
                             int anzahlrowLinOOKor = anzahlrowLinuxOO+1;
                             //qDebug() << "anzahlrowLinuxOO";
                             //qDebug() << anzahlrowLinOOKor;
                             //ganz.replace("'\n'",separ);
                               ganz.replace(rx_linOO,separ);

                       //

                       ganz.replace("','','','",(separ + separ + separ));
                       ganz.replace("','','",(separ + separ));

                       ganz.replace("','",(separ));

                       ganz.replace("''",(escapequote));

                       QRegExp rx_singsep;
                       rx_singsep.setPattern("(')(?!')");
                       //ganz.replace("'",(separ));
                       ganz.replace(rx_singsep,(separ));

                       ganz.replace((escapequote),"'");

                       int anzahlsep = (ganz.count(separ, Qt::CaseInsensitive));

                       int anzkor = anzahlsep-1;
                       int anzkolauto;


                       int anzdiff = anzahlrowLinKor + anzahlrowLinOOKor + anzahlrowWinKor + anzahlrowWinOOKor -3;
                        anzkolauto = anzkor/anzdiff;

                         //qDebug() << anzdiff;

                         //qDebug() << anzahlrowWinKor;


                       //qDebug() << anzkolauto;


                       //int kol = ui->spinBoxCSVtotal->value();
                       int kol = anzkolauto;
                       ui->spinBoxCSVCol->setMaximum(kol);
                       ui->tableinput->setColumnCount(kol);



                       int anzrows = anzkor/kol;

                         wordList << ganz.split(separ);



                        int elemente = wordList.count();
                        //qDebug() << elemente;


                           QVector<QStringList> colArC(kol);

                       int zeilecountS = 0;
                       int n=0;
                       for (int elemNR = 1; (elemNR <= anzrows); elemNR ++)
                       {


                           //elemNR+(kol+1)

                             int z = n*(kol-1);

                             //qDebug() << z;
                               //qDebug() << "enr";
                                 //qDebug() << elemNR;



                           //QString listcall=wordList[elemNR+(z)+coldisp];



                                   for (int coldisp = 0; coldisp < kol; coldisp++)
                                   //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                                   {

                                       QString listcall=wordList[elemNR+(z)+coldisp];
                                       colArC[coldisp].append(listcall);


                                       /*qDebug() << "index";
                                       qDebug() <<  index;
                                       qDebug() << "coldisp";
                                       qDebug() << coldisp;
                                       */

                                     }
                                   zeilecountS++;


                             if(z<=anzkor)
                             {
                           n++;
                             }

                        //qDebug() << zeilecountS;

                        }

                  //qDebug() << "zeilecountS";
                   //qDebug() << zeilecountS;


                 //Call array

                 //id error message moved to top



                           if(
                                   ~(ui->checkBoxSetID->isChecked())
                              )

                            {

                                setstart = 0;


                           }
                           if(
                                   (ui->checkBoxSetID->isChecked())
                              )

                           {
                                setstart = ui->lineEditFirstID->text().toInt();
                           }
                            //qDebug() << "setstart";
                            //qDebug() << setstart;




                           QString rowzahls = "SELECT COUNT(*) FROM " + activedb;

                           QSqlQuery queryc(rowzahls);
                            int rowzahl;




                                        while (queryc.next())
                                        {


                                        rowzahl = queryc.value(0).toInt();

                                        }


                                     //qDebug() << "rowzahl";
                                      //qDebug() << rowzahl;

                           if(zeilecountS > rowzahl-setstart)
                           {

                               int missingrows = zeilecountS - (rowzahl-setstart);
                               QMessageBox msgBox;
                               msgBox.setText("Adding rows.");
                               msgBox.exec();

                               for (int callzeile = 0; callzeile < missingrows/2+1; callzeile++)

                               {


                                 QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
                                 //qDebug() << strupd;
                                 QSqlQuery queryupd(strupd);
                                 queryupd.exec();
                                }
                        //in adding rows
                               int koldisp1 = ui->spinBoxCSVCol->value();
                               int KolZahl = koldisp1 -1;
                               //qDebug() << KolZahl;


                                /*if(ui->checkBoxAddLines->isChecked())
                                {

                                       for (int callzeile = 0; callzeile < anzdiff/2+1; callzeile++)
                                       //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                                       {


                                         QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
                                         //qDebug() << strupd;
                                         QSqlQuery queryupd(strupd);
                                         queryupd.exec();
                                        }
                                 }*/


                               //ID
                               QList<QString> IDsAr;
                               QString strtable = "SELECT * FROM " + activedb;

                               //qDebug() << strtable;

                               QSqlQuery queryid(strtable);



                                        int indexts=0;
                                            while (queryid.next())
                                            {
                                            //qDebug() << querytables;

                                                QString getid = queryid.value(csvsid).toString();
                                                IDsAr.append(getid);

                                                //qDebug() << getid;

                                                //qDebug() << col;
                                              indexts++;

                                            }

                                            int ccounter=0;
                                            if(ui->checkBoxSetID->isChecked())

                                             {

                                                 ccounter = setstart-1;


                                            }




                                            for (int callrw = 0; callrw < anzdiff; callrw++)
                                            //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                                            {

                                              QString colFilterR=colArC[KolZahl][callrw];
                                              QString colFilter = colFilterR.replace("'", "\\'");
                                              //qDebug() << colFilter;




                                              QString IDNumber = IDsAr[callrw+ccounter];
                                              //qDebug() << IDNumber ;
                                                          //qDebug() <<  zielkol  ;
                                                          //qDebug() << csvsidstr ;

                                              //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                                              //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                                              QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + csvsidstr   + "`= '" + IDNumber  + "'";
                                             //qDebug() << strup;


                                             // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                                              //qDebug() << strupd;
                                              QSqlQuery queryup(strup);
                                              queryup.exec();
                                             }


                        //end in adding rows
                           }
                           else
                           {




                           int koldisp1 = ui->spinBoxCSVCol->value();

                           int KolZahl = koldisp1 -1;

                           //qDebug() << KolZahl;


                            /*if(ui->checkBoxAddLines->isChecked())
                            {

                                   for (int callzeile = 0; callzeile < anzdiff/2+1; callzeile++)
                                   //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                                   {


                                     QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
                                     //qDebug() << strupd;
                                     QSqlQuery queryupd(strupd);
                                     queryupd.exec();
                                    }
                             }*/


                           //ID
                           QList<QString> IDsAr;
                           QString strtable = "SELECT * FROM " + activedb;

                           //qDebug() << strtable;

                           QSqlQuery queryid(strtable);



                                    int indexts=0;
                                        while (queryid.next())
                                        {
                                        //qDebug() << querytables;

                                            QString getid = queryid.value(csvsid).toString();
                                            IDsAr.append(getid);

                                            //qDebug() << getid;

                                            //qDebug() << col;
                                          indexts++;

                                        }

                                        int ccounter=0;
                                        if(ui->checkBoxSetID->isChecked())

                                         {

                                             ccounter = setstart-1;


                                        }




                                        for (int callrw = 0; callrw < anzdiff; callrw++)
                                        //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                                        {

                                          QString colFilterR=colArC[KolZahl][callrw];
                                          QString colFilter = colFilterR.replace("'", "\\'");
                                          //qDebug() << colFilter;




                                          QString IDNumber = IDsAr[callrw+ccounter];
                                          //qDebug() << IDNumber ;
                                                      //qDebug() <<  zielkol  ;
                                                      //qDebug() << csvsidstr ;

                                          //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                                          //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                                          QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + csvsidstr   + "`= '" + IDNumber  + "'";
                                         //qDebug() << strup;


                                         // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                                          //qDebug() << strupd;
                                          QSqlQuery queryup(strup);
                                          queryup.exec();
                                         }





                   }
                 }

                       break;

                   case QMessageBox::Cancel:

                       break;

                 }










 ui->TableButtonS->animateClick();

}








  }



//+++END+++CSV to SQL++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++import from active db

void MainWindow::Openimpdbslot()
{

    ui->tableimpdb->clearContents();

    // QString tablenameS = ui->tableSEdit->text();
    QString tablenameS = ui->comboBoximpdb->currentText();



    if(tablenameS.trimmed().isEmpty())
                {
    QMessageBox msgBox;
    msgBox.setText("Please select a table.");
    msgBox.exec();
                 }

    else
        {


        QString strtable = "SELECT * FROM " + tablenameS;

        //qDebug() << strtable;

        QSqlQuery query(strtable);



        ui->tableimpdb->setColumnCount(query.record().count());
        ui->tableimpdb->setRowCount(query.size());


        QString colnames = "SHOW COLUMNS FROM " + tablenameS;
        //qDebug() << colnames;

        QSqlQuery querycol(colnames);

        QList<QString> colAr;

        int ncol=0;
        while (querycol.next())
            {
            QString col;
            col = querycol.value(0).toString();
            colAr.append(col);
            ncol++;
            //qDebug() << ncol;
              }

        //qDebug() << colAr;

        ui->comboBoximpdbsource->clear();
        ui->comboBoximpdbsource->addItems(colAr);
        ui->comboBoximpdbsource->setCurrentIndex(0);





        ui->tableimpdb->setHorizontalHeaderLabels(colAr);




        //QString textData;


        int index=0;
        while (query.next())
        {

            for (int coldisp = 0; coldisp < ncol; coldisp++)
            {

                QTableWidgetItem *item;


                QString foritem = query.value(coldisp).toString();
                QString su = foritem.left(500);
                //qDebug() <<  su;
                item = new QTableWidgetItem(su);

                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->tableimpdb->setItem(index,coldisp,item);

               }



        index++;
        }

    }


}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::impdbToSqlslot()
{
    QString tablenameI = ui->comboBoximpdb->currentText();
      QString activedb  = ui->comboBoxtables->currentText();







    if(
            (activedb .trimmed().isEmpty())
            |(tablenameI.trimmed().isEmpty())
      )
                {
    QMessageBox msgBox;
    msgBox.setText("Please select a table.");
    msgBox.exec();
                 }

    else
    {


    //int csvsid = ui->comboBoxCSVsid->currentIndex();
    //QString csvsidstr = ui->comboBoxCSVsid->currentText();
    QString zielkol = ui->comboBoximpdbziel->currentText();
    QString sourcekol = ui->comboBoximpdbsource->currentText();
    int zielk = ui->comboBoximpdbziel->currentIndex();

    int setstart;

    QString setstartcheck = ui->lineEditFirstIDimpdb->text();


    if(
            (ui->checkBoxSetIDdb->isChecked())
            &(setstartcheck=="")
            )
   {


       QMessageBox msgBox;
       msgBox.setText("Error: Number for first row missing.");
       msgBox.exec();
       return;


   }

    if(zielk==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error: ID column cannot be overwritten.");
        msgBox.exec();

    }
    else if(
           ~(zielk==0)
            &(zielkol==sourcekol)
            &(tablenameI == activedb )
            )
    {
        QMessageBox msgBox;
        msgBox.setText("Error: Source and target column are the same.");
        msgBox.exec();

    }

  else


 {


        QMessageBox msgBox;
               msgBox.setText("Warning: This will overwrite data of the target column.");
               msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
               msgBox.setDefaultButton(QMessageBox::Ok);
               //msgBox.exec();
               int ret = msgBox.exec();

               switch (ret)
               {
                 case QMessageBox::Ok:
               {







        QString strtable = "SELECT * FROM " + tablenameI;

        //qDebug() << strtable;

        QSqlQuery queryI(strtable);





    //int indxEQES = ui->comboBoxEQES->currentIndex();







   QString colnamesS = "SHOW COLUMNS FROM " + activedb;
           //qDebug() << colnames;

           QSqlQuery querycolS(colnamesS);


           int KolZahl = querycolS.size();


           QList<QString> colAr;



           int ncolS=0;
           while (querycolS.next())
               {
               QString colS;
               colS = querycolS.value(0).toString();
               colAr.append(colS);
               ncolS++;
               //qDebug() << ncol;
                 }



QString sidtarget =  colAr[0];



           QString colnamesI = "SHOW COLUMNS FROM " + tablenameI;
                   //qDebug() << colnames;

                   QSqlQuery querycolI(colnamesI);


                   int KolZahlI = querycolI.size();



                   ui->tableimpdb->setColumnCount(KolZahlI);


                   QList<QString> colArI;



                   int ncolI=0;
                   while (querycolI.next())
                       {
                       QString colI;
                       colI = querycolI.value(0).toString();
                       colArI.append(colI);
                       ncolI++;
                       //qDebug() << ncol;
                         }

QString sidsource =  colArI[0];




//+++++++++++++vector+++++++++++++++++++++++++++++

   QVector<QStringList> colArV(KolZahlI);

        //qDebug() << indxC1;
        //qDebug() << indxC2;

              //int index=0;
              while (queryI.next())
                  //for(int index=0;index < RowZahlS; index++)
              {

                  for (int coldisp = 0; coldisp < KolZahlI; coldisp++)
                  //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                  {

                      QString boxAll = queryI.value(coldisp).toString();
                      colArV[coldisp].append(boxAll);
                      //qDebug() << "index";
                      //qDebug() <<  index;
                      //qDebug() << "coldisp";
                      //qDebug() << coldisp;
                         //qDebug() << boxAll;

                     }

              //index++;
              }



//call string array
//get id and write vector


if(
        ~(ui->checkBoxSetIDdb->isChecked())
   )

 {

     setstart = 0;


}
if(
        (ui->checkBoxSetIDdb->isChecked())
   )

{
     setstart = ui->lineEditFirstIDimpdb->text().toInt();
}
 //qDebug() << "setstart";
 //qDebug() << setstart;



QString zeilecountSq = "SELECT COUNT(*) FROM " + tablenameI;
QString rowzahls = "SELECT COUNT(*) FROM " + activedb;

QSqlQuery queryc(rowzahls);
 int rowzahl;

             while (queryc.next())
             {


             rowzahl = queryc.value(0).toInt();

             }


             QSqlQuery queryci(zeilecountSq);
              int zeilecountS;

                          while (queryci.next())
                          {


                          zeilecountS = queryci.value(0).toInt();

                          }


          //qDebug() << "rowzahl";
           //qDebug() << rowzahl;

if(zeilecountS > rowzahl-setstart)
{

    int missingrows = zeilecountS - (rowzahl-setstart);
    QMessageBox msgBox;
    msgBox.setText("Adding rows.");
    msgBox.exec();

    for (int callzeile = 0; callzeile < missingrows/2+1; callzeile++)

    {


      QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
      //qDebug() << strupd;
      QSqlQuery queryupd(strupd);
      queryupd.exec();
     }
//in adding rows


    //int koldisp1 = ui->spinBoxCSVCol->value();
    //int KolZahl = koldisp1 -1;
    int KolZahl = ui->comboBoximpdbsource->currentIndex();
    qDebug() << KolZahl;




    //ID
    QList<QString> IDsAr;
    QString strtable = "SELECT * FROM " + activedb;

    //qDebug() << strtable;

    QSqlQuery queryid(strtable);



             int indexts=0;
                 while (queryid.next())
                 {
                 //qDebug() << querytables;

                     QString getid = queryid.value(0).toString();
                     IDsAr.append(getid);

                     //qDebug() << getid;

                     //qDebug() << col;
                   indexts++;

                 }

                 int ccounter=0;
                 if(ui->checkBoxSetIDdb->isChecked())

                  {

                      ccounter = setstart-1;


                 }




                 for (int callrw = 0; callrw < zeilecountS; callrw++)
                 //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                 {

                   QString colFilterR=colArV[KolZahl][callrw];
                   QString colFilter = colFilterR.replace("'", "\\'");
                   //qDebug() << colFilter;




                   QString IDNumber = IDsAr[callrw+ccounter];
                   //qDebug() << IDNumber ;
                               //qDebug() <<  zielkol  ;
                               //qDebug() << csvsidstr ;

                   //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                   //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                   QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + sidtarget   + "`= '" + IDNumber  + "'";
                  //qDebug() << strup;


                  // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                   //qDebug() << strupd;
                   QSqlQuery queryup(strup);
                   queryup.exec();
                  }


//end in adding rows
}
else
{




//int koldisp1 = ui->spinBoxCSVCol->value();
//int KolZahl = koldisp1 -1;
//qDebug() << KolZahl;
int KolZahl = ui->comboBoximpdbsource->currentIndex();
qDebug() << KolZahl;


 /*if(ui->checkBoxAddLines->isChecked())
 {

        for (int callzeile = 0; callzeile < anzdiff/2+1; callzeile++)
        //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
        {


          QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
          //qDebug() << strupd;
          QSqlQuery queryupd(strupd);
          queryupd.exec();
         }
  }*/


//ID
QList<QString> IDsAr;
QString strtable = "SELECT * FROM " + activedb;

//qDebug() << strtable;

QSqlQuery queryid(strtable);



         int indexts=0;
             while (queryid.next())
             {
             //qDebug() << querytables;

                 QString getid = queryid.value(0).toString();
                 IDsAr.append(getid);

                 //qDebug() << getid;

                 //qDebug() << col;
               indexts++;

             }

             int ccounter=0;
             if(ui->checkBoxSetIDdb->isChecked())

              {

                  ccounter = setstart-1;


             }




             for (int callrw = 0; callrw < zeilecountS; callrw++)
             //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
             {

               QString colFilterR=colArV[KolZahl][callrw];
               QString colFilter = colFilterR.replace("'", "\\'");
               //qDebug() << colFilter;




               QString IDNumber = IDsAr[callrw+ccounter];
               //qDebug() << IDNumber ;
                           //qDebug() <<  zielkol  ;
                           //qDebug() << csvsidstr ;

               //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


               //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

               QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + sidtarget   + "`= '" + IDNumber  + "'";
              //qDebug() << strup;


              // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

               //qDebug() << strupd;
               QSqlQuery queryup(strup);
               queryup.exec();
              }





}

ui->TableButtonS->animateClick();

               }

                   break;

               case QMessageBox::Cancel:

                   break;

             }


}
    //
    }









    //end-----------------------------------------------------------


}



//end of +++++++++import from active db


//+++++++++++FREQU++++++++++++++++++++++++++++++++++++++++


void MainWindow::frequslot()
{

    ui->tableWidgetFrequ->clearContents();

int FreColint = ui->comboBoxFrequ->currentIndex();
QString FreCol = ui->comboBoxFrequ->currentText();
QString tablenameS = ui->comboBoxtables->currentText();




//SELECT GID FROM `StringDB`.`Glossary1`;


       QString fcol = "SELECT " + FreCol + " FROM `" + tablenameS + "`;";
       //qDebug() << fcol;

       QSqlQuery querycol(fcol);

       //QList<QString> colFr;
        QString colFr;

       int ncol=0;
       while (querycol.next())
           {
           QString col;
           col = querycol.value(0).toString();
           //colFr.append(col);
           colFr += col;
           ncol++;
           //qDebug() << ncol;
             }


       colFr.remove(QRegExp("[^a-zA-Z\\d\\s]"));

       QStringList colList;

       colList << colFr.split(" ");

         int elemente = colList.count();



//
         QMap<QString, int> map;

           for (int eleNR = 0; eleNR < elemente; eleNR++)
           //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
           {

               QString listcall=colList[eleNR];

                int anzahl = (colFr.count(listcall));
                map[listcall] = anzahl;             

             }


           //sort

           QList<int> listi = map.values();


           QSet<int> seti = listi.toSet();
           QList<int> listii = seti.toList();
           qSort(listii.begin(), listii.end());

             int setzahl = listii.count();


           QStringList listk = map.keys();
           qSort(listk.begin(), listk.end());



           //qDebug() << map;
           //qDebug() << listii;
               //qDebug() << setzahl;
           //qDebug() << listk;

            int elementei = listi.count();
             int elementek = listk.count();

             //qDebug() << elementei;
             //qDebug() << elementek;


             ui->tableWidgetFrequ->setColumnCount(3);
             ui->tableWidgetFrequ->setRowCount(elementek);

                QVector<QStringList> ArItems(2);


 QList<QPair<int,QString> > lpair;




                                       int   iexo;

                                       QMap<QString, int>::const_iterator i = map.constBegin();
                                       while (i != map.constEnd())
                                       {

                                           QString keyi = i.key();
                                           int vali = i.value();
                                            lpair.append(qMakePair(vali, keyi));


                                           //qDebug() << "sortr";
                                                     //qDebug() << sortr;
                                                    //qDebug() << keyi;
                                                    //qDebug() << "vali";
                                                                 //qDebug() << vali;


                                                 ++i;
                                            ++iexo;

                                          }



qSort(lpair.begin(), lpair.end());

//qDebug() << lpair;


//tableWidgetFrequ



for (int sortr = 0 ; sortr < elementek  ; ++sortr)
                 {

    int dzahl = lpair[sortr].first ;

    QString dzahli = QString::number(dzahl);

    QString dterm = lpair[sortr].second ;
     //qDebug() << dzahl;
    //qDebug() << dterm;



    QTableWidgetItem *item;
              item = new QTableWidgetItem(dzahli);
              item->setFlags(item->flags() & ~Qt::ItemIsEditable);
              ui->tableWidgetFrequ->setItem(sortr,2,item);

              QTableWidgetItem *itemk;
                        itemk = new QTableWidgetItem(dterm);
                        itemk->setFlags(itemk->flags() & ~Qt::ItemIsEditable);
                        ui->tableWidgetFrequ->setItem(sortr,1,itemk);


                        //QTableWidgetItem *item2 = new QTableWidgetItem("");
                        //item2->setCheckState(Qt::Unchecked);
                        //ui->tableWidgetFrequ->setItem(sortr, 0, item2);


                        QCheckBox *cb= new QCheckBox();
                        ui->tableWidgetFrequ->setCellWidget(sortr, 0, cb);
                        cb->setCheckState(Qt::Unchecked);

                }

}

//++ save selection to sql

void MainWindow::creategcslot()
{


      int sid = ui->comboBoxCreateID->currentIndex();
      QString sidstr = ui->comboBoxCreateID->currentText();
      QString zielkol = ui->comboBoxGCziel->currentText();
      QString activedb = ui->comboBoxtables->currentText();
      //int setstart = ui->lineEditFirstIDGC->text().toInt();
      int setstart;

      if(sidstr==zielkol)
         {
             QMessageBox msgBox;
             msgBox.setText("Error: ID column cannot be overwritten.");
             msgBox.exec();

         }
         else
         {


    int KolZahl = ui->tableWidgetFrequ->columnCount();
    int ReiZahl = ui->tableWidgetFrequ->rowCount();
    //qDebug() << ReiZahl;
      //QVector<QStringList> ArItems(KolZahl);
    if(
            ~(ui->checkBoxSetIDGC->isChecked())
       )

     {

         setstart = 0;


    }
    if(
            (ui->checkBoxSetIDGC->isChecked())
       )

    {
         setstart = ui->lineEditFirstIDGC->text().toInt();
    }

    //count rows with checkmark
    int rzeilec = 0;
    for (int rowc = 0 ; rowc < ReiZahl-1 ; ++rowc)
    {



        //QTableWidgetItem *zellec = ui->tableWidgetFrequ->item(rowc, 1);
        //QString zelltextc = zellec->text();

        QCheckBox *mcbc = qobject_cast<QCheckBox*>(ui->tableWidgetFrequ->cellWidget(rowc, 0));
        if(mcbc->isChecked())



            {
            //qDebug() << zelltext;



            rzeilec++;

            }

    }

        int checkedrows = rzeilec;

        //qDebug() << "checkedrows";
          //qDebug() << checkedrows;

    //end count rows with checkmark


    //if(ui->checkBoxAddLinesGC->isChecked())

        //autolines


        QString rowzahls = "SELECT COUNT(*) FROM " + activedb;

        QSqlQuery queryc(rowzahls);
         int rowzahl;




                     while (queryc.next())
                     {


                     rowzahl = queryc.value(0).toInt();

                     }


                  //qDebug() << "rowzahl";
                   //qDebug() << rowzahl;

        if(checkedrows > rowzahl-setstart)
        {

            int missingrows = checkedrows - (rowzahl-setstart);
            QMessageBox msgBox;
            msgBox.setText("Adding rows.");
            msgBox.exec();

            for (int callzeile = 0; callzeile < missingrows/2+1; callzeile++)

            {


              QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
              //qDebug() << strupd;
              QSqlQuery queryupd(strupd);
              queryupd.exec();
             }
     //in adding rows

        //end of autolines



      //ID
      QList<QString> IDsAr;
      QString strtable = "SELECT * FROM " + activedb;

      //qDebug() << strtable;

      QSqlQuery queryid(strtable);



               int indexts=0;
                   while (queryid.next())
                   {
                   //qDebug() << querytables;

                       QString getid = queryid.value(sid).toString();
                       IDsAr.append(getid);

                       //qDebug() << "getid";
                       //qDebug() << getid;


                     indexts++;

                   }




      int ccounter=0;
      if(ui->checkBoxSetIDGC->isChecked())

       {

           ccounter = setstart-1;


      }



       int rzeile = 0;
       for (int row = 0 ; row < ReiZahl-1 ; ++row)
       {



           QTableWidgetItem *zelle = ui->tableWidgetFrequ->item(row, 1);
           QString zelltext = zelle->text();

           QCheckBox *mcb = qobject_cast<QCheckBox*>(ui->tableWidgetFrequ->cellWidget(row, 0));
           if(mcb->isChecked())



               {
               //qDebug() << zelltext;

               QString IDNumber = IDsAr[rzeile+ccounter];
               //qDebug() << IDNumber ;


               //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

               QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + zelltext + "' WHERE `" + sidstr   + "`= '" + IDNumber  + "'";
              //qDebug() << strup;


               QSqlQuery queryup(strup);
               queryup.exec();

               rzeile++;

               }



               //ArItems[col].append(zelltext);

       }
}
else

        {
            //ID
            QList<QString> IDsAr;
            QString strtable = "SELECT * FROM " + activedb;

            //qDebug() << strtable;

            QSqlQuery queryid(strtable);



                     int indexts=0;
                         while (queryid.next())
                         {
                         //qDebug() << querytables;

                             QString getid = queryid.value(sid).toString();
                             IDsAr.append(getid);

                             //qDebug() << getid;

                             //qDebug() << col;
                           indexts++;

                         }




            int ccounter=0;
            if(ui->checkBoxSetIDGC->isChecked())

             {

                 ccounter = setstart-1;


            }



             int rzeile = 0;
             for (int row = 0 ; row < ReiZahl-1 ; ++row)
             {



                 QTableWidgetItem *zelle = ui->tableWidgetFrequ->item(row, 1);
                 QString zelltext = zelle->text();

                 QCheckBox *mcb = qobject_cast<QCheckBox*>(ui->tableWidgetFrequ->cellWidget(row, 0));
                 if(mcb->isChecked())



                     {
                     //qDebug() << zelltext;

                     QString IDNumber = IDsAr[rzeile+ccounter];
                     //qDebug() << IDNumber ;


                     //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                     QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + zelltext + "' WHERE `" + sidstr   + "`= '" + IDNumber  + "'";
                    //qDebug() << strup;


                     QSqlQuery queryup(strup);
                     queryup.exec();

                     rzeile++;

                     }




        }



}
 ui->TableButtonS->animateClick();
}
}

//+++++++++++ END of Frequ+++++++++++++++++++++++++++++++++++++++++++


//++++++++++ search db++++++++++++++++++++++++++++
void MainWindow::searchdbslot()
{

        int zeilecountS = 0;

    ui->tableWidgetSDB->clearContents();

    ui->tableWidgetSDB->setColumnCount(4);




    QStringList horzHeaders;
    horzHeaders << "Table" << "ID" << "Column" << "Content (beginning)";
    ui->tableWidgetSDB->setHorizontalHeaderLabels( horzHeaders );

   //QString dbname = ui->databaseqle->currentText();




   //int indxC1 = ui->comboBoxC1->currentIndex();



   QString filterin = ui->filterinputSDB->text();


   //qDebug() << filterin;



   QSqlQuery querytables("SHOW TABLES");


   QList<QString> tablsAr;


   int indexts=0;
   while (querytables.next())
   {
   //qDebug() << querytables;
       QString tabls;
       tabls = querytables.value(0).toString();
       tablsAr.append(tabls);

       //qDebug() << tabls;

       //qDebug() << col;
     indexts++;

   }


   for (int tab = 0; tab < indexts; tab++)

   {
       QString tablenameS = tablsAr[tab];
       //qDebug() << tablenameS ;

       QString strtable = "SELECT * FROM " + tablenameS;










       //qDebug() << strtable;

       QSqlQuery queryS(strtable);
       // QSqlQuery querytables("SHOW TABLES");

        QString colnames = "SHOW COLUMNS FROM " + tablenameS;
        //qDebug() << colnames;

        QSqlQuery querycol(colnames);

      int KolZahl = querycol.size();



      QVector<QStringList> colArV(KolZahl);



            int index=0;
            while (queryS.next())
            {

                for (int coldisp = 0; coldisp < querycol.size(); coldisp++)
                //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                {

                    QString boxAll = queryS.value(coldisp).toString();
                    colArV[coldisp].append(boxAll);
                    /*qDebug() << "index";
                    qDebug() <<  index;
                    qDebug() << "coldisp";
                    qDebug() << coldisp;
                       qDebug() << boxAll;*/

                   }

            index++;
            }

  //+++++++++++++++++++++++++++++call string array

  int kolnummer=0;

  //while (querycol.next())
  while (kolnummer < KolZahl)

  {


      int itemnummer = 0;
      while (itemnummer < queryS.size())

          //for (int na = 0; na = 10; na ++)

       {
                  QString colFilterE=colArV[kolnummer][itemnummer];


                  QString colFilter;
                  int mesoInS;
                  int mesoSens;
                  QString boundind;
                  QRegExp rxtswvCI(filterin);
                  QRegExp rxtswvCS(filterin);
                  //QString colE1=colArV[2][itemnummer];

                                //qDebug() << colFilter;

                                //remove line breaks
                               if(
                                       (ui->checkBoxILBSDB->isChecked())

                                  )
                               {

                                   colFilter = colFilterE.replace(QString("\\n"), QString(" "));
                                   colFilter = colFilterE.replace(QString("\\r"), QString(""));
                                   //qDebug() << colFilter;
                               }

                               else
                               {
                                   colFilter=colFilterE;
                               }





                                 //match entire string
                               if(
                                      (ui->checkBoxMESOSDB->isChecked())
                                  )
                               {
                               mesoInS = QString::compare(colFilter, filterin, Qt::CaseInsensitive);
                               mesoSens = QString::compare(colFilter, filterin, Qt::CaseSensitive);
                               }


                                   //MATCH ENTIRE WORD ONLY
                               if(
                                       (ui->checkBoxMEWOSDB->isChecked())
                                   )
                               {

                               QRegExp rxsid("\\b(" + filterin + ")\\b");
                               rxsid.setCaseSensitivity(Qt::CaseInsensitive);
                               rxsid.indexIn(colFilter);
                               boundind = rxsid.cap(0);
                               //qDebug() <<  boundind;
                                }

                               //Wildcard
                               if(
                                       (ui->checkBoxWildSDB->isChecked())
                                   )
                               {
                                   rxtswvCI.setCaseSensitivity(Qt::CaseInsensitive);
                                   rxtswvCI.setPatternSyntax(QRegExp::Wildcard);
                                   rxtswvCS.setCaseSensitivity(Qt::CaseSensitive);
                                   rxtswvCS.setPatternSyntax(QRegExp::Wildcard);
                                }


                                if (
                                        (

                                            ~(ui->checkBoxMCSDB->isChecked())&
                                             ~(ui->checkBoxMESOSDB->isChecked())&
                                            ~(ui->checkBoxMEWOSDB->isChecked())&
                                        (colFilter.contains(filterin, Qt::CaseInsensitive))
                                            )|

                                        (

                                            (ui->checkBoxMCSDB->isChecked())&
                                           ~(ui->checkBoxMESOSDB->isChecked())&
                                            ~(ui->checkBoxMEWOSDB->isChecked())&
                                        (colFilter.contains(filterin, Qt::CaseSensitive))
                                            )|

                                           (

                                            (ui->checkBoxMESOSDB->isChecked())&
                                            ~(ui->checkBoxMCSDB->isChecked())&
                                            (mesoInS==0)
                                            )|
                                        (

                                         (ui->checkBoxMESOSDB->isChecked())&
                                         (ui->checkBoxMCSDB->isChecked())&
                                         (mesoSens==0)
                                         )|
                                        (

                                        (ui->checkBoxMEWOSDB->isChecked())
                                        & ~(ui->checkBoxMCSDB->isChecked())
                                        & (boundind != "")
                                        & (colFilter.contains(filterin, Qt::CaseInsensitive))
                                         )|
                                        (

                                        (ui->checkBoxMEWOSDB->isChecked())
                                        & (ui->checkBoxMCSDB->isChecked())
                                        & (boundind != "")
                                        & (colFilter.contains(filterin, Qt::CaseSensitive))
                                         )|
                                        (

                                        ~(ui->checkBoxMCSDB->isChecked())
                                        &(ui->checkBoxWildSDB->isChecked())
                                        & (rxtswvCI.exactMatch(colFilter))
                                         )|
                                        (

                                        (ui->checkBoxMCSDB->isChecked())
                                        &(ui->checkBoxWildSDB->isChecked())
                                        & (rxtswvCS.exactMatch(colFilter))
                                         )





                                    )
                                          {
                                                //qDebug() << "yes";
                                                //qDebug() << itemnummer;
                                                //qDebug() << KolZahl;
                                                //QString colEp=colArV[spalte][itemnummer];

                                                //zeilecountS++;
                                           //size of filter output
                                                 ui->tableWidgetSDB->setRowCount(zeilecountS+1);

                                                //for (int spalte=0; spalte<KolZahl; spalte++)

                                                      //{
                                                      //QString colEp=colArV[spalte][itemnummer];
                                                    //qDebug() << "spalte";
                                                        //qDebug() << spalte;
                                                         QString colip=colArV[0][itemnummer];

                                                          ui->tableWidgetSDB->setItem(zeilecountS,0,new QTableWidgetItem(tablenameS));
                                                          ui->tableWidgetSDB->setItem(zeilecountS,1,new QTableWidgetItem(colip));
                                                          int rkn = kolnummer+1;
                                                          QString kn = QString::number(rkn);
                                                           //qDebug() <<  kn;

                                                           ui->tableWidgetSDB->setItem(zeilecountS,2,new QTableWidgetItem(kn));
                                                          QString su = colFilter.left(500);
                                                          ui->tableWidgetSDB->setItem(zeilecountS,3,new QTableWidgetItem(su));
                                                          //QString colEp=colArV[0][0];
                                                         //qDebug() << colEp;
                                                        //qDebug() << "item";
                                                        //qDebug() << itemnummer;
                                                        //qDebug() << "kolzahl";
                                                        //qDebug() << KolZahl;


                                                      // }
                                           zeilecountS++;
                                             }



                  itemnummer++;


       }


kolnummer++;
}

}

}


//++++++end of search db+++++++++++++++++++++++++++

//+++++++++txt++++++++++++++

//export--------------------------------------
void MainWindow::savetxtslot()
{

    QMessageBox msgBox;
    msgBox.setText("Cell separator: line break.");
    msgBox.exec();

    QString coltotxt = ui->comboBoxtxtExport->currentText();

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    //QString csvname = ui->filenamesave->text();

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/stallman/untitled.txt",
                               tr("txt (*.txt)"));

   /* QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();*/


    QString tablenameS = ui->comboBoxtables->currentText();

    if(tablenameS.trimmed().isEmpty())
                {
    QMessageBox msgBox;
    msgBox.setText("Please select a table.");
    msgBox.exec();
                 }

    else
        {
//SELECT GID FROM `StringDB`.`GlossaryII`;

        QString strtable = "SELECT " + coltotxt + " FROM " + tablenameS;

        //qDebug() << strtable;

        QSqlQuery query(strtable);

        //QString textData;

        QFile csvFile(fileName);
        csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate);


           QString textData;

           int index=0;
           while (query.next())
           {
            //qDebug() <<index;




                 textData += query.value(0).toString();


                  textData += "\n\r";
                 index++;



                }


           QTextStream out(&csvFile);
           out << textData;

    csvFile.close();

    }

}

//import---------------------------------------------
void MainWindow::importtxtslot()
{

    int csvsid = ui->comboBoxtxtsid->currentIndex();
    QString csvsidstr = ui->comboBoxtxtsid->currentText();

    QString zielkol = ui->comboBoxtxtziel->currentText();

    QString activedb = ui->comboBoxtables->currentText();
    QString setstartcheck = ui->lineEditFirstIDtxt->text();
     int setstart;

     //
      if(
              (ui->checkBoxSetIDtxt->isChecked())
              &(setstartcheck=="")
              )
     {


         QMessageBox msgBox;
         msgBox.setText("Error: Number for first row missing.");
         msgBox.exec();
         return;


     }




    if(csvsidstr==zielkol)
    {
        QMessageBox msgBox;
        msgBox.setText("Error: ID column cannot be overwritten.");
        msgBox.exec();

    }
    else
    {


    QMessageBox msgBox;
    msgBox.setText("Cell separator: line break. Data within of the copy range will be overwritten.");
    msgBox.exec();


    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    //QString csvname = ui->filenamesave->text();


    //QStringList fileNames;
     QString fileName;
    //if (dialog.exec())
        //fileNames = dialog.selectedFiles();
    fileName = dialog.getOpenFileName() ;
    //qDebug() << fileName;






    QFile file(fileName);
      if (!file.open(QIODevice::ReadOnly))
      {
          qDebug() << "error";
          return;
      }

      QStringList wordList;
      QString ganz;
      int totalines=0;
      while (!file.atEnd())
      {
          QString line = file.readLine();
          //wordList.append(line.split(',').first());
          //wordList.append(line.split(',').at(1));

        if(
                (line!="")
                |(line!="\n")
                |(line!="\n\r")


         )
        {
          ganz += line;
          totalines++;
         }


       }




      int win = ganz.count("\n\r");
       //qDebug() <<  win;


       int lin = ganz.count("\n");
        //qDebug() <<  lin;



      ganz.replace("\n\r", "\n");
        ganz.replace("\n\n", "\n");
       ganz.replace("\n\n\n", "\n");
        ganz.replace("\n\n\n\n", "\n");
         ganz.replace("\n\n\n\n\n", "\n");
          ganz.replace("\n\n\n\n\n\n", "\n");
           ganz.replace("\n\n\n\n\n\n\n", "\n");
            ganz.replace("\n\n\n\n\n\n\n\n", "\n");
             ganz.replace("\n\n\n\n\n\n\n\n\n", "\n");
              ganz.replace("\n\n\n\n\n\n\n\n\n\n", "\n");




      int win1 = ganz.count("\n\r");
       //qDebug() <<  win1;


       int lin1 = ganz.count("\n");
        //qDebug() <<  lin1;



        int lind = ganz.count("\n\n");
         //qDebug() <<  lind;




        wordList << ganz.split("\n");


    //qDebug() << wordList;

       int elemente = wordList.count();
     //qDebug() << elemente;


           QList<QString>  colArC;

      int zeilecountS = 0;

      for (int elemNR = 0; (elemNR < elemente); elemNR ++)
      {



                      QString listcall=wordList[elemNR];
                      colArC.append(listcall);





                  zeilecountS++;


      }

    //qDebug() <<  "zeilecountS";
    //qDebug() <<  zeilecountS;


//Call array



          if(
                  ~(ui->checkBoxSetIDtxt->isChecked())
             )

           {

               setstart = 0;


          }
          if(
                  (ui->checkBoxSetIDtxt->isChecked())
             )

          {
               setstart = ui->lineEditFirstIDtxt->text().toInt();
          }
           //qDebug() << "setstart";
           //qDebug() << setstart;




          QString rowzahls = "SELECT COUNT(*) FROM " + activedb;

          QSqlQuery queryc(rowzahls);
           int rowzahl;




                       while (queryc.next())
                       {


                       rowzahl = queryc.value(0).toInt();

                       }


                    //qDebug() << "rowzahl";
                     //qDebug() << rowzahl;

          if(zeilecountS > rowzahl-setstart)
          {

              int missingrows = zeilecountS - (rowzahl-setstart);
              QMessageBox msgBox;
              msgBox.setText("Adding rows.");
              msgBox.exec();

              for (int callzeile = 0; callzeile < missingrows/2+1; callzeile++)

              {


                QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
                //qDebug() << strupd;
                QSqlQuery queryupd(strupd);
                queryupd.exec();
               }

  //in add lines
              QList<QString> IDsAr;
              QString strtable = "SELECT * FROM " + activedb;

              //qDebug() << strtable;

              QSqlQuery queryid(strtable);



                       int indexts=0;
                           while (queryid.next())
                           {
                           //qDebug() << querytables;

                               QString getid = queryid.value(csvsid).toString();
                               IDsAr.append(getid);

                               //qDebug() << getid;

                               //qDebug() << col;
                             indexts++;

                           }

                           int ccounter=0;
                           if(ui->checkBoxSetIDtxt->isChecked())

                            {

                                ccounter = setstart-1;


                           }




                           for (int callrw = 0; callrw < elemente; callrw++)
                           //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                           {

                             QString colFilterR=colArC[callrw];

                             QString colFilter = colFilterR.replace("'", "\\'");
                             //qDebug() << colFilter;




                             QString IDNumber = IDsAr[callrw+ccounter];
                             //qDebug() << IDNumber ;
                                         //qDebug() <<  zielkol  ;
                                         //qDebug() << csvsidstr ;

                             //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                             //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                             QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + csvsidstr   + "`= '" + IDNumber  + "'";
                            //qDebug() << strup;


                            // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                             //qDebug() << strupd;
                             QSqlQuery queryup(strup);
                             queryup.exec();
                            }





  //end in add lines
          }
          else
          {

//
           /*if(ui->checkBoxAddLinestxt->isChecked())
           {

                  for (int callzeile = 0; callzeile < elemente; callzeile++)
                  //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                  {


                    QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES (''); SELECT LAST_INSERT_ID();";
                    //qDebug() << strupd;
                    QSqlQuery queryupd(strupd);
                    queryupd.exec();
                   }
            }*/


          //ID
          QList<QString> IDsAr;
          QString strtable = "SELECT * FROM " + activedb;

          //qDebug() << strtable;

          QSqlQuery queryid(strtable);



                   int indexts=0;
                       while (queryid.next())
                       {
                       //qDebug() << querytables;

                           QString getid = queryid.value(csvsid).toString();
                           IDsAr.append(getid);

                           //qDebug() << getid;

                           //qDebug() << col;
                         indexts++;

                       }

                       int ccounter=0;
                       if(ui->checkBoxSetIDtxt->isChecked())

                        {

                            ccounter = setstart-1;


                       }

                        //qDebug() << "else";


                       for (int callrw = 0; callrw < elemente; callrw++)
                       //for (int coldisp = indxC1; coldisp < indxC2+1; coldisp++)
                       {

                         QString colFilterR=colArC[callrw];

                         QString colFilter = colFilterR.replace("'", "\\'");
                         //qDebug() << colFilter;




                         QString IDNumber = IDsAr[callrw+ccounter];
                         //qDebug() << IDNumber ;
                                     //qDebug() <<  zielkol  ;
                                     //qDebug() << csvsidstr ;

                         //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                         //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                         QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + csvsidstr   + "`= '" + IDNumber  + "'";
                        //qDebug() << strup;


                        // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                         //qDebug() << strupd;
                         QSqlQuery queryup(strup);
                         queryup.exec();
                        }








}
ui->TableButtonS->animateClick();
}


  }

//txt to cell

//void MainWindow::importtxtcellslot()
/*
{
    int csvsid = ui->comboBoxtxtsid->currentIndex();
    QString csvsidstr = ui->comboBoxtxtsid->currentText();

    QString zielkol = ui->comboBoxtxtziel->currentText();

    QString activedb = ui->comboBoxtables->currentText();
    //int setstart = ui->lineEditFirstIDtxt->text().toInt();

    QString sline = ui->lineEditIDtxtCell->text();
    //qDebug() <<  sline;


    int setstart;

    setstart = ui->lineEditIDtxtCell->text().toInt();




    QString rowzahls = "SELECT COUNT(*) FROM " + activedb;

    QSqlQuery queryc(rowzahls);
     int rowzahl;




                 while (queryc.next())
                 {


                 rowzahl = queryc.value(0).toInt();

                 }


                 int rowz =   rowzahl;


              //qDebug() << "rowzahl";
               //qDebug() << rowzahl;

     if(csvsidstr==zielkol)
     {
         QMessageBox msgBox;
         msgBox.setText("Error: ID column cannot be overwritten.");
         msgBox.exec();

     }

    else if(
            (setstart > rowz)
            |(setstart < 1)
            )
    {


        QMessageBox msgBox;
        msgBox.setText("Error: Row not found.");
        msgBox.exec();


    }
    else

    {


    QMessageBox msgBox;
    msgBox.setText("Target cell: Column: " + zielkol + ". Row: " + sline + ". All data in this cell will be overwritten.");
    msgBox.exec();


    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
   // dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    //QString csvname = ui->filenamesave->text();


    //QStringList fileNames;
     QString fileName;
    //if (dialog.exec())
        //fileNames = dialog.selectedFiles();
    fileName = dialog.getOpenFileName() ;
    //qDebug() << fileName;






    QFile file(fileName);
      if (!file.open(QIODevice::ReadOnly))
      {
          qDebug() << "error";
          return;
      }

      QStringList wordList;
      QString ganz;
      int totalines=0;
      while (!file.atEnd())
      {
          QString line = file.readLine();
          //wordList.append(line.split(',').first());
          //wordList.append(line.split(',').at(1));


          ganz += line;
          totalines++;






//Call array





          //ID
          QList<QString> IDsAr;
          QString strtable = "SELECT * FROM " + activedb;

          //qDebug() << strtable;

          QSqlQuery queryid(strtable);



                   int indexts=0;
                       while (queryid.next())
                       {
                       //qDebug() << querytables;

                           QString getid = queryid.value(csvsid).toString();
                           IDsAr.append(getid);

                           //qDebug() << getid;

                           //qDebug() << col;
                         indexts++;

                       }


                          int  ccounter = setstart-1;









                         QString colFilterR=ganz;

                         QString colFilter = colFilterR.replace("'", "\\'");
                         //qDebug() << colFilter;




                         QString IDNumber = IDsAr[ccounter];
                         //qDebug() << IDNumber ;
                                     //qDebug() <<  zielkol  ;
                                     //qDebug() << csvsidstr ;

                         //QString IDresult = QString::number(IDNumber).rightJustified(8, '0');


                         //UPDATE `StringsIII` SET `TS`='34985' WHERE `SID`='SID00007';

                         QString strup = "UPDATE `" + activedb + "` SET `" + zielkol  + "`='" + colFilter + "' WHERE `" + csvsidstr   + "`= '" + IDNumber  + "'";
                        //qDebug() << strup;


                        // QString strupd = "INSERT INTO " + activedb + " (" + zielkol  + ") VALUES ('" + colFilter + "'); SELECT LAST_INSERT_ID();";

                         //qDebug() << strupd;
                         QSqlQuery queryup(strup);
                         queryup.exec();









}
ui->TableButtonS->animateClick();
}
}
*/


//end of txt to cell



//++++++end of txt++++++++++++



void MainWindow::markslot()
{

    if (
            (ui->radioButtonMark1->isChecked())
        )

     {
        QPalette p = ui->ref1TextEdit->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->ref1TextEdit->setPalette(p);


        QString searchString = ui->lineEditMark->text();

          ui->ref1TextEdit->find(searchString);
    }


    if (
            (ui->radioButtonMark2->isChecked())
        )

    {
        QPalette p = ui->TextEdit->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEdit->setPalette(p);

        QString searchString = ui->lineEditMark->text();

          ui->TextEdit->find(searchString);
    }





}


void MainWindow::backmarkslot()
{


    if (
            (ui->radioButtonMark1->isChecked())
        )
    {

        QPalette p = ui->ref1TextEdit->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->ref1TextEdit->setPalette(p);

        ui->ref1TextEdit->find(ui->lineEditMark->text(),QTextDocument::FindBackward);
    }

    if (
            (ui->radioButtonMark2->isChecked())
        )
    {

        QPalette p = ui->TextEdit->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEdit->setPalette(p);

        ui->TextEdit->find(ui->lineEditMark->text(),QTextDocument::FindBackward);
    }


}

//admin
void MainWindow::markslotadmin()
{

    QPalette p = ui->RefTextEdit->palette();
    p.setColor(QPalette::Highlight, QColor(Qt::yellow));
    p.setColor(QPalette::HighlightedText, QColor(Qt::black));
    ui->RefTextEdit->setPalette(p);



    QString searchString = ui->lineEditMarkAdm->text();



      ui->RefTextEdit->find(searchString);




}


void MainWindow::backmarkslotadmin()
{

    QPalette p = ui->RefTextEdit->palette();
    p.setColor(QPalette::Highlight, QColor(Qt::yellow));
    p.setColor(QPalette::HighlightedText, QColor(Qt::black));
    ui->RefTextEdit->setPalette(p);

       ui->RefTextEdit->find(ui->lineEditMarkAdm->text(),QTextDocument::FindBackward);



}


//history
void MainWindow::markslothis()
{


    QPalette p = ui->TextEditHis->palette();
    p.setColor(QPalette::Highlight, QColor(Qt::yellow));
    p.setColor(QPalette::HighlightedText, QColor(Qt::black));
    ui->TextEditHis->setPalette(p);

    QString searchString = ui->lineEditMarkHIS->text();



      ui->TextEditHis->find(searchString);




}


void MainWindow::backmarkslothis()
{

    QPalette p = ui->TextEditHis->palette();
    p.setColor(QPalette::Highlight, QColor(Qt::yellow));
    p.setColor(QPalette::HighlightedText, QColor(Qt::black));
    ui->TextEditHis->setPalette(p);

       ui->TextEditHis->find(ui->lineEditMarkHIS->text(),QTextDocument::FindBackward);



}


//meta
void MainWindow::markslotmeta()
{

    if (
            (ui->radioButtonMarkM1->isChecked())
        )
    {

        QPalette p = ui->TextEditStat->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEditStat->setPalette(p);

        QString searchString = ui->lineEditMarkMeta->text();

          ui->TextEditStat->find(searchString);
    }


    if (
            (ui->radioButtonMarkM2->isChecked())
        )
    {

        QPalette p = ui->TextEditCom->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEditCom->setPalette(p);

        QString searchString = ui->lineEditMarkMeta->text();

          ui->TextEditCom->find(searchString);
    }




}


void MainWindow::backmarkslotmeta()
{



    if (
            (ui->radioButtonMarkM1->isChecked())
        )
    {

        QPalette p = ui->TextEditStat->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEditStat->setPalette(p);

        ui->TextEditStat->find(ui->lineEditMarkMeta->text(),QTextDocument::FindBackward);
    }

    if (
            (ui->radioButtonMarkM2->isChecked())
        )
    {
        QPalette p = ui->TextEditCom->palette();
        p.setColor(QPalette::Highlight, QColor(Qt::yellow));
        p.setColor(QPalette::HighlightedText, QColor(Qt::black));
        ui->TextEditCom->setPalette(p);

        ui->TextEditCom->find(ui->lineEditMarkMeta->text(),QTextDocument::FindBackward);
    }




}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++
//Quickfilter for Table (not in use)
/*

void MainWindow::quickresetslot()
{

        ui->GCButton->animateClick();

}

void MainWindow::findslot()
{
    //ui->GCButton->animateClick();
    QString findin = ui->findinput->text();
    if(findin=="")
    {
     return;
    }


    //ui->tableAll->setColumnCount(KolZahl);

            int KolZahl = ui->tableAll->columnCount();
            int ReiZahl = ui->tableAll->rowCount();
            //qDebug() << KolZahl;
              QVector<QStringList> ArItems(KolZahl);
               for (int row = 0 ; row < ReiZahl ; ++row)
               {
                   for (int col = 0; col < KolZahl; col++)
                     {
                       QTableWidgetItem *zelle = ui->tableAll->item(row, col);
                       QString zelltext = zelle->text();
                       ArItems[col].append(zelltext);
                      }
               }

 ui->tableAll->clearContents();

//call array
 qDebug() << KolZahl;
 qDebug() << ReiZahl;

   int zeilecountS = 0;
 for (int rei = 0 ; rei < ReiZahl ; ++rei)

   {



      for (int kol = 0; kol < KolZahl; kol++)

           //for (int na = 0; na = 10; na ++)

        {
                   QString colFilter=ArItems[kol][rei];
                   //qDebug() << colFilter;


                                    if (
                                        (colFilter.contains(findin, Qt::CaseInsensitive))
                                        )

                                    {

                                                ui->tableAll->setRowCount(zeilecountS+10);

                                                for (int spalte=0; spalte<KolZahl; spalte++)

                                                      {
                                                      //QString colEp=colArV[spalte][itemnummer];
                                                    //qDebug() << "spalte";
                                                        //qDebug() << spalte;
                                                         QString colEp=ArItems[spalte][rei];

                                                          ui->tableAll->setItem(zeilecountS,spalte,new QTableWidgetItem(colEp));
                                                          //QString colEp=colArV[0][0];
                                                         //qDebug() << colEp;
                                                        //qDebug() << "item";
                                                        //qDebug() << itemnummer;
                                                        //qDebug() << "kolzahl";
                                                        //qDebug() << KolZahl;


                                                     }
                                                   zeilecountS++;
                                             }

       }
}

}

*/
//+++++++++++++END of Quickfilter for table (not in use)









/*
+++++++++++++++++++++++SQL++
++++++++++++++++++++++++++++
Unicode in mysql and qt:
ALTER SCHEMA `StringDB`  DEFAULT CHARACTER SET utf8  DEFAULT COLLATE utf8_unicode_ci ;

DELETE FROM `StringDB`.`GlossaryII` WHERE `GID`='GID00012';
*/



/*
//+++++++++++++++remote connection
Connection to MySQL server in network:
1)
change in the my.cnf file (etc/mysql) the line bind-address:
bind-address=<type here the ip of the remote server>
2)
sudo ufw allow out 3306/tcp
sudo ufw allow in 3306/tcp
3)
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '<type password here>' WITH GRANT OPTION;
 */









MainWindow::~MainWindow()
{
    delete ui;
}
















