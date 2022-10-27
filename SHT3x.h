#include <stdio.h>
#include <stdint.h>



typedef struct SHT3x
{
    double temp;
    double humidity; 
}SHT3x_Results_t;

/////////////////////PUBLIC FUNCTION DECELARATION/////////////////////
SHT3x_Results_t getReadings(int);