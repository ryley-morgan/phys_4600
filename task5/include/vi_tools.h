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

ViStatus open_scope(ViSession * defaultRM, ViSession handle, ViFindList * resourceList, ViUInt32 * numInst);
// Get functions
ViStatus get_curve(ViSession handle, ViChar * dataBuffer, int npoints);


ViStatus get_data(ViSession handle, ViChar * resultBuffer, int bufferSize);


ViStatus get_data_encoding(ViSession handle, ViChar * resultBuffer, int bufferSize);


ViStatus get_data_width(ViSession handle, ViChar * resultBuffer, int bufferSize);


ViStatus get_data_source(ViSession handle, ViChar * resultBuffer, int bufferSize);


ViStatus get_idn(ViSession handle, ViChar * resultBuffer, int bufferSize);


ViStatus get_voltage(ViSession handle, int channel, ViChar * resultBuffer, int bufferSize);


// Set Functions
void set_channel(ViSession handle, int channel);

void set_voltage(ViSession handle, int channel, float volts);