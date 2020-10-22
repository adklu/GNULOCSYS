## GNULOCSYS Linguistic database management system

v1.9.5p


### Content

A) REQUIRED

B) INSTALL

C) FIRST TIME USE

D) GUI

------------------

### A) REQUIRED

Linux (tested with Debian 9 and 10)

Qt5 (tested with Qt 5.2.1)

qt5-default

build-essential

(gtk2: qt5-style-plugins: echo "export QT_QPA_PLATFORMTHEME=gtk2" >> ~/.profile) 

qmake

GNU Autotools (automake, autoconf, configure, make)

(mesa-common-dev)

(libgl1-mesa-dev, libglu1-mesa-dev)

libmysqlclient

default-libmysqlclient-dev

libmariadbclient-dev

libqt5sql5-mysql



### B) INSTALL

- Copy Source into (replace [username]): /home/[username]/GNULOCSYS

- mark all .sh and .desktop files as executables

- ./INSTALL.sh

- Edit Desktop file (GNULOCSYS.desktop):

replace [username] in:

Exec=/home/[username]/GNULOCSYS/GNULOCSYS %F 

Icon=/home/[username]/GNULOCSYS/Icon1.png 

(To start GNULOCSYS via command (debug output in terminal): /home/[username]/GNULOCSYS/GNULOCSYS)



---------------

GNULOCSYS is a GUI text database management system that contains complex multiple terms glossary filter systems. GNULOCSYS is not limited by the constrains of common spreadsheets. One cell of GNULOCSYS can contain a whole book and one table can contain a whole library. GNULOCSYS can be used for multiple linguistic purposes, e. g. for complex translation projects. Features are dual editor view, external and internal search machines, advanced filter systems and multiple import/export functions that make linguistic manipulations and analysis of big texts easier. 

This distribution of GNULOCSYS uses the MySQL Community Edition (GPL). Install the free MySQL Community Edition (GPL) and create a MySQL user and Database (e. g. with a free GUI tool like MySQL Workbench or via command line) or use an already created MySQL database with your network or on your PC. Please refer to the MySQL documentation or ask your database administrator. 

In order to start GNULOCSYS please set the permission of the GNULOCSYS file inside of the GNULOCSYS build folder to "Allow executing file as program" and execute it.  

Connect to the MySQL database via the tab "Connect". Apart from the password, all connection data of a successful connection are saved for the next time you use the program and can be retrieved via the load button.

The ID column is the first column of every table and the IDs are the numbers of the rows (1,2,3,4...). Other kinds of IDs - like combinations of letters and numbers, e. g. "ID001", could work, but are not supported. For some tasks it is required to select the name of the ID column via the drop down menu. 

Please note that the cells of the table view display only the beginning of longer texts, the full text is displayed only inside of the editor view. In order to see the full text of the database cells please go to one of the edit views tabs and click in the table view on the cell (Admin edit) or the line (dual view).

The "SAVE" button next to the drop down menu will allow you to save the selected value. The saved selections are linked to the tables, closing GNULOCSYS will not delete your saved selection.

GNULOCSYS allows you to create and copy tables, add, move and copy columns or name or rename columns. In order to avoid accidental loss of data, GNULOCSYS will let you create, rename and move, but not delete (tables or columns). GNULOCSYS is "non-destructive", but please note that overwriting of cells with other cells is supported. If renaming, moving, overwriting is not enough in terms of deleting, please refer to the MySQL documentation for further information or ask your database administrator. 

GNULOCSYS is open to other formats and locations. You can import linguistic content from a text file (txt) or a spreadsheet (csv, xlsx via XLSX TOOL FOR GNULOCSYS) or other tables of the database. Import the columns you need into your created or import prepared project. Or just copy and paste a whole (text) book inside of a single cell (or import every paragraph of the book inside of a single cell with one mouse click). 

Use the export tools of GNULOCSYS for quick export of a column or whole tables e. g. in order to use machine translation or a spell checking solution of your choice. Please note that external spreadsheet formats (like .xlsx, which is via XLSX TOOL FOR GNULOCSYS supported) are limited in terms of the maximum text inside of a cell or the maximum number of rows.

Filter multiple columns or one column. Input whole glossary collection to find terminology issues. List all terms, which contain glossary terms or use the logic function and filter only terms with possible terminology issues. Filter multiple tables, multiple columns, one column or search inside of one single cell (which can contain a whole book). The output table gives you a statistic of found terminology including the differences of the count of terms. Use the "Click cell" check box to get search terms from the external search machine with one click on the output statistic cell inside of the cell internal search machine. Filter all lines with missing translations or number typos. 

Or create a new glossary. Use the word frequency tool of GNULOCSYS and select the terms of the new glossary. Provide the translations in the "Edit Glossary" tab or keep the one column table for later manipulations.

The dual view is perfect for translation tasks. Assign the column you want to keep as read only and the column you want to use as edit column. You can also assign the same column as read and edit column. Undo edits with Ctr & Z. The Admin view gives you Admin editing rights. Be careful!  

Activate "History", to keep track of all changes. Or assign columns for quick input of meta information as status notes or comments for localization projects. 

Example for a connection to MySQL server inside of a network:

1)

change in the my.cnf file (etc/mysql) the line bind-address:
bind-address=<type here the ip of the remote server>
    
2)

Disable the firewall for port 3306, example:

sudo ufw allow out 3306/tcp

sudo ufw allow in 3306/tcp

3)

Allow a MySQL user to access the MySQL server:

GRANT ALL PRIVILEGES ON *.* TO '<type MySQL username here>'@'%' IDENTIFIED BY '<type password here>' WITH GRANT OPTION;
    
 
Change  bind-address 

example:
 
 /etc/mysql/server.cnf  
 
 /etc/mysql/my.cnf 
 
 a) sudo gedit /etc/mysql/mariadb.conf.d/50-server.cnf
  
  
 b) replace "localhost" under  "Only allow connections from localhost" with "bind-address = 0.0.0.0"
 
To connect to database via command line:   

sudo mysql -h <MySql Server IP address> -u <username> -p

SHOW DATABASES;

SHOW TABLES;
 



GNULOCSYS is written by A.D.Klumpp. Copyright (C) 2016 A.D.Klumpp. GNULOCSYS is released under the terms of the GNU General Public License (v3). GNULOCSYS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY. The full copyright notice and the full license text shall be included in all copies or substantial portions of the Software.




