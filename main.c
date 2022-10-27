#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "SHT3x.h"


// Create I2C bus
static int file;
char *bus = "/dev/i2c-1";
double temp;
double humidity;
 
 
int main() 
{

	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	ioctl(file, I2C_SLAVE, 0x44);	
	SHT3x_Results_t SHT3x;

	while(1)
	{
		SHT3x = getReadings(file);
		printf("Temp = %f		Humidity = %f\n", SHT3x.temp , SHT3x.humidity);
	}
}







