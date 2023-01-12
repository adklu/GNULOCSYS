## GNULOCSYS Linguistic database management system

v1.9.5p


### Content

A) REQUIRED

B) INSTALL



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

- GUI database management system 
- glossary filter
- dual editor view
- external and internal search 
- multiple import/export functions 
- MySQL
- GUI to create and copy tables, add, move and copy columns/name or rename columns. 
- non-destructive
- import from text file (txt) or spreadsheet (csv, xlsx via XLSX TOOL FOR GNULOCSYS) or other tables of the database. 
- History", input of meta information, status notes, comments

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

GRANT ALL PRIVILEGES ON *.* TO 'type MySQL username here'@'%' IDENTIFIED BY 'type password here' WITH GRANT OPTION;
    
 
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
 



Copyright (C) 2016 A.D.Klumpp. GNULOCSYS is released under the terms of the GNU General Public License (v3). GNULOCSYS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY. The full copyright notice and the full license text shall be included in all copies or substantial portions of the Software.




