/*
File: main.c
Author: Ryley Morgan <ryley-morgan@github.com>

Connect and collect waveform from channel 1 of tektronix oscilloscope.
*/
#include "data-io.h"
#include "filters.h"
#include "sin-amplitude.h"
#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vi_tools.h"

#define DATA_BUFFER_SIZE 2500
#define RESULT_BUFFER_SIZE 256

/*
    Connect to oscilloscope, retrieve raw waveform from channel 1. Smooth raw data,
    find maximum amplitude and save both Raw and smoothed waveforms.
    ARGS:
        None
    OUTPUT:
        int:                            return value 0 if successful and 1 if error
*/
int main(int argc, char const *argv[])
{
    // Define constants
    char idn[VI_FIND_BUFLEN];
    double maxVpp;
    double ch1Waveform[DATA_BUFFER_SIZE];
    double ch1WaveformSmoothed[DATA_BUFFER_SIZE];
    double xdata[DATA_BUFFER_SIZE];
    double xdataSmoothed[DATA_BUFFER_SIZE];
    float ch1DAC, ch1xscale, dataEncoding;
    int y, dataSource, dataWidth, nSmoothPts;

    //  Define Vi specific constants
    ViInt8 dataBuffer[DATA_BUFFER_SIZE];
    ViChar resultBuffer[VI_FIND_BUFLEN];
    ViFindList resourceList;
    ViUInt32 numInst;
    ViUInt32 resultCount=0;
    ViStatus status = VI_SUCCESS;
    ViSession defaultRM, scopeHandle, FGHandle;

    // Open default remote connection
    status = viOpenDefaultRM(&defaultRM);

    if(status == VI_SUCCESS)
    {
        status = open_scope(defaultRM,&scopeHandle,&resourceList,&numInst);
        if(status == VI_SUCCESS)
        {
            
            // Get Scope IDN
            get_idn(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE); // From vi_tools.h
            sscanf(resultBuffer,"%s",idn);
            printf("Result Buffer = %s\n",idn);

            // Set scopeHandle to use CH1
            set_channel(scopeHandle, 1);
            memset(resultBuffer, 0, sizeof(resultBuffer));  // Clear result Buffer
            get_data_source(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE); // Get data source
            printf("Data Source (Buffer raw) = %s\n",resultBuffer);
            sscanf(resultBuffer,"CH%i",&dataSource);
            printf("Data Source = %i\n",dataSource); // Print current data source

            // Check data endoding
            memset(resultBuffer, 0, sizeof(resultBuffer));  // Clear result Buffer
            get_data_encoding(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%f",&dataEncoding);
            printf("Data Encoding = %s\n",resultBuffer);

            // Get channel data width
            memset(resultBuffer, 0, sizeof(resultBuffer));  // Clear result Buffer
            get_data_width(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%d",&dataWidth);
            if (strcmp(resultBuffer,"RIBINARY"))
                dataWidth = (256/2)-1; // signed integer from -128 to 127
            else if (strcmp(resultBuffer,"RPBINARY"))
                dataWidth = (65535/2)-1; //  signed integer from -32768 to 32767.
            printf("Data Width = %d\n", dataWidth);

            // Get channel 1 voltage scale
            memset(resultBuffer, 0, sizeof(resultBuffer));  // Clear result Buffer
            get_voltage(scopeHandle,1,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%e", &ch1DAC);
            printf("CH1 Voltage Scale: %e (Volts/Div)\n",ch1DAC);
            ch1DAC = ch1DAC*5/dataWidth; //Scale for Digital-to-Analog conversion with 10 full divisions (2 are missing from screen)
            printf("CH1 Digital to Analog conversion factor: %f (Volts/adc_step)\n", ch1DAC);

            // Set curve x-data start and end points to 1 and 2500, respectively. This captures complete waveform
            set_data_start(scopeHandle);
            set_data_stop(scopeHandle);

            // Get x-axis scaling factor (space between each point)
            memset(resultBuffer, 0, sizeof(resultBuffer));  // Clear result Buffer
            get_x_scale(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%e", &ch1xscale);
            printf("CH1 X scale: %e (Volts/Div)\n",ch1xscale);

            // Get scope curve
            get_curve(scopeHandle, dataBuffer, DATA_BUFFER_SIZE);
        
            // Convert data using digital to analog conversion factor: ch1DAC
            for (int i = 0; i < DATA_BUFFER_SIZE; ++i)
            {
                y = dataBuffer[i];
                ch1Waveform[i] = y*ch1DAC;
                xdata[i] = (i-(DATA_BUFFER_SIZE/2))*ch1xscale;
                printf("Data point = %i, \tRaw = %x,\tRead = %d,\t Value = %f\n",i,y,y,ch1Waveform[i]);
            }

            // Save raw waveform
            saveData(xdata,ch1Waveform,DATA_BUFFER_SIZE,"raw_data.dat");

            // Smooth raw waveform
            nSmoothPts = movingAverageFilter(ch1Waveform,DATA_BUFFER_SIZE,10,ch1WaveformSmoothed);

            // Shrink xdata to fit moving average filter output (lose difference-of-array-sizes/2 off each end)
            if ((nSmoothPts % 2) != 0)
                memcpy(xdataSmoothed,&xdata[(DATA_BUFFER_SIZE-(nSmoothPts-1))/2],nSmoothPts);   // Odd-sized smoothing window
            else
                memcpy(xdataSmoothed,&xdata[(DATA_BUFFER_SIZE-nSmoothPts)/2],nSmoothPts);       // Even-sized smoothing window

            // Save smoothed data including resized x-data array
            saveData(xdataSmoothed,ch1WaveformSmoothed, nSmoothPts,"smooth_data.dat");

            // Calculate maximum amplitude using sin-amplitude.h function
            maxVpp = maxAmplitude(ch1WaveformSmoothed, nSmoothPts);
            printf("Max Amplitude = %f", maxVpp);
        }

    }
    else
        printf("Failed to open defaultRM");
    viClose(scopeHandle);
    viClose(defaultRM);
    return 0;
}

