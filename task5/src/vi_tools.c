#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define scope commands
#define GET_CURV "CURV?\n"
#define GET_DATA "DAT?\n"
#define GET_DATA_SRC "DAT:SOU?\n"
#define GET_DATA_ENC "DATA:ENCDG?\n"
#define GET_DATA_WID "DATA:WID?\n"
#define GET_VOLT "CH%i:SCA?\n"
#define GET_IDN "*IDN?\n"
#define SET_CHX "DAT:SOU CH%i\n"
#define SET_VOLT "CH%i:SCA %E\n"

#define RESULT_BUFFER_SIZE 256

ViChar resultBuffer[RESULT_BUFFER_SIZE];


ViStatus get_curve(ViSession handle, int channel, char * dataBuffer, int npoints)
{
    ViUInt32 resultCount;
    ViStatus status;
    viWrite(handle, GET_CURV, (ViUInt32)strlen(GET_CURV), &resultCount); //Specific to our oscilloscope
    sleep(10);
    status = viRead(handle, dataBuffer, npoints, &resultCount);
    return status;
}

ViStatus get_voltage(ViSession handle, int channel, char* resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    char * command[36];
    sprintf(command, GET_VOLT, channel);
    iWrite(handle, command, (ViUInt32)strlen(command), &resultCount); //Specific to our oscilloscope
    sleep(10);
    status = viRead(handle, dataBuffer, bufferSize, &resultCount);
    return status;
}

void set_channel(ViSession handle, int channel)
{
    ViUInt32 resultCount;
    char * command[36];
    sprintf(command, SET_CHX, channel);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}

void set_voltage(ViSession handle, int channel, float volts)
{
    ViUInt32 resultCount;
    char * command[36];
    sprintf(command, GET_VOLT_CH1, channel, volts);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}



ViStatus init_scope(ViSession handle)
{
    // Set channel
    // Set voltage
    // Set width

    return status;
}