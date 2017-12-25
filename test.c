#include <iostream>
#include <mysql.h>
#include <my_global.h>

#include <unistd.h>
#include <stdio.h>
#include <cstring>

using namespace std;

#include "bmp180.h"

void finish_with_error(MYSQL *con)
{
	cout<<mysql_error(con)<<endl;
	mysql_close(con);
	exit(1);
}


int main(int argc, char **argv){



	MYSQL *con = mysql_init(NULL);
		
	if(con == NULL)
	{
		cout<<mysql_error(con)<<endl;
		exit(1);
	}
		
//	if(mysql_real_connect(con,"localhost","admin","admin","Sensor",0,NULL,0) == NULL)

	if(mysql_real_connect(con,"MySQL Server ip address","user-name","password","Sensor",0,NULL,0) == NULL)

	{
		finish_with_error(con);
	}


	const char *i2c_device = "/dev/i2c-1";
	int address = 0x77;
	
	void *bmp = bmp180_init(address, i2c_device);
	
	bmp180_eprom_t eprom;
	bmp180_dump_eprom(bmp, &eprom);
	
	
	bmp180_set_oss(bmp, 1);
	
	if(bmp != NULL)
	{
		int i;
		for(i = 0; i < 10; i++)
		{
			float t = bmp180_temperature(bmp);
			long p = bmp180_pressure(bmp);
			float alt = bmp180_altitude(bmp);
			printf("t = %f, p = %lu, a= %f\n", t, p, alt);
		
			string pre = to_string(p);
	
			string query = "insert into Detection values(NOW(),1," + pre + ")";

			//cout<<query<<endl;

			if(p > 95000 )
			{	
				if(mysql_query(con,query.c_str()))
				{
					finish_with_error(con);
				}

			}
			usleep(2 * 1000 * 1000);
		}
	
		bmp180_close(bmp);
	}

	mysql_close(con);
	
	return 0;
}

