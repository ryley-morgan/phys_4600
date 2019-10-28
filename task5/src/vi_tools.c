#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Define scope commands
#define GET_CURV "CURV?\n"
#define GET_DATA "DAT?\n"
#define GET_DATA_ENC "DATA:ENCDG?\n"
#define GET_DATA_WID "DATA:WID?\n"
#define GET_DATA_SRC "DAT:SOU?\n"
#define GET_IDN "*IDN?\n"
#define GET_VOLT "CH%i:SCA?\n"
#define SET_CHX "DAT:SOU CH%i\n"
#define SET_VOLT "CH%i:SCA %E\n"
#define RESULT_BUFFER_SIZE 256
#define DEFAULT_COMMAND_SIZE 36

ViChar resultBuffer[RESULT_BUFFER_SIZE];

// Open scope
ViStatus open_scope(ViSession * defaultRM, ViSession handle, ViFindList * resourceList, ViUInt32 * numInst)
{
    ViChar description[VI_FIND_BUFLEN];
    ViStatus status;
    // Read scope info to populate description and resource list
    status = viFindRsrc(*defaultRM, "USB[0-9]::0x0699?*INSTR",resourceList,numInst,description);  // Techtronics Scopes (Vendor id: 0x0699)
    if(status == VI_SUCCESS)
    {
        status = viOpen(*defaultRM,description, VI_NULL,VI_NULL,&handle);
        // Confirm scope opened correctly
        if(status == VI_SUCCESS)
        {
            printf("Opened %s\n",description);
            viClear(handle); //Clear scope IO buffers
        }
        else
            printf("Failed to open %s",description);
    }
    else
        printf("Couldn't find any instruments");
    return status;
}

// Get functions
ViStatus get_curve(ViSession handle, ViChar * dataBuffer, int npoints)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_CURV, (ViUInt32)strlen(GET_CURV), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, dataBuffer, npoints, &resultCount);
    return status;
}

ViStatus get_data(ViSession handle, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA, (ViUInt32)strlen(GET_DATA), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}

ViStatus get_data_encoding(ViSession handle, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_ENC, (ViUInt32)strlen(GET_DATA_ENC), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}

ViStatus get_data_width(ViSession handle, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_WID, (ViUInt32)strlen(GET_DATA_WID), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}

ViStatus get_data_source(ViSession handle, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_SRC, (ViUInt32)strlen(GET_DATA_SRC), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}

ViStatus get_idn(ViSession handle, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_IDN, (ViUInt32)strlen(GET_IDN), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}

ViStatus get_voltage(ViSession handle, int channel, ViChar * resultBuffer, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    char command[DEFAULT_COMMAND_SIZE];
    sprintf(command, GET_VOLT, channel);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuffer, bufferSize, &resultCount);
    return status;
}


// Set Functions
void set_channel(ViSession handle, int channel)
{
    ViUInt32 resultCount;
    char command[DEFAULT_COMMAND_SIZE];
    sprintf(command, SET_CHX, channel);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}

void set_voltage(ViSession handle, int channel, float volts)
{
    ViUInt32 resultCount;
    char command[DEFAULT_COMMAND_SIZE];
    sprintf(command, SET_VOLT, channel, volts);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}