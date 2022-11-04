#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "SHT3x.h"


// Create I2C bus
uint8_t fd;
double temp;
double humidity;
 
 
int main() 
{

	if(gpioInitialise() < 0) 
	{
		printf("Failed to open the bus. \n");
	}	
	fd = i2cOpen(1, DEVICE_ADDRESS, 0);
	SHT3x_Results_t SHT3x;

	while(1)
	{
		SHT3x = getReadings(fd);
		printf("Temp = %f		Humidity = %f\n", SHT3x.temp , SHT3x.humidity);
	}
}








