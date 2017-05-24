#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private slots:
  void connectpressed();
  void loadpressed();
  void showtable();
  void tableS();
  void tableG();
  void GCslot();
  void gcmatchslot();
  void gclistslot();
  void filterslotS(); 
  void updateSslot();
  void updateAdslot();
  void itemChanged(int nrow, int ncol);
  void itemRef(const QModelIndex &);
  void statusslot();
  void synctablesslot();
  void savecolslot();
  void tsslot();
  void ntsslot();
  void idslot();
  void esslot();
  void saveesslot();
  void savetsslot();
  void saventsslot();
  void historyslot();
  void savehisslot();
  void hisboxslot();
  void updateSslotStat(); 
  void savecomslot();
  void savestatslot();
  void comboxslot();
  void statboxslot();
  void RenameCslot();
  void MoveCslot();
  void AddCslot();
  void RenameTslot();
  void AddTslot(); 
  void SaveC1slot();
  void SaveC2slot();
  void RangeBoxslot();
  void MESOslot();
  void MEWOslot();
  void Wildcardslot();
  void saveGIDslot();
  void saveGESslot();
  void saveGTSslot();
  void saveGSIDslot();
  void saveGSESslot();
  void saveGSTSslot();
  void Glossaryboxslot();  
  void SaveFilter2slot();
  void gcselectionslot();
  void saveslotFilterG2();
  void saveslotEQES();
  void saveslotEQTS();
  void saveslotFilterEQ();
  void EQslot();
  void EQMTslot();
  void EQNRslot();
  void savecsvslot();
  void importcsvslot();
  void savehtmlslot();
  void csvtosqlslot();
  void frequslot();
  void creategcslot();
  void gesyncslot();
  void gefilterslot();
  void searchdbslot();
  void WildcardslotSDB();
  void MEWOslotSDB();
  void MESOslotSDB();
  void savetxtslot();
  void importtxtslot();
  void itemRefy();
  void FilterCboxslot();
  void markslot();
  void backmarkslot();
  void markslotadmin();
  void backmarkslotadmin();
  void markslothis();
  void backmarkslothis();
  void markslotmeta();
  void backmarkslotmeta();
  void addrowsslot();  
  void FilterGL2slot();
  void FilterG3slot();
  void FilterEmptyslot();
  void FilterEQslot();
  void FilterEQNEslot();
  void FilterEmptyEQslot();
  void Filter2slot();
  void Filter3slot();
  void copytableslot();
  void synconlyslot();
  void copycslot();
  void Openimpdbslot();
  void impdbToSqlslot();
  void synctableGslot();
  void morecombosaveslots();
  void synctableimpdb();
  void slotfontsize();
  void slotfontsizeMin();



  //void itemChanged(const QModelIndex &index);
  //void BoxC1slot();
  //void BoxC2slot();
  //void filterslotall();
   //void filterslotG();
   //void findslot();
  // void quickresetslot();
  // void importtxtcellslot();






};

#endif // MAINWINDOW_H
