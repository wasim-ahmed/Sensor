# Sensor

This project retreives data on i2c from BMP180 sensor & update the readings to remote MYSQL Server 

Requirement: libi2c-dev for SMBUS support


Compilation :

g++ -c bmp180.c
g++ -c -std=c++11 test.c -I /usr/include/mysql

g++ -o test bmp180.o test.o -l mysqlclient -L /usr/include/mysql


