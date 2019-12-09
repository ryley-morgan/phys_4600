/*
File: vi_tools.c
Author: Ryley Morgan <ryley-morgan@github.com>

A collection of tools for querying and setting Tektronix oscilloscopes
*/
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
#define GET_X_SCALE "WFMP:XIN?\n"
#define SET_CHX "DAT:SOU CH%i\n"
#define SET_DATA_START "DAT:STAR 1"
#define SET_DATA_STOP "DAT:STOP 2500"
#define SET_VOLT "CH%i:SCA %E\n"
#define DATA_BUFFER_SIZE 2500
#define RESULT_BUFFER_SIZE 256
#define DEFAULT_COMMAND_SIZE 36

/*
    Open connection to oscilloscope
    ARGS:
        ViSession defaultRM:            default VISA connection manager
        ViSession *handle:              oscilloscope handle
        ViFindList *resourceList:       resources available for access
        ViUInt32 *numInst:              number of instruments found
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus open_scope(ViSession defaultRM, ViSession *handle, ViFindList *resourceList, ViUInt32 *numInst)
{
    ViChar description[VI_FIND_BUFLEN];
    ViStatus status;
    // Read scope info to populate description and resource list with Techtronix Scopes
    status = viFindRsrc(defaultRM, "USB[0-9]::0x0699?*INSTR",resourceList,numInst,description);  // Techtronix Scopes (Vendor id: 0x0699)
    if(status == VI_SUCCESS)
    {
        status = viOpen(defaultRM,description,VI_NULL,VI_NULL,handle);
        // Confirm scope opened correctly
        if(status == VI_SUCCESS)
        {
            viSetAttribute(*handle, VI_ATTR_TMO_VALUE, 10000);
            printf("Opened %s\n",description);
            printf("Resource list: %d\n",*resourceList);
            viClear(*handle); //Clear scope IO buffers
        }
        else
            printf("Failed to open %s",description);
    }
    else
        printf("Couldn't find any instruments");
    return status;
}

/*
    Retrieve current waveform from oscilloscope
    ARGS:
        ViSession handle:               oscilloscope handle
        ViInt8 *dataBuf:                address of dataBuffer to store retrieved waveform
        ViUInt32 npoints:               number of points to collect for waveform
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_curve(ViSession handle, ViInt8 *dataBuf, ViUInt32 npoints)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    sleep(2);
    status = viWrite(handle, GET_CURV, (ViUInt32)strlen(GET_CURV), &resultCount); //Specific to our oscilloscope
    status = viRead(handle, dataBuf, npoints, &resultCount);
    return status;
}

/*
    Retrieve current y-axis specification data
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA, (ViUInt32)strlen(GET_DATA), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Retrieve current y-axis data encoding type e.g. RPBINARY, RIBINARY, etc.
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_encoding(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_ENC, (ViUInt32)strlen(GET_DATA_ENC), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Retrieve current y-axis number of ADC bin (256-bit or 65535-bit)
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_width(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_WID, (ViUInt32)strlen(GET_DATA_WID), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Retrieve current y-axis data source channel
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_data_source(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_DATA_SRC, (ViUInt32)strlen(GET_DATA_SRC), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Retrieve current x-axis scale/div in units of volts/div
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_x_scale(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_X_SCALE, (ViUInt32)strlen(GET_DATA_SRC), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Get oscilloscope identification string
    ARGS:
        ViSession handle:               oscilloscope handle
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_idn(ViSession handle, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    viClear(handle);
    viWrite(handle, GET_IDN, (ViUInt32)strlen(GET_IDN), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Retrieve current y-axis voltage/division
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    channel of scope to query
        ViChar *resultBuf:              address of resultBuffer to store retrieved results of query
        int bufferSize:                 size of result buffer
    OUTPUT:
        ViStatus:                       status of last executed vi-command (i.e. viOpen)
*/
ViStatus get_voltage(ViSession handle, int channel, ViChar *resultBuf, int bufferSize)
{
    ViUInt32 resultCount;
    ViStatus status;
    ViChar command[DEFAULT_COMMAND_SIZE];
    sprintf(command, GET_VOLT, channel);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount); //Specific to our oscilloscope
    sleep(2);
    status = viRead(handle, resultBuf, bufferSize, &resultCount);
    return status;
}

/*
    Set oscilloscope channel to 1,2, or 3(MATH)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_channel(ViSession handle, int channel)
{
    ViUInt32 resultCount;
    ViChar command[DEFAULT_COMMAND_SIZE];
    sprintf(command, SET_CHX, channel);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}

/*
    Set data starting point to default for collecting waveform (0 is the left most point)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_data_start(ViSession handle)
{
    ViUInt32 resultCount;
    viClear(handle);
    viWrite(handle, SET_DATA_START, (ViUInt32)strlen(SET_DATA_START), &resultCount); //Specific to our oscilloscope
}

/*
    Set data stop point to default for collecting waveform (2500 is the right most point)
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
    OUTPUT:
        Void:
*/
void set_data_stop(ViSession handle)
{
    ViUInt32 resultCount;
    viClear(handle);
    viWrite(handle, SET_DATA_STOP, (ViUInt32)strlen(SET_DATA_START), &resultCount); //Specific to our oscilloscope
}

/*
    Set oscilloscope voltage scale for channel
    ARGS:
        ViSession handle:               oscilloscope handle
        int channel:                    oscilloscope channel
        float volts:                    floating-point voltage scale
    OUTPUT:
        Void:
*/
void set_voltage(ViSession handle, int channel, float volts)
{
    ViUInt32 resultCount;
    ViChar command[DEFAULT_COMMAND_SIZE];
    sprintf(command, SET_VOLT, channel, volts);
    viClear(handle);
    viWrite(handle, command, (ViUInt32)strlen(command), &resultCount);
}