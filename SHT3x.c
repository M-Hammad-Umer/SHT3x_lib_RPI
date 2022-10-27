#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "SHT3x.h"

/////////////////////PRIVATE FUNCTION DECELARATION/////////////////////
static uint8_t calculate_crc(const uint8_t *data, size_t length);




/////////////////////PUBLIC FUNCTION DEFINITION/////////////////////
SHT3x_Results_t getReadings(int file)
{
    SHT3x_Results_t SHT3x;

	// Send high repeatability measurement command
	// Command msb, command lsb(0x2C, 0x06)
	char config[2] = {0};
	config[0] = 0x2C;
	config[1] = 0x06;
	write(file, config, 2);
	sleep(1);
 
	// Read 6 bytes of data
	// temp msb, temp lsb, temp CRC, humidity msb, humidity lsb, humidity CRC
	char data[6] = {0};
	if(read(file, data, 6) != 6)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		// CRC Check	
		uint8_t tempCrc = calculate_crc((uint8_t*)data, 2);	
		uint8_t humidityCrc = calculate_crc((uint8_t*)data+3, 2);
		if(tempCrc == data[2] && humidityCrc == data[5])
		{
			// Convert the data
            SHT3x.temp = (((data[0] * 256) + data[1]) * 175.0) / 65535.0  - 45.0;
            SHT3x.humidity = (((data[3] * 256) + data[4])) * 100.0 / 65535.0;
		}
		else
		{
			printf("Data may be corrupted");
		}
	}
		return SHT3x;
		
}



/////////////////////PRIVATE FUNCTION DEFINITION/////////////////////

static uint8_t calculate_crc(const uint8_t *data, size_t length)
{
	uint8_t crc = 0xff;
	for (size_t i = 0; i < length; i++) {
		crc ^= data[i];
		for (size_t j = 0; j < 8; j++) {
			if ((crc & 0x80u) != 0) {
				crc = (uint8_t)((uint8_t)(crc << 1u) ^ 0x31u);
			} else {
				crc <<= 1u;
			}
		}
	}
	return crc;
}