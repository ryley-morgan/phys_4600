#include "data-io.h"
#include "filters.h"
#include "sin-amplitude.h"
#include <visa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "vi_tools.h"

int main(int argc, char const *argv[])
{
    int y, dataSource, dataWidth, nSmoothPts;
    float ch1DAC, ch1xscale, dataEncoding;
    double max_amplitude;
    double ch1Waveform[2500];
    double ch1WaveformSmoothed[2500];
    double xdata[2500];
    double xdataSmoothed[2500];
    char idn[VI_FIND_BUFLEN];

    //ViChar description[VI_FIND_BUFLEN];
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
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_source(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE); // Get data source
            printf("Data Source (Buffer raw) = %s\n",resultBuffer);
            sscanf(resultBuffer,"CH%i",&dataSource);
            printf("Data Source = %i\n",dataSource); // Print current data source

            // Check data endoding
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_encoding(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%f",&dataEncoding);
            printf("Data Encoding = %s\n",resultBuffer);

            // Get channel data width
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_data_width(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%d",&dataWidth);

            if (strcmp(resultBuffer,"RIBINARY"))
                dataWidth = (256/2)-1; // signed integer from -128 to 127
            else if (strcmp(resultBuffer,"RPBINARY"))
                dataWidth = (65535/2)-1; //  signed integer from -32768 to 32767.
            printf("Data Width = %d\n", dataWidth);

            // Get channel 1 voltage scale
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_voltage(scopeHandle,1,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%e", &ch1DAC);
            printf("CH1 Voltage Scale: %e (Volts/Div)\n",ch1DAC);
            ch1DAC = ch1DAC*5/dataWidth; //Scale for Digital-to-Analog conversion with 10 full divisions (2 are missing from screen)
            printf("CH1 Digital to Analog conversion factor: %f (Volts/adc_step)\n", ch1DAC);

            // Set curve x-data start and end points to 1 and 2500, respectively. This captures complete waveform
            set_data_start(scopeHandle);
            set_data_stop(scopeHandle);

            // Get x-axis scaling factor (space between each point)
            memset(resultBuffer, 0, sizeof(resultBuffer));
            get_x_scale(scopeHandle,resultBuffer,RESULT_BUFFER_SIZE);
            sscanf(resultBuffer,"%e", &ch1xscale);
            printf("CH1 X scale: %e (Volts/Div)\n",ch1xscale);

            // Get scope curve
            get_curve(scopeHandle, dataBuffer, 2500);
        
            // Convert data using digital to analog conversion factor: ch1DAC
            for (int i = 0; i < 2500; ++i)
            {
                y = dataBuffer[i];
                ch1Waveform[i] = y*ch1DAC;
                xdata[i] = (i-(2500/2))*ch1xscale;
                printf("Data point = %i, \tRaw = %x,\tRead = %d,\t Value = %f\n",i,y,y,ch1Waveform[i]);
            }

            saveData(xdata,ch1Waveform,2500,"raw_data.dat");

            nSmoothPts = movingAverageFilter(ch1Waveform,2500,10,ch1WaveformSmoothed);

            // Shrink xdata to fit moving average filter output (lose difference-of-array-sizes/2 off each end)
            if ((nSmoothPts % 2) != 0)
                memcpy(xdataSmoothed,&xdata[(2500-(nSmoothPts-1))/2],nSmoothPts);   // Odd-sized smoothing window
            else
                memcpy(xdataSmoothed,&xdata[(2500-nSmoothPts)/2],nSmoothPts);       // Even-sized smoothing window

            // Save smoothed data including resized x-data array
            saveData(xdataSmoothed,ch1WaveformSmoothed, nSmoothPts,"smooth_data.dat");

            // Calculate maximum amplitude using sin-amplitude.h function
            max_amplitude = maxAmplitude(ch1WaveformSmoothed, nSmoothPts);

            printf("Max Amplitude = %f", max_amplitude);
        }

    }
    else
        printf("Failed to open defaultRM");
    viClose(scopeHandle);
    viClose(defaultRM);
    return 0;
}

