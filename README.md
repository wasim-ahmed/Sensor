# Sensor

Compilation :

g++ -c bmp180.c
g++ -c -std=c++11 test.c -I /usr/include/mysql

g++ -o test bmp180.o test.o -l mysqlclient -L /usr/include/mysql


