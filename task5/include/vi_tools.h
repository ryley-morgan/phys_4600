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
#define SET_DATA_START "DAT:STAR 1"
#define SET_DATA_STOP "DAT:STOP 2500"
#define SET_VOLT "CH%i:SCA %E\n"
#define DATA_BUFFER_SIZE 2500
#define RESULT_BUFFER_SIZE 256
#define DEFAULT_COMMAND_SIZE 36


ViStatus open_scope(ViSession * defaultRM, ViSession * handle, ViFindList * resourceList, ViUInt32 * numInst);
// Get functions
ViStatus get_curve(ViSession handle, ViChar * dataBuffer, int npoints);


ViStatus get_data(ViSession handle, ViChar * resultBuf, int bufferSize);


ViStatus get_data_encoding(ViSession handle, ViChar * resultBuf, int bufferSize);


ViStatus get_data_width(ViSession handle, ViChar * resultBuf, int bufferSize);


ViStatus get_data_source(ViSession handle, ViChar * resultBuf, int bufferSize);


ViStatus get_idn(ViSession handle, ViChar * resultBuf, int bufferSize);


ViStatus get_voltage(ViSession handle, int channel, ViChar * resultBuf, int bufferSize);


// Set Functions
void set_channel(ViSession handle, int channel);

void set_data_start(ViSession handle);

void set_data_stop(ViSession handle);

void set_voltage(ViSession handle, int channel, float volts);